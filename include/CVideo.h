#define __STDC_CONSTANT_MACROS

#ifdef _MSC_VER
#define ALIGN_16(T, F) __declspec(align(16)) T F;
#else
#define ALIGN_16(T, F) T F __attribute__((aligned(16)));
#endif

#ifdef __cplusplus
extern "C"{
#endif
#include <libavfilter/avfilter.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavdevice/avdevice.h>
#include <libavutil/imgutils.h>
#include <libavutil/avstring.h>
#include <libavutil/time.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>

#define SDL_MAIN_HANDLED

#ifdef __cplusplus
}
#endif

#define MAX_QUEUE_SIZE (15 * 1024 * 1024)

#define VIDEO_PICTURE_QUEUE_SIZE (1)

#define SDL_AUDIO_BUFFER_SIZE 1024

#define AVCODEC_MAX_AUDIO_FRAME_SIZE 192000

#define AV_SYNC_THRESHOLD 0.01

#define AV_NOSYNC_THRESHOLD 10.0

typedef struct _VideoPicture{
    SDL_Texture *texture;
    int width, height;
    int allocated;
    double pts;
} VideoPicture;

typedef struct _VideoState{
    ALIGN_16(uint8_t, audioBuf[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 3) / 2])
    ALIGN_16(uint8_t, audioConvertedData[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 3) / 2])
    ALIGN_16(AVPacket, audioPkt)
    ALIGN_16(AVPacket, videoPkt)
    AVFormatContext *pFormatCtx;
    AVCodecContext *audioCtx;
    AVCodecContext *videoCtx;
    struct SwrContext *pSwrCtx;
    struct SwsContext *pSwsCtx;
    int videoStream, audioStream;
    AVStream *audioSt;

    unsigned int audioBufSize, audioBufIndex;
    int hasAudioFrames;
    AVFrame *pAudioFrame;
    AVFrame *pFrameRGB;
    uint8_t *pFrameBuffer;

    int seek_req;
    int seek_flags;
    int64_t seek_pos;

    AVStream *videoSt;

    VideoPicture pictq[VIDEO_PICTURE_QUEUE_SIZE];
    int pictqSize, pictqRindex, pictqWindex;
    SDL_mutex *pictqCs;
    SDL_cond *pictqCv;

    double video_current_pts;
    int64_t video_current_pts_time;

    double videoClock, audioClock, lastFramePts, lastFrameDelay, frameTimer;
} VideoState;

#include "CFilaPacotes.h"

class CVideo:public CPigVisual{

int audioDeviceId;
double volume;
VideoState *is;
SDL_Thread *hParseThread;
SDL_Thread *hVideoThread;
int quit;
bool janelaToda;
PIG_StatusVideo estado;
int64_t pausa;
bool decodeEncerrado;
double tempoFrame;
Janela janelaAtual;
Timer timerProx;
FilaPacotes filaAudio,filaVideo;
SDL_mutex *mutexTex;

double get_video_clock() {
  double delta = (av_gettime() - is->video_current_pts_time) / 1000000.0;
  return is->video_current_pts + delta;
}

static int DecodeThread(void* pUserData){
    CVideo *player = (CVideo*) pUserData;
    VideoState *is = player->is;
    AVPacket pkt;
    int rv;

    for (;player->quit==0;){
        if(is->seek_req) {
            int stream_index= -1;
            int64_t seek_target = is->seek_pos;

            if     (is->videoStream >= 0) stream_index = is->videoStream;
            else if(is->audioStream >= 0) stream_index = is->audioStream;

            if(stream_index>=0){
                //printf("calc target ");
                seek_target= av_rescale_q(seek_target, AV_TIME_BASE_Q,
                                  is->pFormatCtx->streams[stream_index]->time_base);
                //printf("%d\n",seek_target);
            }

            if(av_seek_frame(is->pFormatCtx, stream_index, seek_target, is->seek_flags) < 0) {
                fprintf(stderr, "%s: error while seeking\n", is->pFormatCtx->filename);
            }else{
                //printf("fui pro else\n");
                if(is->audioStream >= 0){
                    //printf("not flush() ok\n");
                    player->filaAudio->Flush();
                    //printf("flush() ok\n");
                    player->filaAudio->PutFlush();
                    //printf("putflush() ok\n");
                }
                //printf("flush fila audio\n");
                if(is->videoStream >= 0){
                    //printf("not flush() ok\n");
                    player->filaVideo->Flush();
                    //printf("flush() ok\n");
                    player->filaVideo->PutFlush();
                    //printf("putflush() ok\n");
                }
                //printf("flush fila video\n");
                //printf("*");
            }
            is->seek_req = 0;
        }

        if (player->filaVideo->GetSize() >= MAX_QUEUE_SIZE || player->filaAudio->GetSize() >= MAX_QUEUE_SIZE){
            SDL_Delay(10);
            continue;
        }

        rv = av_read_frame(is->pFormatCtx, &pkt);
        if (rv < 0){
            //printf("Nao tem frame para decodificar\n");
            break;
        }

        SDL_Delay(10);// need more locking, actually

        if (pkt.stream_index == is->audioStream){
            player->filaAudio->Put(&pkt);
        }else if (pkt.stream_index == is->videoStream){
            player->filaVideo->Put(&pkt);
        }

        av_packet_unref(&pkt);
    }

    //printf("encerrei decode\n");
    player->decodeEncerrado = true;

    return 0;
}

double GetAudioClock(){
    double pts;
    int hwBufSize, bytesPerSec, n;

    pts = is->audioClock;

    hwBufSize = is->audioBufSize - is->audioBufIndex;
    bytesPerSec = 0;
    if (is->audioCtx){
        n = is->audioCtx->channels * sizeof(float);
        bytesPerSec = is->audioCtx->sample_rate * n;
    }
    if (bytesPerSec){
        pts -= hwBufSize / bytesPerSec;
    }

    return pts;
}

int QueuePicture(AVFrame *frame, double pts){

    SDL_LockMutex(is->pictqCs);
    while (is->pictqSize >= VIDEO_PICTURE_QUEUE_SIZE && !quit){
        SDL_CondWait(is->pictqCv, is->pictqCs);
    }
    SDL_UnlockMutex(is->pictqCs);

    if (quit)
        return -1;

    VideoPicture *vp = &is->pictq[is->pictqWindex];

    if (!vp->texture || vp->width != is->videoCtx->width || vp->height != is->videoCtx->height){

        AllocPicture();

        SDL_LockMutex(is->pictqCs);
        while (!vp->allocated && !quit){
            SDL_CondWait(is->pictqCv, is->pictqCs);
        }
        SDL_UnlockMutex(is->pictqCs);

        if (quit)
            return -1;
    }

    if (vp->texture){
        sws_scale(is->pSwsCtx,
                  (const uint8_t * const *)(&frame->data[0]),
                  frame->linesize,
                  0,
                  is->videoCtx->height,
                  is->pFrameRGB->data,
                  is->pFrameRGB->linesize);

        SDL_LockMutex(mutexTex);
        SDL_UpdateTexture(vp->texture, NULL, is->pFrameRGB->data[0], is->pFrameRGB->linesize[0]);
        SDL_UnlockMutex(mutexTex);

        vp->pts = pts;

        if (++is->pictqWindex == VIDEO_PICTURE_QUEUE_SIZE){
            is->pictqWindex = 0;
        }

        SDL_LockMutex(is->pictqCs);
        is->pictqSize++;
        SDL_UnlockMutex(is->pictqCs);
    }

    return 0;
}

double SyncVideo(AVFrame *frame, double pts){
    double frameDelay;

    if (pts != 0){
        is->videoClock = pts;
    }else{
        pts = is->videoClock;
    }

    frameDelay = av_q2d(is->videoSt->time_base);
    frameDelay += frame->repeat_pict * (frameDelay * 0.5);
    is->videoClock += frameDelay;
    return pts;
}

static int VideoThread(void *pUserData){
    CVideo *player = (CVideo*)pUserData;
    VideoState *is = player->is;
    int rv;
    double pts;

    AVFrame *pFrame = av_frame_alloc();

    while (player->filaVideo->Get(&is->videoPkt, !player->decodeEncerrado, player->quit) > 0){
        if (player->quit)
            break;

        if (player->filaVideo->IgualFlushData(is->videoPkt.data)) {
            if (is->videoSt->internal)
            avcodec_flush_buffers(is->videoSt->codec);
            continue;
        }

        rv = avcodec_send_packet(is->videoCtx, &is->videoPkt);
        if (rv < 0) continue;

        while (!avcodec_receive_frame(is->videoCtx, pFrame)){
            if (player->quit)
                break;

            if (is->videoPkt.dts != AV_NOPTS_VALUE){
                pts = (double)av_frame_get_best_effort_timestamp(pFrame);
            }else{
                pts = 0;
            }

            pts *= av_q2d(is->videoSt->time_base);

            pts = player->SyncVideo(pFrame, pts);

            if (player->QueuePicture(pFrame, pts) < 0||player->quit){
                break;
            }
        }
        if (player->quit)
            break;

        av_packet_unref(&is->videoPkt);
    }

    av_frame_free(&pFrame);
    //printf("encerrei video\n");

    return 0;
}

void VideoRefreshTimer(){
    double delay, actualDelay, syncThreshold, refClock, diff;
    static double last=0;
    double atraso = timerProx->GetTempoDecorrido()-(tempoFrame+last);

    if (atraso<0) return;

    if (is->videoCtx&&estado==VIDEO_TOCANDO){

        if (is->pictqSize == 0){
            //ScheduleRefresh(10);
        }else{
            timerProx->Reinicia(0);
            VideoPicture * vp = &is->pictq[is->pictqRindex];
            // timing

            is->video_current_pts = vp->pts;
            is->video_current_pts_time = av_gettime();

            delay = vp->pts - is->lastFramePts;

            if (delay <= 0 || delay >= 1){
                delay = is->lastFrameDelay;//aqui!!!!!!! (Pts)
            }

            // save
            is->lastFrameDelay = delay;
            is->lastFramePts = vp->pts;

            //
            refClock = GetAudioClock();
            diff = vp->pts - refClock;

            // Skip or repeat the frame. Take delay into account
            //FFPlay still doesn't "know if this is the best guess."
            syncThreshold = (delay > AV_SYNC_THRESHOLD) ? delay : AV_SYNC_THRESHOLD;
            if (fabs(diff) < AV_NOSYNC_THRESHOLD){
                if (diff <= -syncThreshold){
                    delay = 0;
                }else if (diff >= syncThreshold){
                    delay = 2 * delay;
                }
            }

            is->frameTimer += delay;

            // computer the REAL delay
            last = actualDelay = is->frameTimer - (av_gettime() / 1000000.0);
            if (actualDelay < 0.01) {
                // Really it should skip the picture instead
                actualDelay = 0.01;
            }

            DisplayVideo();

            if (++is->pictqRindex == VIDEO_PICTURE_QUEUE_SIZE) {
                is->pictqRindex = 0;
            }

            SDL_LockMutex(is->pictqCs);
            is->pictqSize--;
            SDL_CondSignal(is->pictqCv);
            SDL_UnlockMutex(is->pictqCs);

        }
    }
    else{
        //ScheduleRefresh(100);
    }
}

void DisplayVideo(){
    double aspectRatio;
    int windowW, windowH;

    VideoPicture *vp = &is->pictq[is->pictqRindex];

    if (vp->texture&&!janelaToda){
        if (is->videoCtx->sample_aspect_ratio.num == 0){
            aspectRatio = 0;
        }else{
            aspectRatio = av_q2d(is->videoCtx->sample_aspect_ratio) *
                          is->videoCtx->width /
                          is->videoCtx->height;
        }
        if (aspectRatio <= 0.0){
            aspectRatio = is->videoCtx->width / (double)is->videoCtx->height;
        }
        SDL_GetWindowSize(janelaAtual->GetWindow(), &windowW, &windowH);
        //destVideo.h = windowH;
        //destVideo.w = ((int)rint(destVideo.h * aspectRatio)) & -3;

        dest.h = windowH;
        dest.w = ((int)rint(dest.h * aspectRatio)) & -3;
        if (dest.w > windowW) {
            dest.w = windowW;
            dest.h = ((int)rint(dest.w / aspectRatio)) & -3;
        }
        dest.x = (windowW - dest.w) / 2;
        dest.y = (windowH - dest.h) / 2;
    }
}

void AllocPicture(){
    VideoPicture *vp = &is->pictq[is->pictqWindex];
    SDL_LockMutex(mutexTex);
    if (vp->texture){
        SDL_DestroyTexture(vp->texture);
    }

    vp->texture = SDL_CreateTexture(janelaAtual->GetRenderer(),
        SDL_PIXELFORMAT_RGB24,
        SDL_TEXTUREACCESS_STREAMING,
        is->videoCtx->width,
        is->videoCtx->height);
    SDL_UnlockMutex(mutexTex);
    vp->width = is->videoCtx->width;
    vp->height = is->videoCtx->height;

    SDL_SetTextureBlendMode(vp->texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(vp->texture,opacidade);
    SDL_SetTextureColorMod(vp->texture,coloracao.r,coloracao.g,coloracao.b);

    SDL_LockMutex(is->pictqCs);
    vp->allocated = 1;
    SDL_CondSignal(is->pictqCv);
    SDL_UnlockMutex(is->pictqCs);
}

int DecodeAudioFrame(double *ptsPtr){
    int n, dataSize = 0, outSize = 0, rv, hasPacket = 0;
    uint8_t * converted = &is->audioConvertedData[0];
    double pts;

    for (;estado!=VIDEO_PARADO;){
        while (is->hasAudioFrames) {
            rv = avcodec_receive_frame(is->audioCtx, is->pAudioFrame);
            if (rv){
                is->hasAudioFrames = 0;
                break;
            }

            //ajuste manual volume
            for (int i = 0; i < is->pAudioFrame->channels; i++) {
                float *data = (float*)is->pAudioFrame->extended_data[i];

                for (int j = 0; j < is->pAudioFrame->nb_samples; j++){
                    data[j] *= volume;
                    //if (i==0)
                    //    sons[(contSons++)%1000] = data[j];
                }
            }

            dataSize = av_samples_get_buffer_size(NULL,
                                                  is->audioCtx->channels,
                                                  is->pAudioFrame->nb_samples,
                                                  is->audioCtx->sample_fmt,
                                                  1);

            outSize = av_samples_get_buffer_size(NULL,
                                                 is->audioCtx->channels,
                                                 is->pAudioFrame->nb_samples,
                                                 AV_SAMPLE_FMT_FLT,
                                                 1);
            swr_convert(is->pSwrCtx,
                        &converted,
                        is->pAudioFrame->nb_samples,
                        (const uint8_t**)&is->pAudioFrame->data[0],
                        is->pAudioFrame->nb_samples);
            memcpy(is->audioBuf, converted, outSize);

            dataSize = outSize;

            pts = is->audioClock;
            *ptsPtr = pts;
            n = sizeof(float) * is->audioCtx->channels;
            is->audioClock += (double)outSize / (double)(n * is->audioCtx->sample_rate);

            /* We have data, return it and come back for more later */
            return dataSize;
        }

        if (hasPacket){
            av_packet_unref(&is->audioPkt);
        }

        //if (estado==VIDEO_PARADO) break;

        if (estado==VIDEO_PARADO||filaAudio->Get(&is->audioPkt, !decodeEncerrado, quit) < 0){
            break;
        }

        if (filaAudio->IgualFlushData(is->audioPkt.data)) {
            avcodec_flush_buffers(is->audioSt->codec);
            continue;
        }

        if (is->audioPkt.pts != AV_NOPTS_VALUE){
            is->audioClock = av_q2d(is->audioSt->time_base)*is->audioPkt.pts;
        }

        hasPacket = 1;

        rv = avcodec_send_packet(is->audioCtx, &is->audioPkt);
        if (rv) return rv;

        is->hasAudioFrames = 1;
    }
    //printf("encerrei audio frame\n");
    return -1;
}

static void AudioCallback(void *userdata, uint8_t *stream, int len){
    CVideo* player = (CVideo*)userdata;
    VideoState * is = player->is;
    int len1, audioSize;
    double pts;

    while (len > 0){
        if (is->audioBufIndex >= is->audioBufSize){
            // already sent all data; get more
            audioSize = player->DecodeAudioFrame(&pts);

            if (audioSize < 0){
                // error
                is->audioBufSize = SDL_AUDIO_BUFFER_SIZE;
                memset(is->audioBuf, 0, sizeof(is->audioBuf));
            }else{
                is->audioBufSize = audioSize;
            }
            is->audioBufIndex = 0;
        }

        len1 = is->audioBufSize - is->audioBufIndex;
        if (len1 > len)
            len1 = len;
        memcpy(stream, (uint8_t *)is->audioBuf + is->audioBufIndex, len1);
        len -= len1;
        stream += len1;
        is->audioBufIndex += len1;
    }
}

static int DecodeInterruptCallback(void *userData){
    CVideo *player = (CVideo*)userData;
    return player->is && player->quit;
}

int StreamVideoComponentOpen(){
    AVFormatContext *pFormatCtx = is->pFormatCtx;
    int streamIndex = is->videoStream;

    if (streamIndex < 0 || streamIndex >= (int)pFormatCtx->nb_streams)
        return -1;

    AVCodecParameters *codecPar = pFormatCtx->streams[streamIndex]->codecpar;
    if (!codecPar) return -1;

    AVCodec *codec = avcodec_find_decoder(codecPar->codec_id);
    if (!codec) return -1;

    AVCodecContext *codecCtx = avcodec_alloc_context3(codec);
    if (!codecCtx) return -1;

    int rv = avcodec_parameters_to_context(codecCtx, codecPar);
    if (rv < 0){
        avcodec_free_context(&codecCtx);
        return rv;
    }

    rv = avcodec_open2(codecCtx, codec, NULL);
    if (rv < 0){
        avcodec_free_context(&codecCtx);
        return rv;
    }

    is->videoCtx = codecCtx;
    is->videoStream = streamIndex;
    is->videoSt = pFormatCtx->streams[streamIndex];
    is->frameTimer = (double)av_gettime()/ 1000000.0;
    //printf("frame timer: %.2f\n",is->frameTimer);
    is->video_current_pts_time = av_gettime();
    is->lastFrameDelay = 0.01;
    is->pSwsCtx = sws_getContext(codecCtx->width,
                                 codecCtx->height,
                                 codecCtx->pix_fmt,
                                 codecCtx->width,
                                 codecCtx->height,
                                 AV_PIX_FMT_RGB24,
                                 SWS_BILINEAR,
                                 NULL,
                                 NULL,
                                 NULL);
    if(!is->pSwsCtx) return -1;

    is->pFrameRGB = av_frame_alloc();
    if (!is->pFrameRGB) return -1;

    int rgbFrameSize = av_image_get_buffer_size(AV_PIX_FMT_RGB24, codecPar->width, codecPar->height, 8);
    if (rgbFrameSize < 1) return -1;

    is->pFrameBuffer = (uint8_t*)av_malloc(rgbFrameSize);
    if (!is->pFrameBuffer) return AVERROR(ENOMEM);

    rv = av_image_fill_arrays(&is->pFrameRGB->data[0],
                              &is->pFrameRGB->linesize[0],
                              is->pFrameBuffer,
                              AV_PIX_FMT_RGB24,
                              codecPar->width,
                              codecPar->height,
                              1);
    if (rv < 0) return rv;

    return 0;
}

int StreamAudioComponentOpen(){
    AVFormatContext *pFormatCtx = is->pFormatCtx;
    AVCodecContext *codecCtx;
    AVCodec *codec;
    AVCodecParameters *codecPar;
    SDL_AudioSpec wantedSpec = { 0 }, audioSpec = {0};
    int rv;
    int streamIndex = is->audioStream;

    if (streamIndex < 0 || streamIndex >= (int)pFormatCtx->nb_streams)
        return -1;

    codecPar = pFormatCtx->streams[streamIndex]->codecpar;
    codec = avcodec_find_decoder(codecPar->codec_id);
    if (!codec) return -1;

    codecCtx = avcodec_alloc_context3(codec);
    if (!codecCtx) return -1;

    rv = avcodec_parameters_to_context(codecCtx, codecPar);
    if (rv < 0){
        avcodec_free_context(&codecCtx);
        return rv;
    }

    rv = avcodec_open2(codecCtx, codec, NULL);
    if (rv < 0){
        avcodec_free_context(&codecCtx);
        return rv;
    }

    is->audioCtx = codecCtx;
    is->audioStream = streamIndex;
    is->audioBufSize = 0;
    is->audioBufIndex = 0;
    is->audioSt = pFormatCtx->streams[streamIndex];
    memset(&is->audioPkt, 0, sizeof(is->audioPkt));
    is->pAudioFrame = av_frame_alloc();
    if (!is->pAudioFrame) return -1;

    is->pSwrCtx = swr_alloc();
    if (!is->pSwrCtx) return -1;

    if (codecCtx->channel_layout){
        av_opt_set_channel_layout(is->pSwrCtx, "in_channel_layout", codecCtx->channel_layout, 0);
        av_opt_set_channel_layout(is->pSwrCtx, "out_channel_layout", codecCtx->channel_layout, 0);
    }else if (codecCtx->channels == 2){
        av_opt_set_channel_layout(is->pSwrCtx, "in_channel_layout", AV_CH_LAYOUT_STEREO, 0);
        av_opt_set_channel_layout(is->pSwrCtx, "out_channel_layout", AV_CH_LAYOUT_STEREO, 0);
    }else if(codecCtx->channels == 1){
        av_opt_set_channel_layout(is->pSwrCtx, "in_channel_layout", AV_CH_LAYOUT_MONO, 0);
        av_opt_set_channel_layout(is->pSwrCtx, "out_channel_layout", AV_CH_LAYOUT_MONO, 0);
    }else{
        av_opt_set_channel_layout(is->pSwrCtx, "in_channel_layout", AV_CH_LAYOUT_NATIVE, 0);
        av_opt_set_channel_layout(is->pSwrCtx, "out_channel_layout", AV_CH_LAYOUT_NATIVE, 0);
    }

    av_opt_set_int(is->pSwrCtx, "in_sample_rate", codecCtx->sample_rate, 0);
    av_opt_set_int(is->pSwrCtx, "out_sample_rate", codecCtx->sample_rate, 0);
    av_opt_set_sample_fmt(is->pSwrCtx, "in_sample_fmt", codecCtx->sample_fmt, 0);
    av_opt_set_sample_fmt(is->pSwrCtx, "out_sample_fmt", AV_SAMPLE_FMT_FLT, 0);

    rv = swr_init(is->pSwrCtx);
    if (rv < 0) return rv;

    wantedSpec.channels = codecCtx->channels;
    wantedSpec.freq = codecCtx->sample_rate;
    wantedSpec.format = AUDIO_F32;
    wantedSpec.silence = 0;
    wantedSpec.samples = SDL_AUDIO_BUFFER_SIZE;
    wantedSpec.userdata = this;
    wantedSpec.callback = AudioCallback;

    audioDeviceId = SDL_OpenAudioDevice(NULL,0,&wantedSpec, &audioSpec,SDL_AUDIO_ALLOW_ANY_CHANGE);
    if (audioDeviceId < 0) {
        printf("Erro Video: nao foi possivel abrir o dispositivo de audio (%s)\n", SDL_GetError());
        return -1;
    }
    //printf("audiodeviceid: %d\n",audioDeviceId);

    return 0;
}

int CriaVideoState(){
    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
    //printf( "Alocando VideoState\n" );
    is = (VideoState*)av_mallocz(sizeof(VideoState));
    if (!is){
        Stop();
        printf("Erro Video: nao foi possivel alocar memoria!!!\n");
        return -1;
    }

    for (int i=0;i<VIDEO_PICTURE_QUEUE_SIZE;i++){
        is->pictq[i].texture = NULL;
    }

    is->audioStream = -1;
    is->videoStream = -1;
    is->seek_req = 0;

    //printf("Alocando Contexto Geral\n");
    is->pFormatCtx = avformat_alloc_context();
    if (!is->pFormatCtx){
        Stop();
        printf("Erro Video: nao foi possivel criar o contexto de video!!!\n");
        return -2;
    }

    is->pFormatCtx->interrupt_callback.callback = DecodeInterruptCallback;
    is->pFormatCtx->interrupt_callback.opaque = this;

    //printf("Abrindo midia\n");
    int rv = avformat_open_input(&is->pFormatCtx, nomeArquivo.c_str(), NULL, NULL);
    if (rv < 0){
        Stop();
        printf("Erro Video: nao foi possivel abrir a midia %s!!!\n",nomeArquivo);
        return -3;
    }

    //printf("Buscando informacoes dos streams\n");
    rv = avformat_find_stream_info(is->pFormatCtx, NULL);
    if (rv < 0){
        Stop();
        printf("Erro Video: nao foi possivel localizar a informacao dos streams!!!\n");
        return -4;
    }

    //av_dump_format(is->pFormatCtx, 0, filename, 0);

    printf("Marcando Streams\n");
    for (int s = 0; s < is->pFormatCtx->nb_streams; ++s){
        if (is->pFormatCtx->streams[s]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO && is->audioStream < 0){
            is->audioStream = s;
        }else if (is->pFormatCtx->streams[s]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO && is->videoStream < 0){
            is->videoStream = s;
        }
    }
    //printf("etapa2\n");
    if (is->audioStream < 0 && is->videoStream < 0){
        Stop();
        printf("Erro Video: nao foi possivel encontrar os streams!!!\n");
        return -5;
    }

    //printf("Criando Stream de Audio\n");
    if (is->audioStream >= 0){
        rv = StreamAudioComponentOpen();
        if (rv < 0){
            Stop();
            printf("Erro Video: nao foi possivel abrir o stream de audio!!!\n");
            return -6;
        }
    }

    //printf("Criando Stream de Video\n");
    if (is->videoStream >= 0){
        is->pictqCs = SDL_CreateMutex();
        is->pictqCv = SDL_CreateCond();
        rv = StreamVideoComponentOpen();
        if (rv < 0){
            Stop();
            printf("Erro Video: nao foi possivel abrir o stream de video!!!\n");
            return -7;
        }
    }

    //printf("Calculando tempo de Frame\n");
    tempoFrame = 1.0/av_q2d(is->pFormatCtx->streams[is->videoStream]->r_frame_rate);
    //printf("CriaVideoState() encerrado com sucesso!!!\n");
    return 0;
}

void DestroiStream(AVStream *stream){
    //printf("flushei1\n");
    if (stream->codec->internal)
        avcodec_flush_buffers(stream->codec);

    //printf("fecha stream\n");
    if (stream->codec){
        avcodec_close(stream->codec);
        stream->codec = NULL;
    }
}

void DestroiVideoState(){
    if (!is) return;

    //printf("Encerrando mutex e variavel de sessao critica\n");
    SDL_CondSignal(is->pictqCv);
    if (is->videoStream >= 0){
        SDL_DestroyMutex(is->pictqCs);
        SDL_DestroyCond(is->pictqCv);
    }

    //printf("Liberando texturas\n");
    for (int i=0;i<VIDEO_PICTURE_QUEUE_SIZE;i++)
        if (is->pictq[i].texture){
            SDL_DestroyTexture(is->pictq[i].texture);
        }

    //printf("Liberando Frames\n");
    if (is->pAudioFrame)    av_frame_free(&is->pAudioFrame);
    if (is->pFrameRGB)      av_frame_free(&is->pFrameRGB);
    if (is->pFrameBuffer)   av_free(is->pFrameBuffer);

    //printf("Liberando Contextos\n");
    if (is->videoCtx)       avcodec_free_context(&is->videoCtx);
    if (is->audioCtx)       avcodec_free_context(&is->audioCtx);
    if (is->pSwrCtx)        swr_free(&is->pSwrCtx);
    if (is->pSwsCtx)        sws_freeContext(is->pSwsCtx);

    //printf("Destruindo Streams\n");
    DestroiStream(is->videoSt);
    DestroiStream(is->audioSt);

    /*printf("flushei2\n");
    if (is->audioSt->codec->internal)
        avcodec_flush_buffers(is->audioSt->codec);

    printf("fecha audio\n");
    if (is->audioSt->codec){
        avcodec_close(is->audioSt->codec);
        is->audioSt->codec = NULL;
    }*/

    //printf("Encerrando Contexto geral\n");
    avio_flush(is->pFormatCtx->pb);
    //printf("Liberando memoria do Contexto\n");
    avformat_flush(is->pFormatCtx);
    //printf("Liberando VideoState\n");
    if (is) av_free(is);
    is = NULL;
    //printf("DestroiVideoState() encerrado com sucesso!!!\n");
}

public:

CVideo(std::string nomeArq,int idJanela=0):
    CPigVisual(CGerenciadorJanelas::GetJanela(idJanela)->GetAltura(),CGerenciadorJanelas::GetJanela(idJanela)->GetLargura(),nomeArq,idJanela){
    volume = 0.5;
    janelaAtual = CGerenciadorJanelas::GetJanela(idJanela);

    janelaToda = true;
    tempoFrame = -1;
    timerProx = new CTimer(0);

    quit = 0;
    decodeEncerrado = false;
    audioDeviceId = -1;

    estado = VIDEO_PARADO;

    filaAudio = new CFilaPacotes();
    filaVideo = new CFilaPacotes();

    mutexTex = SDL_CreateMutex();
}

~CVideo(){
    Stop();//caso seja chamado o destrutor sem o video já ter sido parado

    if (filaAudio){
        filaAudio->LiberaBlock();
        delete filaAudio;
        filaAudio = NULL;
    }

    if (filaVideo){
        filaVideo->LiberaBlock();
        delete filaVideo;
        filaVideo = NULL;
    }

    //DestroiVideoState();
    //printf("Fim do stop");

    if (timerProx)
        delete timerProx;
    if (mutexTex)
        SDL_DestroyMutex(mutexTex);
}

void SetSeek(double incremento){
    if (!is) return;
    double pos = get_video_clock();
    pos += incremento;
    if(!is->seek_req) {
        is->seek_pos = (int64_t)(pos * AV_TIME_BASE);
        is->seek_flags = incremento < 0 ? AVSEEK_FLAG_BACKWARD : 0;
        is->seek_req = 1;
        //printf("Setado para posicao %d\n",pos);
    }
}

void Play(){
    if (estado!=VIDEO_PARADO) return;
    estado = VIDEO_TOCANDO;
    decodeEncerrado = false;
    quit = 0;

    int erro = CriaVideoState();

    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    //printf("Vou criar thread de video\n");
    hVideoThread = SDL_CreateThread(VideoThread,"iii",this);
    if (!hVideoThread){
        Stop();
        return;
    }

    //printf("Vou criar thread de decodificacao\n");
    hParseThread = SDL_CreateThread(DecodeThread,"ddd", this);
    if (!hParseThread){
        Stop();
        return;
    }

    pausa = av_gettime();

    timerProx->Reinicia(0);// = new CTimer(0);
    //printf("Audio device: %d\n",audioDeviceId);
    SDL_PauseAudioDevice(audioDeviceId,0);

    printf("Play() encerrado com sucesso\n");
}

void Stop(){
    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 111);
    //printf("Vou fazer stop\n");
    if (estado==VIDEO_PARADO) return;//Stop() pode ser chamado isoladamente ou pelo destrutor, mas não deve ser executado 2 vezes
    estado = VIDEO_PARADO;
    quit = 1;

    SDL_CondSignal(is->pictqCv);

    //printf("Vou encerrar audio device\n");
    if (audioDeviceId != -1){
        SDL_PauseAudioDevice(audioDeviceId,1);
        SDL_CloseAudioDevice(audioDeviceId);
    }
    filaAudio->Flush();
    filaVideo->Flush();

    //printf("vou remover threads\n");
    int status=0;
    if (hParseThread)   SDL_WaitThread(hParseThread,&status);
    //printf("Liberado1\n");
    if (hVideoThread)   SDL_WaitThread(hVideoThread,&status);

    DestroiVideoState();

    //printf("Finalizei stop()\n\n");
}

void Pause(){
    if (is==NULL) return;
    if (estado==VIDEO_TOCANDO){
        estado = VIDEO_PAUSADO;
        pausa = av_gettime();
        while (SDL_GetAudioDeviceStatus(audioDeviceId)==SDL_AUDIO_PLAYING)
            SDL_PauseAudioDevice(audioDeviceId,1);
        timerProx->Pausa();
    }
}

void Resume(){
    if (is==NULL) return;
    if (estado==VIDEO_PAUSADO){
        estado = VIDEO_TOCANDO;
        is->frameTimer += (av_gettime()-pausa) / 1000000.0;// - is->vidclk.last_updated
        //printf("pausa?\n");
        timerProx->Despausa();
        while (SDL_GetAudioDeviceStatus(audioDeviceId)==SDL_AUDIO_PAUSED)
            SDL_PauseAudioDevice(audioDeviceId,0);
    }
}

int Desenha(){
    if (estado==VIDEO_PARADO) return 1;
    VideoRefreshTimer();
    //printf("1");
    SDL_LockMutex(mutexTex);
    if (is->pictq[is->pictqRindex].texture)
    SDL_RenderCopyEx(janelaAtual->GetRenderer(), is->pictq[is->pictqRindex].texture, NULL, &dest,-angulo,&pivoRelativo,flip);
    SDL_UnlockMutex(mutexTex);
    return 0;
}

void SetVolume(double valor){
    volume = valor;
    if (volume<0) volume = 0;
}

double GetVolume(){
    return volume;
}

double GetTempoAtual(){
    return is->videoClock;
}

std::string GetTempoAtualString(){
    double base = is->videoClock;
    double fH = base / 3600.;
    int     H = static_cast<int>(fH);
    double fM = (fH - H) * 60.;
    int     M = static_cast<int>(fM);
    double fS = (fM - M) * 60.;
    //sprintf(str,"%d:%02d:%06.3f",H,M,fS);
    return std::to_string(H) + ":" + std::to_string(M) + ":" + std::to_string(fS);
}

double GetTempoTotal(){
    return (is->pFormatCtx->duration*1.0/AV_TIME_BASE);
}

std::string GetTempoTotalString(){
    double base = GetTempoTotal();
    double fH = base / 3600.;
    int     H = static_cast<int>(fH);
    double fM = (fH - H) * 60.;
    int     M = static_cast<int>(fM);
    double fS = (fM - M) * 60.;
    //sprintf(str,"%d:%d:%.3f",H,M,fS);
    return std::to_string(H) + ":" + std::to_string(M) + ":" + std::to_string(fS);
}

double GetTempoFrame(){
    return tempoFrame;
}

double GetFPS(){
    return 1.0/tempoFrame;
}

/*void SetAngulo(float a){
    angulo = a;
}

double GetAngulo(){
    return angulo;
}

void SetFlip(PIG_Flip valor){
    flip = valor;
}

PIG_Flip GetFlip(){
    return flip;
}

void SetPivo(int px,int py){
    pivoRelativo.x = px;
    pivoRelativo.y = destVideo.h-py;
    //printf("pivo mudado para %d,%d\n",pivoRelativo.x,pivoRelativo.y);
}

void SetPivo(float px,float py){
    pivoRelativo.x = px*destVideo.w;
    pivoRelativo.y = destVideo.h-py*destVideo.h;
}

void GetPivo(int &px,int &py){
    px = pivoRelativo.x;
    py = pivoRelativo.y;
}
*/

void Move(int nx,int ny){
    CPigVisual::Move(nx,ny);
    janelaToda = false;
}

void SetDimensoes(int altura,int largura)override{
    CPigVisual::SetDimensoes(altura,largura);
    janelaToda = false;
}

void OcupaJanelaInteira(){
    angulo = 0;
    x = y = 0;
    dest.x = 0;
    dest.y = altJanela-y-alt;
    pivoRelativo.x = pivoRelativo.y = 0;
    dest.h = alt = janelaAtual->GetAltura();
    dest.w = larg = janelaAtual->GetLargura();
    flip = FLIP_NENHUM;
    janelaToda = true;
}

void UsaResolucaoOriginal(){
    janelaToda = false;
}

};

typedef CVideo *Video;

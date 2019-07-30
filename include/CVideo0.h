#define __STDC_CONSTANT_MACROS

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#ifndef WINVER
#define WINVER 0x0601
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif

#ifdef _MSC_VER
#define ALIGN_16(T, F) __declspec(align(16)) T F;
#else
#define ALIGN_16(T, F) T F __attribute__((aligned(16)));
#endif

#ifdef __cplusplus
extern "C"
{
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

//#include <SDL.h>
//#include <SDL_thread.h>
//#include <SDL_syswm.h>
#include <SDL_render.h>
#include <SDL_audio.h>

#ifdef __cplusplus
}
#endif

#define MAX_QUEUE_SIZE (15 * 1024 * 1024)

#define VIDEO_PICTURE_QUEUE_SIZE (10)

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
    AVFormatContext * pFormatCtx;
    AVCodecContext * audioCtx;
    AVCodecContext * videoCtx;
    struct SwrContext * pSwrCtx;
    struct SwsContext * pSwsCtx;
    int videoStream, audioStream;
    AVStream * audioSt;
    //PacketQueue audioq;
    unsigned int audioBufSize, audioBufIndex;
    int hasAudioFrames;
    AVFrame * pAudioFrame;
    AVFrame * pFrameRGB;
    uint8_t * pFrameBuffer;

    int seek_req;
    int seek_flags;
    int64_t seek_pos;

    AVStream *videoSt;
    //PacketQueue videoq;

    VideoPicture pictq[VIDEO_PICTURE_QUEUE_SIZE];
    int pictqSize, pictqRindex, pictqWindex;
    SDL_mutex *pictqCs;
    SDL_cond *pictqCv;

    double video_current_pts;
    int64_t video_current_pts_time;

    double videoClock, audioClock, lastFramePts, lastFrameDelay, frameTimer;

} VideoState;

#include "CFilaPacotes.h"

class CVideo{

int meuId;
int audioDeviceId;
char filename[1024];
VideoState *is = NULL;
SDL_Thread *hParseThread;
SDL_Thread *hVideoThread;
SDL_Rect destVideo;
int quit;
double volume;
int posicaoAutomatica;
double angulo;
int altJanela;
int x,y,alt,larg;
PIG_Flip flip;
SDL_Point pivoRelativo;
PIG_Cor coloracao;
int opacidade;
Janela janelaAtual;
PIG_StatusVideo estado;
int64_t pausa;
bool decodeEncerrado;
double tempoFrame;
Timer timerProx;
FilaPacotes filaAudio,filaVideo;

double get_video_clock() {
  double delta = (av_gettime() - is->video_current_pts_time) / 1000000.0;
  return is->video_current_pts + delta;
}

static Uint32 TimerRefreshCallback(Uint32 interval, void* param){
    CVideo *player = (CVideo*)param;
    SDL_Event evt;
    evt.type = FF_REFRESH_EVENT;
    evt.user.data1 = &(player->meuId);
    SDL_PushEvent(&evt);
    return 0;
}

/*void ScheduleRefresh2(int delay){
    SDL_AddTimer(delay, TimerRefreshCallback, this);
}*/

static int DecodeThread(void* pUserData){
    CVideo *player = (CVideo*) pUserData;
    VideoState * is = player->is;
    AVPacket pkt;
    int rv;

    //gf[13] = is->frameTimer - (av_gettime()/1000000.0);

    for (;;){


        if(is->seek_req) {
            int stream_index= -1;
            int64_t seek_target = is->seek_pos;

            if     (is->videoStream >= 0) stream_index = is->videoStream;
            else if(is->audioStream >= 0) stream_index = is->audioStream;

            if(stream_index>=0){
                seek_target= av_rescale_q(seek_target, AV_TIME_BASE_Q,
                                  is->pFormatCtx->streams[stream_index]->time_base);
            }
            if(av_seek_frame(is->pFormatCtx, stream_index, seek_target, is->seek_flags) < 0) {
                fprintf(stderr, "%s: error while seeking\n", is->pFormatCtx->filename);
            }else{
                if(is->audioStream >= 0) {
                    player->filaAudio->Flush();
                    player->filaAudio->PutFlush();
                }
                if(is->videoStream >= 0) {
                    player->filaVideo->Flush();
                    player->filaVideo->PutFlush();
                }
            }
            is->seek_req = 0;
        }

        if (player->filaVideo->GetSize() >= MAX_QUEUE_SIZE || player->filaAudio->GetSize() >= MAX_QUEUE_SIZE){
            SDL_Delay(10);
            continue;
        }

        rv = av_read_frame(is->pFormatCtx, &pkt);
        if (rv < 0) break;

        SDL_Delay(10); // need more locking, actually

        if (pkt.stream_index == is->audioStream){
            //PacketQueuePut(&is->audioq, &pkt);
            player->filaAudio->Put(&pkt);
        }else if (pkt.stream_index == is->videoStream){
            //PacketQueuePut(&is->videoq, &pkt);
            player->filaVideo->Put(&pkt);
        }

        av_packet_unref(&pkt);
    }

    printf("encerrei decode\n");
    player->decodeEncerrado = true;

    /*while (!player->quit){
        Sleep(100);
    }

    SDL_Event evt;
    evt.type = FF_QUIT_EVENT;
    evt.user.data1 = &(player->meuId);
    SDL_PushEvent(&evt);
*/
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

int QueuePicture(AVFrame* frame, double pts){

    SDL_LockMutex(is->pictqCs);
    while (is->pictqSize >= VIDEO_PICTURE_QUEUE_SIZE && !quit){
        SDL_CondWait(is->pictqCv, is->pictqCs);
    }
    SDL_UnlockMutex(is->pictqCs);

    if (quit)
        return -1;

    VideoPicture * vp = &is->pictq[is->pictqWindex];

    if (!vp->texture || vp->width != is->videoCtx->width || vp->height != is->videoCtx->height){
        /*SDL_Event evt;

        vp->allocated = 0;

        evt.type = FF_ALLOC_EVENT;
        evt.user.data1 = &meuId;
        SDL_PushEvent(&evt);
*/
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

        SDL_UpdateTexture(vp->texture, NULL, is->pFrameRGB->data[0], is->pFrameRGB->linesize[0]);

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

double SyncVideo(AVFrame * frame, double pts){
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

static int VideoThread(void* pUserData){
    CVideo *player = (CVideo*)pUserData;
    VideoState *is = player->is;
    int rv;
    double pts;

    //gf[12] = is->frameTimer - (av_gettime()/1000000.0);

    AVFrame *pFrame = av_frame_alloc();

    //while (PacketQueueGet(&is->videoq, &is->videoPkt, !player->decodeEncerrado, player->quit) > 0){
    while (player->filaVideo->Get(&is->videoPkt, !player->decodeEncerrado, player->quit) > 0){

        if (player->filaVideo->IgualFlushData(is->videoPkt.data)) {
            avcodec_flush_buffers(is->videoSt->codec);
            continue;
        }

        rv = avcodec_send_packet(is->videoCtx, &is->videoPkt);
        if (rv < 0) continue;

        while (!avcodec_receive_frame(is->videoCtx, pFrame)){

            //while (player->estado==VIDEO_PAUSADO);

            if (is->videoPkt.dts != AV_NOPTS_VALUE){
                pts = (double)av_frame_get_best_effort_timestamp(pFrame);
            }else{
                pts = 0;
            }

            pts *= av_q2d(is->videoSt->time_base);

            pts = player->SyncVideo(pFrame, pts);
            if (player->QueuePicture(pFrame, pts) < 0){
                break;
            }
        }


        av_packet_unref(&is->videoPkt);
    }

    av_frame_free(&pFrame);
    printf("encerrei video\n");
    SDL_PauseAudioDevice(player->audioDeviceId,1);
    printf("pause4\n");

    player->Stop();
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
            VideoPicture *vp = &is->pictq[is->pictqRindex];
            // timing

            is->video_current_pts = vp->pts;
            is->video_current_pts_time = av_gettime();

            delay = vp->pts - is->lastFramePts;
            //gf[0] = delay;
            if (delay <= 0 || delay >= 1){
                delay = is->lastFrameDelay;//aqui!!!!!!! (Pts)
            }
            //gf[1] = delay;

            // save
            is->lastFrameDelay = delay;
            is->lastFramePts = vp->pts;

            refClock = GetAudioClock();
            diff = vp->pts - refClock;

            //gf[2] = diff;
            last = 0;

            /* Skip or repeat the frame. Take delay into account
            FFPlay still doesn't "know if this is the best guess." */
            syncThreshold = (delay > AV_SYNC_THRESHOLD) ? delay : AV_SYNC_THRESHOLD;
            if (fabs(diff) < AV_NOSYNC_THRESHOLD){
                if (diff <= -syncThreshold){
                    delay = 0;
                    last = -99999;
                }else if (diff >= syncThreshold){
                    delay = 2 * delay;

                    //gf[4] = 0;
                }//else gf[4] = -1;
            }
            //gf[3] = delay;
            //last = delay;
            //if (cont==2)
            //gf[5] = is->frameTimer;
            is->frameTimer += delay;
            //gf[6] = is->frameTimer;
            //printf("delay %f frame %f",delay,is->frameTimer);

            /* computer the REAL delay */
            //gf[7] = (av_gettime() / 1000000.0);
            actualDelay = is->frameTimer - (av_gettime() / 1000000.0);
            last += actualDelay;
            if (actualDelay < 0.01) {
                /* Really it should skip the picture instead */
                actualDelay = 0.01;
            }
            //gf[4] = actualDelay;

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

    if (vp->texture&&posicaoAutomatica){
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
        destVideo.h = windowH;
        destVideo.w = ((int)rint(destVideo.h * aspectRatio)) & -3;
        if (destVideo.w > windowW) {
            destVideo.w = windowW;
            destVideo.h = ((int)rint(destVideo.w / aspectRatio)) & -3;
        }
        destVideo.x = (windowW - destVideo.w) / 2;
        destVideo.y = (windowH - destVideo.h) / 2;
    }
}

void AllocPicture(){
    VideoPicture *vp = &is->pictq[is->pictqWindex];
    if (vp->texture){
        SDL_DestroyTexture(vp->texture);
    }

    vp->texture = SDL_CreateTexture(janelaAtual->GetRenderer(),
        SDL_PIXELFORMAT_RGB24,
        SDL_TEXTUREACCESS_STREAMING,
        is->videoCtx->width,
        is->videoCtx->height);
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

int DecodeAudioFrame(double * ptsPtr){
    int n, dataSize = 0, outSize = 0, rv, hasPacket = 0;
    uint8_t * converted = &is->audioConvertedData[0];
    double pts;

    //printf("audioframe\n");

    for (;estado!=VIDEO_PARADO;){
        while (is->hasAudioFrames) {
            rv = avcodec_receive_frame(is->audioCtx, is->pAudioFrame);
            if (rv|| is->pAudioFrame->pts>is->pFormatCtx->duration){
                is->hasAudioFrames = 0;
                break;
            }

            //ajuste manual volume
            for (int i = 0; i < is->pAudioFrame->channels; i++) {
                float *data = (float*)is->pAudioFrame->extended_data[i];

                for (int j = 0; j < is->pAudioFrame->nb_samples; j++){
                    //data[j] *= volume;
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

        if (estado==VIDEO_PARADO){
            //audioEncerrado = true;
            printf("pausei1\n");
            system("pause");
            SDL_PauseAudioDevice(audioDeviceId,1);
            break;
        }

        //if (PacketQueueGet(&is->audioq, &is->audioPkt, !decodeEncerrado, quit) < 0){
        if (filaAudio->Get(&is->audioPkt, !decodeEncerrado, quit) < 0){
            //audioEncerrado = true;
            printf("pausei2\n");
            system("pause");
            SDL_PauseAudioDevice(audioDeviceId,1);
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
    printf("encerrei audio frame\n");
    return -1;
}

static void AudioCallback(void *userdata, uint8_t * stream, int len){
    CVideo* player = (CVideo*)userdata;
    VideoState * is = player->is;
    int len1, audioSize;
    double pts;

    //printf("callback\n");
    //double t = (av_gettime()/1000000.0);
    //gf[11] = is->frameTimer - t;
    //printf("ft %.2f clock: %.2f\n",is->frameTimer,t);
    //if (gf[11]>0){
        //system("pause");
    //}

    //if (player->audioEncerrado) return;

    while (len > 0){
        //printf("ainda\n");
        if (is->audioBufIndex >= is->audioBufSize){
            // already sent all data; get more
            //printf("entrando1\n");
            audioSize = player->DecodeAudioFrame(&pts);
            /*if (player->audioEncerrado){
                    printf("pausei3\n");
                    system("pause");
                    SDL_PauseAudioDevice(player->audioDeviceId,1);
                    break;
            }*/
            if (audioSize < 0){
                // error
                SDL_PauseAudioDevice(player->audioDeviceId,1);
                printf("pausei5\n");
                system("pause");
                is->audioBufSize = SDL_AUDIO_BUFFER_SIZE;
                memset(is->audioBuf, 0, sizeof(is->audioBuf));
            }else{
                is->audioBufSize = audioSize;
            }
            is->audioBufIndex = 0;
        }
        //if (player->audioEncerrado) break;
        len1 = is->audioBufSize - is->audioBufIndex;
        if (len1 > len)
            len1 = len;
        memcpy(stream, (uint8_t *)is->audioBuf + is->audioBufIndex, len1);
        len -= len1;
        stream += len1;
        is->audioBufIndex += len1;
    }
}

static int DecodeInterruptCallback(void* userData){
    CVideo *player = (CVideo*)userData;
    return player->is && player->quit;
}

int StreamComponentOpen(int streamIndex){
    AVFormatContext *pFormatCtx = is->pFormatCtx;
    AVCodecContext *codecCtx;
    AVCodec *codec;
    AVCodecParameters *codecPar;
    SDL_AudioSpec wantedSpec = { 0 }, audioSpec = {0};
    int rv, rgbFrameSize;

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

    if (codecPar->codec_type == AVMEDIA_TYPE_AUDIO){
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
            fprintf(stderr, "SDL_OpenAudio: %s\n", SDL_GetError());
            return -1;
        }
        //SDL_PauseAudioDevice(audioDeviceId,1);
        printf("audiodeviceid: %d\n",audioDeviceId);

        //PacketQueueInit(&is->audioq);


    }else if (codecPar->codec_type == AVMEDIA_TYPE_VIDEO){
        is->videoCtx = codecCtx;
        is->videoStream = streamIndex;
        is->videoSt = pFormatCtx->streams[streamIndex];
        is->frameTimer = (double)av_gettime()/ 1000000.0;
        printf("frame timer: %.2f\n",is->frameTimer);
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

        rgbFrameSize = av_image_get_buffer_size(AV_PIX_FMT_RGB24, codecPar->width, codecPar->height, 8);
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

        //PacketQueueInit(&is->videoq);

        hVideoThread = SDL_CreateThread(VideoThread,"iii",this);
        printf("null\n");
        //if (!hVideoThread) return -1;
    }else{
        avcodec_free_context(&codecCtx);
        return -1;
    }

    return 0;
}

public:

CVideo(int id,Janela janela,char *nomeArq){
    meuId = id;
    volume = 0.5;
    janelaAtual = janela;
    coloracao = BRANCO;
    opacidade = 255;
    angulo = 0;
    altJanela = janela->GetAltura();
    flip = FLIP_NENHUM;
    SetPivo(0,0);
    posicaoAutomatica = true;
    tempoFrame = -1;
    timerProx = NULL;

    strcpy(filename,nomeArq);

    estado = VIDEO_PARADO;

    filaAudio = new CFilaPacotes();
    filaVideo = new CFilaPacotes();
}

void SetSeek(double incremento){
    if (!is) return;
    double pos = get_video_clock();
    pos += incremento;
    if(!is->seek_req) {
        is->seek_pos = (int64_t)(pos * AV_TIME_BASE);
        is->seek_flags = incremento < 0 ? AVSEEK_FLAG_BACKWARD : 0;
        is->seek_req = 1;
    }
}

void Play(){
    if (estado!=VIDEO_PARADO) return;

    quit = 0;
    decodeEncerrado = false;//audioEncerrado = false;
    estado = VIDEO_TOCANDO;
    audioDeviceId = -1;
    printf("Vou dar play\n");

    is = (VideoState*)av_mallocz(sizeof(VideoState));
    if (!is){
        Stop();
        return;
    }

    for (int i=0;i<VIDEO_PICTURE_QUEUE_SIZE;i++){
        is->pictq[i].texture = NULL;
    }

    is->audioStream = -1;
    is->videoStream = -1;
    is->seek_req = 0;

    is->pFormatCtx = avformat_alloc_context();
    if (!is->pFormatCtx){
        Stop();
        return;
    }

    is->pFormatCtx->interrupt_callback.callback = DecodeInterruptCallback;
    is->pFormatCtx->interrupt_callback.opaque = this;

    int rv = avformat_open_input(&is->pFormatCtx, filename, NULL, NULL);
    if (rv < 0){
        Stop();
        return;
    }

    rv = avformat_find_stream_info(is->pFormatCtx, NULL);
    if (rv < 0){
        Stop();
        return;
    }

    av_dump_format(is->pFormatCtx, 0, filename, 0);

    //printf("etapa1\n");
    for (int s = 0; s < is->pFormatCtx->nb_streams; ++s){
        if (is->pFormatCtx->streams[s]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO && is->audioStream < 0){
            is->audioStream = s;
        }else if (is->pFormatCtx->streams[s]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO && is->videoStream < 0){
            is->videoStream = s;
        }
    }
    //printf("etapa2\n");
    if (is->audioStream < 0 && is->videoStream < 0){
        rv = -1;
        Stop();
        return;
    }
    //printf("etapa3\n");
    if (is->audioStream >= 0){
        rv = StreamComponentOpen(is->audioStream);
        if (rv < 0){
            Stop();
            return;
        }
    }
    //printf("etapa4\n");
    if (is->videoStream >= 0){
        is->pictqCs = SDL_CreateMutex();
        is->pictqCv = SDL_CreateCond();
        rv = StreamComponentOpen(is->videoStream);
        if (rv < 0){
            Stop();
            return;
        }
    }
    //printf("etapa6\n");
    fprintf(stderr, "STARTING PARSE THREAD\n");
    hParseThread = SDL_CreateThread(DecodeThread,"ddd", this);
    if (!hParseThread){
        Stop();
        return;
    }

    tempoFrame = 1.0/av_q2d(is->pFormatCtx->streams[is->videoStream]->r_frame_rate);

    printf("tempoFrame: %f\n",tempoFrame);
    //refresh=true;
    //ScheduleRefresh(tempoFrame*1000);


    pausa = av_gettime();
    timerProx = new CTimer(0);
    SDL_PauseAudioDevice(audioDeviceId,0);
    //printf("etapa8\n");
    fprintf(stderr, "STARTING SDL LOOP\n");
}

void Pause(){
    if (is==NULL) return;
    if (estado==VIDEO_TOCANDO){
        estado = VIDEO_PAUSADO;
        pausa = av_gettime();
        while (SDL_GetAudioDeviceStatus(audioDeviceId)==SDL_AUDIO_PLAYING)
            SDL_PauseAudioDevice(audioDeviceId,1);
        //timerGeral->Pausa();
        timerProx->Pausa();
    }else if (estado==VIDEO_PAUSADO){
        estado = VIDEO_TOCANDO;

        //totalPausa += (av_gettime()-pausa)/1000000.0;

        is->frameTimer += (av_gettime()-pausa) / 1000000.0;// - is->vidclk.last_updated
        printf("pausa?\n");
        timerProx->Despausa();
        //timerGeral->Despausa();
        while (SDL_GetAudioDeviceStatus(audioDeviceId)==SDL_AUDIO_PAUSED)
            SDL_PauseAudioDevice(audioDeviceId,0);
    }
}

int Desenha(){
    if (estado==VIDEO_PARADO) return 1;
    VideoRefreshTimer();
    SDL_RenderCopyEx(janelaAtual->GetRenderer(), is->pictq[is->pictqRindex].texture, NULL, &destVideo,-angulo,&pivoRelativo,flip);
    return 0;
}

void TrataEvento(PIG_Evento evento){
    return;
    if (evento.tipoEvento==EVENTO_VIDEO){

        switch (evento.video.acao){
        case FF_QUIT_EVENT:
            printf("quit!!!!\n");
            quit = 1;
            Stop();
            return;
            break;
        case FF_ALLOC_EVENT:
            AllocPicture();
            break;
        case FF_REFRESH_EVENT:
            VideoRefreshTimer();
            break;
        default:
            break;
        }
    }
}

~CVideo(){
    Stop();
}

void Stop(){
    return;
    printf("vou fazer stop\n");
    if (estado==VIDEO_PARADO) return;
    printf("vou fazer stop\n");
    estado = VIDEO_PARADO;

    if (audioDeviceId != -1){
        SDL_PauseAudioDevice(audioDeviceId,1);
        SDL_CloseAudioDevice(audioDeviceId);
    }

    printf("limpando-1\n");

    if (timerProx)
        delete timerProx;
    //fprintf(stderr, "Limpando\n");
    if (!is) return;

    //SDL_CondSignal(is->audioq.cv);
    //SDL_CondSignal(is->videoq.cv);
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
    //delete filaAudio;

    SDL_CondSignal(is->pictqCv);


    printf("limpando-1\n");
    //printf("1\n");
    if (hVideoThread)       SDL_DetachThread(hVideoThread);

    if (hParseThread)       SDL_DetachThread(hVideoThread);
printf("2\n");
    //PacketQueueFinish(&(is->videoq));
    //PacketQueueFinish(&(is->audioq));

    delete filaAudio;
    delete filaVideo;

    for (int i=0;i<VIDEO_PICTURE_QUEUE_SIZE;i++)
        if (is->pictq[i].texture){
            SDL_DestroyTexture(is->pictq[i].texture);
        }

    //printf("3\n");
    if (is->pAudioFrame)    av_frame_free(&is->pAudioFrame);
    printf("4\n");
    if (is->pFrameRGB)      av_frame_free(&is->pFrameRGB);
    //printf("5\n");
    if (is->pFrameBuffer)   av_free(is->pFrameBuffer);

    if (is->videoCtx)       avcodec_free_context(&is->videoCtx);
    if (is->audioCtx)       avcodec_free_context(&is->audioCtx);
    if (is->pSwrCtx)        swr_free(&is->pSwrCtx);
    if (is->pSwsCtx)        sws_freeContext(is->pSwsCtx);



    printf("flushei1\n");
    if (is->videoSt->codec->internal)
        avcodec_flush_buffers(is->videoSt->codec);
    printf("flushei2\n");
    if (is->audioSt->codec->internal)
        avcodec_flush_buffers(is->audioSt->codec);

    printf("fecha audio\n");
    if (is->audioSt->codec){
        avcodec_close(is->audioSt->codec);
        is->audioSt->codec = NULL;
    }

    printf("fecha video\n");
    if (is->videoSt->codec){
        avcodec_close(is->videoSt->codec);
        is->videoSt->codec = NULL;
    }

    printf("fechados\n");

    avio_flush(is->pFormatCtx->pb);
    avformat_flush(is->pFormatCtx);

    //if (is->pFormatCtx)     avformat_close_input(&is->pFormatCtx);
    if (is)                 av_free(is);
    is = NULL;

    //printf("6\n");

    //avformat_network_deinit();
}

void SetVolume(double valor){
    volume = valor;
    if (volume<0) volume = 0;
}

double GetVolume(){
    return volume;
}

void GetNomeArquivo(char *nome){
    strcpy(filename,nome);
}

double GetTempoAtual(){
    return is->videoClock;
}

void GetTempoAtual(char *str){
    double base = is->videoClock;
    double fH = base / 3600.;
    int     H = static_cast<int>(fH);
    double fM = (fH - H) * 60.;
    int     M = static_cast<int>(fM);
    double fS = (fM - M) * 60.;
    sprintf(str,"%d:%02d:%06.3f",H,M,fS);
}

double GetTempoTotal(){
    return (is->pFormatCtx->duration*1.0/AV_TIME_BASE);
}

void GetTempoTotal(char *str){
    double base = GetTempoTotal();
    double fH = base / 3600.;
    int     H = static_cast<int>(fH);
    double fM = (fH - H) * 60.;
    int     M = static_cast<int>(fM);
    double fS = (fM - M) * 60.;
    sprintf(str,"%d:%d:%.3f",H,M,fS);
}

double GetTempoFrame(){
    return tempoFrame;
}

double GetFPS(){
    return 1.0/tempoFrame;
}

void SetAngulo(float a){
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

void Move(int nx,int ny){
    x = nx;
    y = ny;
    destVideo.x = x;
    destVideo.y = altJanela-alt-y;
    posicaoAutomatica = false;
}

void SetDimensoes(int altura,int largura){
    destVideo.h = alt = altura;
    destVideo.w = larg = largura;
    destVideo.x = x;
    destVideo.y = altJanela-y-alt;
    posicaoAutomatica = false;
}

void GetDimensoes(int &altura, int &largura){
    altura = alt;
    largura = larg;
    posicaoAutomatica = true;
}

void OcupaJanelaInteira(){
    angulo = 0;
    x = y = 0;
    destVideo.x = 0;
    destVideo.y = altJanela-y-alt;
    pivoRelativo.x = pivoRelativo.y = 0;
    destVideo.h = alt = janelaAtual->GetAltura();
    destVideo.w = larg = janelaAtual->GetLargura();
    flip = FLIP_NENHUM;
    posicaoAutomatica = true;
}

void SetColoracao(PIG_Cor cor){
    coloracao = cor;
}

void SetOpacidade(int valor){
    opacidade = valor;
}

int GetOpacidade(){
    return opacidade;
}


};

typedef CVideo *Video;

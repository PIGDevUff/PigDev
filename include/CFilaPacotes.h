

class CFilaPacotes{

private:

AVPacketList *first, *last;
int nb_packets, size;

AVPacket flushPkt;
SDL_mutex *cs;
SDL_cond *cv;

public:

int GetQtdPacotes(){
    return nb_packets;
}

int GetSize(){
    return size;
}

void SetQtdPacotes(int valor){
    nb_packets = valor;
}

void SetSize(int valor){
    size = valor;
}

int Put(AVPacket *srcPkt){
    AVPacketList *elt;
    AVPacket pkt;
    int rv;

    if(srcPkt != &flushPkt && av_dup_packet(srcPkt) < 0) {
        return -1;
    }

    if (srcPkt->data!=flushPkt.data)
        av_packet_ref(&pkt, srcPkt);

    if (rv) return rv;
    elt = (AVPacketList*)av_malloc(sizeof(AVPacketList));
    if (!elt) return -1;
    elt->pkt = pkt;
    elt->next = NULL;

    SDL_LockMutex(cs);

    if (!last)
        first = elt;
    else
        last->next = elt;
    last = elt;
    nb_packets++;
    size += elt->pkt.size;
    SDL_CondSignal(cv);

    SDL_UnlockMutex(cs);
    return 0;
}

int Get(AVPacket *pkt, int block, int &encerrar){
    AVPacketList * elt;
    int rv;

    if (!pkt) return -1;

    SDL_LockMutex(cs);
    for (;encerrar==false;){

        if (encerrar){
            rv = -1;
            break;
        }

        elt = first;
        if (elt){
            first = elt->next;
            if (!first)
                last = NULL;
            nb_packets--;
            size -= elt->pkt.size;
            *pkt = elt->pkt;
            av_free(elt);
            rv = 1;
            break;
        }else if (!block){
            rv = 0;
            break;
        }else{
            SDL_CondWait(cv, cs);
        }
    }
    SDL_UnlockMutex(cs);
    return rv;
}

int PutFlush(){
    return Put(&flushPkt);
}

void Flush() {
    AVPacketList *pkt, *pkt1;
    SDL_LockMutex(cs);
    for(pkt = first; pkt != NULL; pkt = pkt1) {
        pkt1 = pkt->next;
        av_free_packet(&pkt->pkt);
        av_freep(&pkt);
    }
    last = NULL;
    first = NULL;
    nb_packets = 0;
    size = 0;
    SDL_UnlockMutex(cs);
}

CFilaPacotes(){
    cs = SDL_CreateMutex();
    cv = SDL_CreateCond();
    size = 0;
    nb_packets = 0;
    first = last = NULL;
    av_init_packet(&flushPkt);
    flushPkt.data = (uint8_t*)"FLUSH";
}

~CFilaPacotes(){
    Flush();
    SDL_DestroyMutex(cs);
    SDL_DestroyCond(cv);
}

bool IgualFlushData(uint8_t *data){
    return flushPkt.data == data;
}

void LiberaBlock(){
    SDL_UnlockMutex(cs);
    SDL_CondSignal(cv);
}

};

typedef CFilaPacotes *FilaPacotes;

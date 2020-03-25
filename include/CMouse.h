typedef struct iC{
    SDL_Surface *bitmap;
    SDL_Texture *text;
    char nomeArquivo[60];
} InfoCursor;

class CMouse{

private:

    static int cursorAtual;
    static InfoCursor *cursores[MAX_CURSORES];
    static SDL_Rect rect;
    static int mx,my;

public:

    static void Inicia(SDL_Renderer *render=NULL){
        rect.w = rect.h = 32;
        cursorAtual = 0;
        SDL_ShowCursor(0);
        for (int i=0;i<MAX_CURSORES;i++)
            cursores[i] = NULL;
    }

    static void Encerra(){
        for (int i=0;i<MAX_CURSORES;i++){
            if (cursores[i]){
                CAssetLoader::FreeImage(cursores[i]->nomeArquivo);
                SDL_DestroyTexture(cursores[i]->text);
                free(cursores[i]);
            }
        }
    }

    static void PegaXY(int &x, int &y){
        x = mx;
        y = my;
    }

    static void MudaCursor(int indice){
        cursorAtual = indice;
    }

    static void Desenha(int idJanela=0){
        Janela jan = CGerenciadorJanelas::GetJanela(idJanela);
        SDL_RenderCopy(jan->GetRenderer(),cursores[cursorAtual]->text,NULL,&rect);
    }

    static void Move(int x,int y, int idJanela=0){
        rect.x = x;
        rect.y = CGerenciadorJanelas::GetJanela(idJanela)->GetAltura() - y;
        mx = x;
        my = y;
    }

    static void CarregaCursor(int indice,char *nomeArquivo,int idJanela=0){
        if (cursores[indice]){
            CAssetLoader::FreeImage(cursores[indice]->nomeArquivo);
            SDL_DestroyTexture(cursores[indice]->text);
            free(cursores[indice]);
        }
        cursores[indice] = (InfoCursor*)malloc(sizeof(InfoCursor));
        strcpy(cursores[indice]->nomeArquivo,nomeArquivo);
        SDL_Surface *bitmap = CAssetLoader::LoadImage(nomeArquivo);
        cursores[indice]->bitmap = bitmap;
        if (bitmap==NULL){
            printf("Erro ao ler arquivo: %s\n",nomeArquivo);
            return;
        }

        Uint8 red, green, blue, alpha;
        Uint32 *pixel = (Uint32*)bitmap->pixels;
        SDL_GetRGBA(*pixel,bitmap->format,&red,&green,&blue,&alpha);

        SDL_SetColorKey( bitmap, SDL_TRUE, SDL_MapRGBA(bitmap->format, red, green, blue,alpha) );
        cursores[indice]->text = SDL_CreateTextureFromSurface(CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer(), bitmap);
    }

};

int CMouse::cursorAtual;
InfoCursor* CMouse::cursores[MAX_CURSORES];
SDL_Rect CMouse::rect;
int CMouse::mx;
int CMouse::my;

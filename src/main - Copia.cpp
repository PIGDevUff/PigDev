#include "PIG.h"
#include "CPigComponente.h"
#include "CPigBotao.h"
#include "CPigCaixaTexto.h"

PIG_Evento evento;
PIG_Teclado meuTeclado;

int idObj=-1;
int Funcao(int id, void *param){
    printf("Sou o botao %d\n",id);
    if (idObj>=0){
        DestroiObjeto(idObj);
        idObj=-1;
    }else{
        idObj = CriaObjeto("../imagens/bot.png");
        SetDimensoesObjeto(idObj,20,20);
    }
}

int Habilita(int id, void *param){
    printf("Sou o botao %d\n",id);
    PigBotao bot = (PigBotao) param;
    if (bot->GetEstado()==COMPONENTE_DESABILITADO){
        bot->DefineEstado(COMPONENTE_NORMAL);
    }else{
        bot->DefineEstado(COMPONENTE_DESABILITADO);
    }
}

int main( int argc, char* args[] ){

    CriaJogo("Meu Jogo");

    meuTeclado = GetTeclado();

    int audio = CriaAudio("../audios/Computer Mouse.aif",0);

    int fonte = CriaFonteNormal("../fontes/arial.ttf",10,AZUL,0,PRETO);

    PigBotao bot = new CPigBotao(13,30,30,60,150,"../imagens/bot.png",1);
    bot->DefineTexto("OK");
    bot->DefineSom(audio);
    bot->DefineAtalho(TECLA_k);
    bot->DefineHint("Botão que faz alguma coisa");
    bot->DefineFonteHint(fonte);
    bot->DefineEstado(COMPONENTE_DESABILITADO);
    bot->DefineAcao(Funcao,NULL);

    PigBotao bot2 = new CPigBotao(15,200,30,60,150,"../imagens/bot.png",1);
    bot2->DefineTexto("Habilita");
    bot2->DefineSom(audio);
    bot2->DefineAtalho(TECLA_h);
    bot2->DefineHint("Botão que habilita o outro");
    bot2->DefineFonteHint(fonte);
    //bot2->DefineEstado(COMPONENTE_DESABILITADO);
    bot2->DefineAcao(Habilita,bot);

    PigCaixaTexto caixa = new CPigCaixaTexto(2,30,300,80,400,"../imagens/textbox3.png",50);
    caixa->SetLabel("Nome:");
    caixa->DefineEstado(COMPONENTE_EDITANDO);
    caixa->DefineSom(audio);
    caixa->SetMargens(30,60);
    caixa->SetCorCursor(AZUL);
    //caixa->SetSenha(true,'%');

    //SDL_Rect r = {400,300,40,120};
    //SDL_SetTextInputRect(&r);
    printf("%d %c\n",(uint8_t)'ó','ó');
    printf("%d %c\n",(uint8_t)'é','é');
    printf("%d %c\n",(uint8_t)'í','í');
    printf("%d %c\n",(uint8_t)'ª','ª');
    printf("%d %c\n",(uint8_t)'º','º');

    int mx,my;

    Timer t = new CTimer(false);
    int p=0;
    caixa->SetPosicaoPadraoLabel((PIG_PosicaoComponente)p);

    while(JogoRodando()){
        evento = GetEvento();

        caixa->TrataEvento(evento);
        bot->TrataEvento(evento);
        bot2->TrataEvento(evento);
        CMouse::PegaXY(mx,my);
        //printf("Mouse %d,%d\n",mx,my);
        bot->MouseSobre(mx,my);
        bot2->MouseSobre(mx,my);

        if (t->GetTempoDecorrido()>2){
            p = (p+1)%8;
            caixa->SetPosicaoPadraoLabel((PIG_PosicaoComponente)p);
            t->Reinicia(false);
        }

        IniciaDesenho();

        bot->Desenha();
        bot2->Desenha();
        caixa->Desenha();

        if (idObj>=0){
            DesenhaObjeto(idObj);
        }

        EncerraDesenho();
    }

    FinalizaJogo();
    return 0;
}

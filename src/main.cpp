#include "PIG.h"

PIGEvento evento;          //evento ser tratado a cada passada do loop principal
PIGTeclado meuTeclado;     //variável como mapeamento do teclado

int print(int id, void *param){
    printf("id%d\n",id);
    return 0;
}

//#include "Luz.h"

int main( int argc, char* args[] ){

    //criando o jogo (aplicação)
    CriaJogo("Meu Jogo");

    glewInit();

    //associando o teclado (basta uma única vez) com a variável meuTeclado
    meuTeclado = GetTeclado();

    #define PIGCOMFORM

    //PIGForm form = new CPIGForm("",600,800);
    int form = PIGCriaForm(600,800);
 /*   int menu = PIGCriaItemMenu(form,60,200,"fundo.png");
    int submenu1 = PIGCriaItemMenu(form,60,200,"fundo.png");
    int submenu2 = PIGCriaItemMenu(form,60,200,"fundo.png");
    int submenu3 = PIGCriaItemMenu(form,60,200,"fundo.png");
    int ssubmenu1 = PIGCriaItemMenu(form,60,200,"fundo.png");
    int ssubmenu2 = PIGCriaItemMenu(form,60,200,"fundo.png");
    int ssubmenu3 = PIGCriaItemMenu(form,60,200,"fundo.png");
    int sssubmenu2 = PIGCriaItemMenu(form,60,200,"fundo.png");
    int sssubmenu3 = PIGCriaItemMenu(form,60,200,"fundo.png");

    PIGComponenteMove(menu,10,300);

    PIGComponenteSetLabel(menu,"menuPrinc");
    PIGComponenteSetLabel(submenu1,"submenu1");
    PIGComponenteSetLabel(submenu2,"submenu2");
    PIGComponenteSetLabel(submenu3,"submenu3");
    PIGComponenteSetLabel(ssubmenu1,"ssubmenu1");
    PIGComponenteSetLabel(ssubmenu2,"ssubmenu2");
    PIGComponenteSetLabel(ssubmenu3,"ssubmenu3");
    PIGComponenteSetLabel(sssubmenu2,"sssubmenu2");
    PIGComponenteSetLabel(sssubmenu3,"sssubmenu3");

    PIGMenuSetPosicaoSubMenu(menu,PIG_POSICAO_BAIXO_CENTRO);
    PIGComponenteDefineAcao(submenu1,print,NULL);
    PIGMenuInsereSubMenu(menu,submenu1);
    PIGMenuInsereSubMenu(menu,submenu2);
    PIGMenuInsereSubMenu(menu,submenu3);
    PIGMenuInsereSubMenu(submenu2,ssubmenu1);
    PIGMenuInsereSubMenu(submenu2,ssubmenu2);
    PIGMenuInsereSubMenu(submenu2,ssubmenu3);
    PIGMenuInsereSubMenu(submenu3,sssubmenu2);
    PIGMenuInsereSubMenu(submenu3,sssubmenu3);
*/
    /*PIGItemMenu submenu1 = new CPIGItemMenu(1,"fundo.png","sub1",200,60);
    PIGItemMenu submenu2 = new CPIGItemMenu(2,"fundo.png","sub2",200,60);
    PIGItemMenu submenu3 = new CPIGItemMenu(3,"fundo.png","sub3",200,60);
    PIGItemMenu ssubmenu1 = new CPIGItemMenu(1,"fundo.png","ssub1",200,60);
    PIGItemMenu ssubmenu2 = new CPIGItemMenu(2,"fundo.png","ssub2",200,60);
    PIGItemMenu ssubmenu3 = new CPIGItemMenu(3,"fundo.png","ssub3",200,60);
    PIGItemMenu sssubmenu2 = new CPIGItemMenu(2,"fundo.png","sssub2",200,60);
    PIGItemMenu sssubmenu3 = new CPIGItemMenu(3,"fundo.png","sssub3",200,60);
    PIGItemMenu menu = new CPIGItemMenu(-1,"fundo.png","menu1",200,60);
*/

    int v = CriaVideo("aula07.mp4");

    /*menu->InsereSubMenu(submenu1);
    menu->InsereSubMenu(submenu2);
    menu->InsereSubMenu(submenu3);
    menu->SetPosicaoSubMenu(PIG_POSICAO_BAIXO_CENTRO);
    submenu1->DefineAcao(print,NULL);
    submenu1->SetPosicaoSubMenu(PIG_POSICAO_DIR_BAIXO);
    submenu2->SetPosicaoSubMenu(PIG_POSICAO_DIR_BAIXO);
    submenu3->SetPosicaoSubMenu(PIG_POSICAO_DIR_BAIXO);
    submenu2->InsereSubMenu(ssubmenu1);
    submenu2->InsereSubMenu(ssubmenu2);
    submenu2->InsereSubMenu(ssubmenu3);
    submenu3->InsereSubMenu(sssubmenu2);
    submenu3->InsereSubMenu(sssubmenu3);
    menu->Move(10,300);
    */

    #define PIGCOMFORM

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);

    //PlayVideo(v);
    SetColoracaoVideo(v,ROXO);
    //MoveVideo(v,0,0);

    double soma=0;
    int cont=0;

    int sprite = CriaSprite("teste.png");

    int a = PIGCriaAreaDeTexto(form,100,300);

    int g = PIGCriaGaugeBar(form,200,300,"barra1.png","barra2.png");
    PIGComponenteMove(g,300,380);

    int g1 = PIGCriaGaugeCircular(form,90,90);
    PIGComponenteMove(g1,450,380);

    int s = PIGCriaSlideBar(form,100,250,"barra1.png",120,30,"teste.png");
    PIGComponenteMove(s,450,80);

    //Luz luz(GL_LIGHT0);
    //luz.OnOff(true);
    //luz.DefineCor({180,180,180,255},{200,200,200,255},PRETO);

    //luz.Posiciona(0,0,18);
    int tam=50;
    //cout << s<<" s"<<endl;

    //PIGTimer t = new CPIGTimer(false);

    //loop principal do jogo
    while(JogoRodando()){

        //pega um evento que tenha ocorrido desde a última passada do loop
        evento = GetEvento();
        if (evento.tipoEvento==PIG_EVENTO_TECLADO&&evento.teclado.acao==PIG_TECLA_PRESSIONADA){
            switch(evento.teclado.tecla){
            case PIG_TECLA_CIMA: PIGGaugeCircularAvancaBarra(g1,1);PIGGaugeBarAvancaBarra(g,1);DeslocaSprite(sprite,0,+1);break;
            case PIG_TECLA_BAIXO: PIGGaugeCircularAvancaBarra(g1,-1);PIGGaugeBarAvancaBarra(g,-1);DeslocaSprite(sprite,0,-1);break;
            case PIG_TECLA_DIREITA: DeslocaSprite(sprite,+1,0);break;
            case PIG_TECLA_ESQUERDA: DeslocaSprite(sprite,-1,0);break;
            case PIG_TECLA_KP_MAIS: SetDimensoesSprite(sprite,++tam,tam);break;
            case PIG_TECLA_KP_MENOS: SetDimensoesSprite(sprite,--tam,tam);break;
            }
        }
        /*if (evento.tipoEvento==PIG_EVENTO_TECLADO&&evento.teclado.acao==PIG_TECLA_PRESSIONADA){
            switch(evento.teclado.tecla){
            case PIG_TECLA_p: PauseVideo(v);break;
            case PIG_TECLA_r: ResumeVideo(v);break;
            case PIG_TECLA_BARRAESPACO: PlayVideo(v);break;
            case PIG_TECLA_s: StopVideo(v);break;
            }
        }*/

        //aqui o evento deve ser tratado e tudo deve ser atualizado
        //if (evento.tipoEvento==PIG_EVENTO_MOUSE&&evento.mouse.acao==PIG_MOUSE_PRESSIONADO)
        //menu->TrataEventoMouse(evento);
PIGFormTrataEvento(form,evento);

        //será feita a preparação do frame que será exibido na tela
        IniciaDesenho();


CPIGGerenciadorJanelas::GetJanela(0)->Desloca(0.001,0.0001,0);
DesenhaVideo(v);

SetAnguloVideo(v,tam);
        //todas as chamadas de desenho devem ser feitas aqui na ordem desejada
        //menu->Desenha();
        PIGFormDesenha(form);
PreparaCameraFixa();
        EscreverEsquerda("olá testandú",300,400,VERDE);

        //DesenhaRetanguloVaza
DesenhaSprite(sprite);




        //PreparaCameraMovel();



        //EscreverLongaDireita("testandó teste tesnaod ú dhbs dhbue fne fw",300,300,100,50,VERDE);

        //o frame totalmente pronto será mostrado na tela
        EncerraDesenho();
    }

    //o jogo será encerrado
    FinalizaJogo();

    return 0;
}

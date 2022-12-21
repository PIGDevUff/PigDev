#ifndef _CPIGITEMMENU_
#define _CPIGITEMMENU_


class CPIGItemMenu:public CPIGItemComponente{

private:

    vector<CPIGItemMenu*> submenu;
    PIGPosicaoComponente posSubmenu;

    virtual PIGEstadoEvento OnMouseClick()override{
        if (submenu.size()==0){
            SetAcionado(true);
            if (acao!=NULL)
                acao(id,param);
        }else{
            printf(" mudar de %d acionado\n",acionado);
            SetAcionado(!GetAcionado());
        }

        #ifdef PIGCOMAUDIO
        if (audioComponente>=0) pigGerAudios.Play(audioComponente);
        #endif
        return PIG_COMPONENTE_TRATADO;
    }

public:

    //item com icone e com fundo
    CPIGItemMenu(int idComponente, int alturaIcone,int larguraIcone, string arqImagemIcone, string arqImagemFundo, string labelItem, int larguraLista, int alturaItemLista, int retiraFundo=1, int retiraFundoIcone=1, int janela=0):
        CPIGItemComponente(idComponente,alturaItemLista,larguraLista,arqImagemIcone,arqImagemFundo,labelItem,larguraLista,alturaItemLista,retiraFundo,janela){
        tipo = PIG_ITEMMENU;
        posSubmenu = PIG_POSICAO_DIR_BAIXO;
    }

    //item com icone e sem fundo
    CPIGItemMenu(int idComponente, int alturaIcone,int larguraIcone, string arqImagemIcone, string labelItem, int larguraLista, int alturaItemLista, int retiraFundoIcone=1, int janela=0):
        CPIGItemComponente(idComponente,alturaIcone,larguraIcone,arqImagemIcone,labelItem,larguraLista,alturaItemLista,retiraFundoIcone,janela){
        tipo = PIG_ITEMMENU;
        posSubmenu = PIG_POSICAO_DIR_BAIXO;
    }

    //item sem icone e com fundo
    CPIGItemMenu(int idComponente, string arqImagemFundo, string labelItem, int larguraLista, int alturaItemLista, int retiraFundo=1, int janela=0):
        CPIGItemComponente(idComponente,arqImagemFundo,labelItem,larguraLista,alturaItemLista,retiraFundo,janela){
        tipo = PIG_ITEMMENU;
        posSubmenu = PIG_POSICAO_DIR_BAIXO;
    }

    //item sem icone e sem fundo
    CPIGItemMenu(int idComponente, string labelItem, int larguraLista, int alturaItemLista, int retiraFundo=1, int janela=0):
        CPIGItemComponente(idComponente,labelItem,larguraLista,alturaItemLista,retiraFundo,janela){
        tipo = PIG_ITEMMENU;
        posSubmenu = PIG_POSICAO_DIR_BAIXO;
    }

    virtual ~CPIGItemMenu(){
        //não deletar os submenus pois o próprio form vai chamar o delete prea eles
        submenu.clear();
    }

    void AjustaPosicao(CPIGItemMenu *sub, int indice){
        switch(posSubmenu){
        case PIG_POSICAO_DIR_BAIXO:
            sub->Move(pos.x+larg,pos.y-indice*alt);break;
        case PIG_POSICAO_DIR_CIMA:
            sub->Move(pos.x+larg,pos.y+indice*alt);break;
        case PIG_POSICAO_BAIXO_CENTRO:
            sub->Move(pos.x,pos.y-(indice+1)*alt);break;
        case PIG_POSICAO_BAIXO_DIR:
            sub->Move(pos.x+indice*alt,pos.y-alt);break;
        default: break;
        }
    }

    int InsereSubMenu(CPIGItemMenu *sub){
        int resp = submenu.size();
        AjustaPosicao(sub,resp);

        sub->SetVisivel(false);
        submenu.push_back(sub);
        if (resp==0){
            SetLabel(GetLabel()+"...");
        }

        return resp; //indice onde foi inserido
    }

    void SetPosicaoSubMenu(PIGPosicaoComponente posicao){
        posSubmenu = posicao;
        for (int i=0;i<submenu.size();i++)
            AjustaPosicao(submenu[i],i);
    }

    void SetAcionado(bool valor)override{
        CPIGComponente::SetAcionado(valor);
        if (AjustaFrame) AjustaFrame(this);
        for (CPIGItemMenu *sub:submenu){
            sub->SetVisivel(valor);
        }
        if (!acionado){
            for (CPIGItemMenu *sub:submenu){
                sub->SetAcionado(false);
            }
        }
    }

    void SetHabilitado(bool valor)override{
        CPIGComponente::SetHabilitado(valor);
        for (CPIGItemMenu *sub:submenu){
            sub->SetHabilitado(valor);
        }
    }

    void SetHabilitadoLista(bool valor)override{
        if (valor){
           CPIGComponente::SetHabilitado(habilitadoPorSi);
        }else{
            habilitadoPorSi = habilitado;
            CPIGComponente::SetHabilitado(valor);
        }
        for (CPIGItemMenu *sub:submenu){
            sub->SetHabilitadoLista(valor);
        }
    }

    virtual int Desenha()override{
        if (!visivel) return 0;

        //fundo
        if (imagemPropria)
            CPIGSprite::Desenha();
        else PIGDesenhaRetangulo((int)pos.x,(int)pos.y,alt,larg,coresBasicas[0]);

        if (icone)
            icone->Desenha();
        //CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetanguloVazado((int)pos.x,(int)pos.y,alt,larg,AMARELO);

        for (CPIGItemMenu *sub:submenu)
            sub->Desenha();

        return CPIGComponente::Desenha();
    }

    virtual PIGEstadoEvento TrataEventoMouse(PIGEvento evento)override{
        if (!habilitado) return PIG_COMPONENTE_DESABILITADO;
        if (!visivel) return PIG_COMPONENTE_INVISIVEL;

        ChecaMouseOver(GetPosicaoMouse());

        if(mouseOver){
            if (evento.mouse.acao==PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO){
                return OnMouseClick();
            }
            return PIG_COMPONENTE_MOUSEOVER;
        }else{
            PIGEstadoEvento resp = PIG_COMPONENTE_NAOTRATADO;
            for (CPIGItemMenu *sub:submenu){
                PIGEstadoEvento aux = sub->TrataEventoMouse(evento);
                if (aux != PIG_COMPONENTE_TRATADO&&aux!=PIG_COMPONENTE_MOUSEOVER)
                    sub->SetAcionado(false);
                else if (aux == PIG_COMPONENTE_TRATADO)
                    resp = aux;
            }
            return resp;
        }
    }

    void Desloca(double dx, double dy)override{
        CPIGComponente::Desloca(dx,dy);
        if (icone) icone->Desloca(dx,dy);
        lab->Desloca(dx,dy);
        for (CPIGItemMenu *sub:submenu)
            sub->Desloca(dx,dy);
    }

};

typedef CPIGItemMenu *PIGItemMenu;
#endif //_CPIGITEMMENU_

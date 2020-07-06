class CPigCampoTextoESenha: public CPigCaixaTexto{

private:

    char mascara;//símbolo usado quando o campo for de senha
    std::string (CPigCampoTextoESenha::*GetTextoVisivelPtr)();//ponteiro para a função que vai retornar o texto visivel

    //retorna o texto com a quantidade de símbolos (máscara) igual ao tamanho da string com textobase
    std::string GetTextoMask(){
        std::string resp;
        resp.assign(texto.size(),mascara);
        return resp;
    }

    //recupera a string com o texto visível (com máscara de senha ou não)
    std::string GetTextoVisivel(){
        return (this->*GetTextoVisivelPtr)();
    }

    //desenha apenas o texto
    void DesenhaElementosEspecificos(){
        CGerenciadorFontes::EscreverString(GetTextoVisivel(),xBase,yBase,fonteTexto,CPIG_TEXTO_ESQUERDA);
    }

    //ajusta o alinhamento do cursor
    void AjustaAlinhamento(){
        std::string textoBase = GetTextoVisivel();
        std::string aux;

        xBase = xBaseOriginal;

        aux.assign(textoBase,0,posCursor);
        xCursor = xBase + CGerenciadorFontes::GetLarguraPixels(aux,fonteTexto);

        AjustaBaseTextoEixoX(CGerenciadorFontes::GetLarguraPixels(aux,fonteTexto));
    }

public:

    CPigCampoTextoESenha(int idComponente,int px, int py, int altura,int largura,std::string nomeArq,int maxCars = 200, bool apenasNumeros=false, int retiraFundo=1,int janela=0,bool campoSenha = false):
        CPigCaixaTexto(idComponente,px,py,altura,largura,nomeArq,maxCars,apenasNumeros,retiraFundo,janela){
            yBaseOriginal = y+margemVertBaixo;
            xBaseOriginal = x+margemHorEsq;
            yBase = yBaseOriginal;
            xBase = xBaseOriginal;
            xCursor = xBase;
            yCursor = yBase;
            mascara = '*';
            if(campoSenha){
                GetTextoVisivelPtr = &GetTextoMask;
            }else{
                GetTextoVisivelPtr = &GetTexto;
            }
    }

    CPigCampoTextoESenha(std::string nomeArqParam):CPigCampoTextoESenha(LeArquivoParametros(nomeArqParam)){}

    ~CPigCampoTextoESenha(){}

    static CPigCampoTextoESenha LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,altura,largura,maxCars = 200,retiraFundo=1,janela=0;
        bool apenasNumeros = false,campoSenha = false;

        std::string nomeArq = "",variavel;

        arquivo.open(nomeArqParam);

        if(!arquivo.is_open()) throw CPigErroArquivo(nomeArqParam);
        //formato "x valor"
        while(!arquivo.eof()){
           arquivo >> variavel;
            if(variavel == "idComponente") arquivo >> idComponente;
            if(variavel == "px") arquivo >> px;
            if(variavel == "py") arquivo >> py;
            if(variavel == "altura") arquivo >> altura;
            if(variavel == "largura") arquivo >> largura;
            if(variavel == "nomeArq") arquivo >> nomeArq;
            if(variavel == "retiraFundo") arquivo >> retiraFundo;
            if(variavel == "janela") arquivo >> janela;
            if(variavel == "maxCars") arquivo >> maxCars;
            if(variavel == "apenasNumeros") arquivo >> apenasNumeros;
            if(variavel == "campoSenha") arquivo >> campoSenha;
        }
        arquivo.close();

        if(nomeArq == "") throw CPigErroParametro("nomeArq",nomeArqParam);
       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;
        return CPigCampoTextoESenha(idComponente,px,py,altura,largura,nomeArq,maxCars,apenasNumeros,retiraFundo,janela,campoSenha);

    }

    //define as margens do componente
    void SetMargens(int horEsq,int horDir, int vertBaixo,int vertCima){
        margemVertCima = vertCima;
        margemVertBaixo = vertBaixo;
        margemHorDir = horDir;
        margemHorEsq = horEsq;
        yBaseOriginal = y+margemVertBaixo;
        xBaseOriginal = x+margemHorEsq;
        yBase = yBaseOriginal;
        xBase = xBaseOriginal;
        xCursor = xBase;
        yCursor = yBase;
        AjustaAlinhamento();
    }

    int TrataMouseBotaoDireito(PIG_Evento evento,SDL_Point p){return 1;}//não usa o botão direito

    int TrataMouseRodinha(PIG_Evento evento){return 1;}//não usa arodinha

    int SobeCursor(){return 1;} //não usa o SobeCursor

    int DesceCursor(){return 1;}//não usa o DesceCursor

    int PulaLinha(){return 1;}//não usa o PulaLinha
};

typedef CPigCampoTextoESenha *PigCampoTextoESenha;

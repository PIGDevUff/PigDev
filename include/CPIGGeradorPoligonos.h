class CGeradorPoligono{

private:

    COffscreenRenderer *off;

public:

    CGeradorPoligono(){

    }

    void GeraPoligonoRegular(int raio,int lados,PIG_Cor cor){
        off = new COffscreenRenderer(raio*2+3,raio*2+3);
        off->PintarFundo(PRETO);
        int centroX = raio+1;
        int centroY = raio+1;
        int *x,*y;
        double rad,ang = 90.0;
        x = (int*)malloc((lados+1)*sizeof(int));
        y = (int*)malloc((lados+1)*sizeof(int));

        for (int i=0;i<=lados;i++,ang+=360.0/lados){
            rad = ang*M_PI/180;
            x[i] = cos(rad)*raio+centroX;
            y[i] = sin(rad)*raio+centroY;
            //printf("%d,%d\n",x[i],raio*2+3-y[i]);
        }

        for (int i=0;i<lados;i++)
            off->DesenharLinha(x[i],y[i],x[i+1],y[i+1],cor);

        off->PintarArea(centroX,centroY,cor);
        //off->EncerrarDesenho();
        off->SalvarImagem("poli.bmp");

        free(x);
        free(y);

        delete off;

    }

    void GeraRetanguloChanfrado(int altura,int largura,int chanfro,PIG_Cor cor){
        off = new COffscreenRenderer(altura,largura);
        off->PintarFundo(PRETO);

        off->DesenharRetangulo(chanfro,0,altura,largura-chanfro*2,cor);
        off->DesenharRetangulo(0,chanfro,altura-chanfro*2,largura,cor);

        int centroX = chanfro;
        int centroY = altura-chanfro;
        int *x,*y;
        int lados=20;
        double rad,ang = 90.0;
        x = (int*)malloc((lados+1)*sizeof(int));
        y = (int*)malloc((lados+1)*sizeof(int));


        for (int i=0;i<=lados;i++,ang+=360.0/(lados*4)){
            rad = ang*M_PI/180;
            x[i] = cos(rad)*chanfro+centroX;
            y[i] = sin(rad)*chanfro+centroY;
            //printf("%d,%d\n",x[i],raio*2+3-y[i]);
        }

        for (int i=0;i<lados;i++)
            off->DesenharLinha(x[i],y[i],x[i+1],y[i+1],cor);

        off->PintarArea(centroX-1,centroY+1,cor);

        centroY = chanfro+1;
        ang = 180;
        for (int i=0;i<=lados;i++,ang+=360.0/(lados*4)){
            rad = ang*M_PI/180;
            x[i] = cos(rad)*chanfro+centroX;
            y[i] = sin(rad)*chanfro+centroY;
            printf("%d,%d\n",x[i],altura-y[i]);
        }

        for (int i=0;i<lados;i++)
            off->DesenharLinha(x[i],y[i],x[i+1],y[i+1],cor);
        //printf("11\n");
        off->PintarArea(centroX-1,centroY-1,cor);
        //printf("22\n");
        ang = 270;
        centroX = largura-chanfro;
        for (int i=0;i<=lados;i++,ang+=360.0/(lados*4)){
            rad = ang*M_PI/180;
            x[i] = cos(rad)*chanfro+centroX;
            y[i] = sin(rad)*chanfro+centroY;
            //printf("%d,%d\n",x[i],raio*2+3-y[i]);
        }

        for (int i=0;i<lados;i++)
            off->DesenharLinha(x[i],y[i],x[i+1],y[i+1],cor);

        off->PintarArea(centroX+1,centroY-1,cor);

        ang = 0;
        centroY = altura-chanfro;
        for (int i=0;i<=lados;i++,ang+=360.0/(lados*4)){
            rad = ang*M_PI/180;
            x[i] = cos(rad)*chanfro+centroX;
            y[i] = sin(rad)*chanfro+centroY;
            //printf("%d,%d\n",x[i],raio*2+3-y[i]);
        }

        for (int i=0;i<lados;i++)
            off->DesenharLinha(x[i],y[i],x[i+1],y[i+1],cor);

        off->PintarArea(centroX+1,centroY+1,cor);
        //off->EncerrarDesenho();
        off->SalvarImagem("chanfro.bmp");

        delete off;
    }

    void GeraEstrela(int raio,int pontas,PIG_Cor cor){
        int lados=2*pontas;
        off = new COffscreenRenderer(raio*2+3,raio*2+3);
        off->PintarFundo(PRETO);
        int centroX = raio+1;
        int centroY = raio+1;
        int *x,*y;
        double rad,ang = 90.0;
        x = (int*)malloc((lados+1)*sizeof(int));
        y = (int*)malloc((lados+1)*sizeof(int));

        for (int i=0;i<=lados;i++,ang+=360.0/lados){
            rad = ang*M_PI/180;
            x[i] = cos(rad)*(raio/(1+ (i% 2)))+centroX;
            y[i] = sin(rad)*(raio/(1+ (i% 2)))+centroY;
            //printf("%d,%d\n",x[i],raio*2+3-y[i]);
        }

        for (int i=0;i<lados;i++)
            off->DesenharLinha(x[i],y[i],x[i+1],y[i+1],cor);

        off->PintarArea(centroX,centroY,cor);
        //off->EncerrarDesenho();
        off->SalvarImagem("poli2.bmp");

        free(x);
        free(y);

        delete off;
    }

    void GeraCirculoAberto(int raio,int angulo,PIG_Cor cor){
        off = new COffscreenRenderer(raio*2+3,raio*2+3);
        off->PintarFundo(PRETO);
        int centroX = raio+1;
        int centroY = raio+1;
        int *x,*y;
        double rad,ang = 90.0;
        x = (int*)malloc((angulo+1)*sizeof(int));
        y = (int*)malloc((angulo+1)*sizeof(int));

        for (int ang=0;ang<=angulo;ang++){
            rad = (ang+90)*M_PI/180;
            x[ang] = cos(rad)*raio+centroX;
            y[ang] = sin(rad)*raio+centroY;
            //printf("%d,%d\n",x[i],raio*2+3-y[i]);
        }

        for (int i=0;i<angulo;i++)
            off->DesenharLinha(x[i],y[i],x[i+1],y[i+1],cor);

        off->DesenharLinha(centroX,centroY,x[0],y[0],cor);
        off->DesenharLinha(centroX,centroY,x[angulo],y[angulo],cor);

        off->PintarArea(x[0]-1,y[0]-2,cor);
        //off->EncerrarDesenho();
        off->SalvarImagem("poli.bmp");

        free(x);
        free(y);

        delete off;

    }

    ~CGeradorPoligono(){

    }


};

#nome do arquivo com código principal (função main)
MAIN = main

#nome do executável
EXE = Projeto

#se o projeto não utilizar videos, mudar o valor de MODULOVIDEO abaixo para qualquer outro valor
MODULOVIDEO = PIGCOMVIDEO

#se mostra também a janela de console
MOSTRACONSOLE = SIM

#compilador
CC = mingw32-g++

#flags de compilacao
CC_FLAGS = -Wall -fexceptions -march=core2 -w -std=c++11 -m32 -O3

#flags de arquitetura
CC_ARCH =

#diretorios de busca de arquivos .h
CC_INCLUDE = -I../include -I../include/SDL -I../include/SDL_image -I../include/video

#diretorios de busca de bibliotecas estáticas
CC_LIB = -L../lib

#bibliotecas necessarias
LIBBASICAS = -lpthread -lm
LIBSDL = -m32 -lmingw32 -lSDL2main -lSDL2 -lSDL2_net -lSDL2_image -lSDL2_ttf -lSDL2_mixer -O3

ifeq ($(MODULOVIDEO),PIGCOMVIDEO)
LIBVIDEO = -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lswresample -lswscale
CC_FLAGS += -DPIGCOMVIDEO
else
LIBVIDEO =
endif

ifeq ($(MOSTRACONSOLE),SIM)
OPTCONSOLE =
else
OPTCONSOLE = -mwindows
endif

all: $(EXE)

$(EXE): $(MAIN).o
	$(CC) $(CC_LIB) -o $(EXE).exe $(MAIN).o $(LIBSDL) $(LIBBASICAS) $(LIBVIDEO) $(OPTCONSOLE)
	del /Q /F *.o

$(MAIN).o: $(MAIN).cpp
	$(CC) $(CC_FLAGS) $(CC_ARCH) $(CC_INCLUDE) $(OPTCONSOLE) -c $(MAIN).cpp -o $(MAIN).o

run:
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.:../lib ./$(EXE).exe

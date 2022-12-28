#nome do arquivo com código principal (função main)
MAIN = main

#nome do executável
EXE = Projeto.exe

#compilador
CC = g++

#flags de compilação
CC_FLAGS = -fexceptions -march=core2 -w -std=c++11 -static-libstdc++ -O3
#não vamos mais usar a glew
#-DGLEW_STATIC

#flags de arquitetura
CC_ARCH =

#diretorios de busca de arquivos .h
CC_INCLUDE = -I../include -I./ogldev -I../include/SDL -I../include/SDL_image -I../include/glad -I../include/assimp/include
#não vamos mais usar a glew
#-I../include/glew-2.1.0/include

#diretorios de busca de bibliotecas estáticas
CC_LIB = -L../lib

#-static-libstdc++
#bibliotecas necessárias
LIBBASICAS =  -lassimp.dll -lglu32  -lopengl32 -lpthread -lm
#não vamos mais usar a glew
#../include/glew-2.1.0/lib/Release/Win32/glew32s.lib ../include/glew-2.1.0/lib/Release/Win32/glew32.lib

#se o projeto não utilizar audios, mudar o valor de MODULOAUDIO abaixo para qualquer outro valor ou apenas comentar a linha abaixo
MODULOAUDIO = SIM

#se o projeto não utilizar videos, mudar o valor de MODULOVIDEO abaixo para qualquer outro valor ou apenas comentar a linha abaixo
MODULOVIDEO = SIM

#se o projeto não utilizar sockets, mudar o valor de MODULOREDE abaixo para qualquer outro valor ou apenas comentar a linha abaixo
MODULOREDE = SIM

#se o projeto não utilizar formulários, mudar o valor de MODULOFORM abaixo para qualquer outro valor ou apenas comentar a linha abaixo
MODULOFORM = SIM

#se o projeto não utilizar telas, mudar o valor de MODULOTELA abaixo para qualquer outro valor ou apenas comentar a linha abaixo
MODULOTELA = SIM

#se o projeto não utilizar controles, mudar o valor de MODULOCONTROLE abaixo para qualquer outro valor ou apenas comentar a linha abaixo
MODULOCONTROLE = SIM

#se mostra também a janela de console, além da janela gráfica do jogo
MOSTRACONSOLE = SIM

ifeq ($(MODULOAUDIO),SIM)
LIBAUDIO = -lSDL2_mixer
CC_FLAGS += -DPIGCOMAUDIO
endif

ifeq ($(MODULOVIDEO),SIM)
LIBVIDEO = -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lswresample -lswscale
CC_FLAGS += -DPIGCOMVIDEO
CC_INCLUDE += -I../include/video
endif

ifeq ($(MODULOREDE),SIM)
LIBREDE = -lSDL2_net
CC_FLAGS += -DPIGCOMREDE
endif

ifeq ($(MODULOFORM),SIM)
CC_FLAGS += -DPIGCOMFORM
endif

ifeq ($(MODULOTELA),SIM)
CC_FLAGS += -DPIGCOMTELA
endif

ifeq ($(MODULOCONTROLE),SIM)
CC_FLAGS += -DPIGCOMCONTROLE
endif

ifneq ($(MOSTRACONSOLE),SIM)
OPTCONSOLE = -mwindows
endif

RUNCOMMAND = $(EXE)

ifeq ($(OS),Windows_NT)
	CC_FLAGS +=
	LIBMINGW32 = -lmingw32
	CLEARCOMMAND = del /Q /F *.o
	RUNCOMMAND = set %PATH%=../lib;%PATH% && echo %PATH% && $(EXE)
else
	CLEARCOMMAND = rm *.o
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		RUNCOMMAND = LD_LIBRARY_PATH=LD_LIBRARY_PATH:.:../lib ./$(EXE)
	endif
	ifeq ($(UNAME_S),Darwin)
		RUNCOMMAND = DYLD_LIBRARY_PATH=DYLD_LIBRARY_PATH:.:../lib ./$(EXE)
	endif
endif

all: $(EXE)

$(EXE): $(MAIN).o
	$(CC) $(CC_LIB) -o $(EXE) $(MAIN).o $(LIBMINGW32) -lSDL2main -lSDL2 $(LIBAUDIO) -lSDL2_image -lSDL2_ttf $(LIBREDE)  $(LIBBASICAS) -O3 $(LIBVIDEO) $(OPTCONSOLE)
	$(CLEARCOMMAND)

$(MAIN).o: $(MAIN).cpp
	$(CC) $(CC_FLAGS) $(CC_ARCH) $(CC_INCLUDE) $(OPTCONSOLE) -c $(MAIN).cpp -o $(MAIN).o

.PHONY:
run:
	$(RUNCOMMAND)

#compilador
CC = g++

#flags de compilacao
CC_FLAGS = -Wall -fexceptions -O3 -w -std=c++11

#flags de arquitetura
CC_ARCH = -march=native

#diretorios de busca de arquivos .h
CC_INCLUDE = -I../include -I../include/SDL -I../include/SDL_image -I../include/video

#diretorios de busca de bibliotecas est·ticas
CC_LIB = -L../libLinux -L../bin

#bibliotecas necessarias
LIBRARIES = -pthread -lm -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lswresample -lswscale -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

all: Projeto

Projeto: main.o
	$(CC) $(CC_LIB) $(LIBRARIES) -o Projeto main.o 

main.o: main.cpp
	$(CC) $(CC_FLAGS) $(CC_ARCH) $(CC_INCLUDE) -c main.cpp -o main.o

run:
	DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:.:../libMacOsX ./Projeto
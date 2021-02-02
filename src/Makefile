#compilador
CC = g++

#flags de compilacao
CC_FLAGS = -Wall -fexceptions -O3 -w -std=c++11 -g

#flags de arquitetura
CC_ARCH = native

#flag para decidir qual libLinux usar (x64 ou x86)
OS_BITS = x64

#diretorios de busca de arquivos .h
CC_INCLUDE = -I../include -I../include/SDL -I../include/SDL_image -I../include/video

#diretorios de busca de bibliotecas
CC_LIB = ../libLinux/$(OS_BITS)
LIB_DEST_DIR = /usr/local/lib/

#bibliotecas necessarias
LIBRARIES = -pthread -lm -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lswresample -lswscale -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

$(info CC_ARCH="$(CC_ARCH)")
$(info CC_INCLUDE="$(CC_INCLUDE)")
$(info CC_LIB="$(CC_LIB)")
$(info LIBRARIES="$(LIBRARIES)")

all: Projeto

Projeto: main.o
	export LIBRARY_PATH=$LIBRARY_PATH:.:$(CC_LIB)
	$(CC) main.o -L$(CC_LIB) $(LIBRARIES) -o Projeto

main.o: main.cpp
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) -c main.cpp -o main.o

run:
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.:$(CC_LIB) ./Projeto
	
install-libs:
	sudo cp -R $(CC_LIB)/* $(LIB_DEST_DIR)
	sudo bash -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/pig.conf'
	sudo ldconfig

clean:
	rm *.o Projeto


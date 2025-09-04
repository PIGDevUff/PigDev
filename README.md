# PIG (PigDev) — Biblioteca gráfica sobre SDL

PIG é uma biblioteca C++ que encapsula a SDL e facilita seu uso em projetos educacionais e de jogos 2D. Este repositório traz um esqueleto de projeto já configurado, com Makefile, exemplos e integração opcional com IDEs populares.

## Visão geral

- Foco educacional: facilitar o início em programação de jogos/GUI em C++.
- Multiplataforma: Windows, Linux e macOS.
- Compilação via Makefile, Code::Blocks ou VS Code.
- Modular: habilite/desabilite áudio, vídeo, rede, telas, formulários e controles diretamente no Makefile.

## Requisitos

- Compilador C++ compatível com g++ (GNU C++). No Windows, recomenda-se MinGW32.
- SDL2 e extensões correspondentes já estão incluídas na pasta lib (veja Instalação).
- Threads POSIX (se sua IDE/compilador perguntar, escolha POSIX).

## Instalação

1) Descompacte as bibliotecas nativas
- Acesse a pasta lib.
- Descompacte o .zip referente ao seu sistema operacional dentro da própria pasta lib.
- Se você não pretende usar vídeos, não é necessário descompactar o pacote de vídeo (libVideo_yyy.zip).

2) PATH no Windows (opcional)
- Se for compilar pelo Prompt/PowerShell (sem IDE), adicione a pasta lib do projeto ao PATH do Windows.
- Se for usar Makefile/IDE conforme abaixo, normalmente não é necessário alterar o PATH.

## Como compilar

Há várias formas. Escolha a que preferir:

- Terminal (Makefile)
  - Entre na pasta src:
    ```bash
    cd src
    make          # ou mingw32-make no Windows
    ```
  - O executável é gerado conforme a variável EXE no Makefile (padrão: Projeto.exe).

- VS Code
  - Abra a pasta src no VS Code.
  - Menu Terminal > Run Task... e selecione "Compilar Makefile".

- Code::Blocks
  - Abra primeiro src/Projeto.cbp e depois src/main.cpp.
  - Clique em Compilar.

- Outras IDEs
  - Inclua os cabeçalhos: include, include/SDL, include/SDL_image.
  - Linke as bibliotecas a partir de lib.
  - Se a IDE/compilador perguntarem sobre threads, escolha POSIX.

Dicas do Makefile (src/Makefile):
- MAIN define o arquivo-fonte principal (sem extensão). Padrão: main.
- EXE define o nome do executável.
- As pastas de include e bibliotecas já estão configuradas para o projeto.

## Como executar

- Terminal (Makefile)
  - Na pasta src:
    ```bash
    make run      # executa com as variáveis de ambiente corretas (Linux/macOS)
    ```
  - Observação: no Linux/macOS, o Makefile já exporta LD_LIBRARY_PATH/DYLD_LIBRARY_PATH para encontrar as libs em lib ao usar make run.

- VS Code
  - Menu Terminal > Run Task... e selecione "Executar Makefile".

- Code::Blocks
  - Clique em Executar.

- Executando diretamente o binário
  - Pode ser necessário adicionar a pasta lib ao PATH (Windows) ou trazer as DLLs/.so/.dylib para a pasta src do executável.

## Modularização (habilite apenas o que precisa)

A partir da versão 0.8.0, a PIG é modularizável. No arquivo src/Makefile, defina “SIM” para habilitar um módulo ou comente/alterar o valor para desabilitar:

- MODULOAUDIO: áudio (SDL2_mixer)
- MODULOVIDEO: vídeo (FFmpeg)
- MODULOREDE: rede (SDL2_net)
- MODULOFORM: formulários
- MODULOTELA: telas
- MODULOCONTROLE: controles
- MOSTRACONSOLE: mostra console junto da janela do jogo (no Windows)

Exemplo: para desabilitar vídeo e rede, deixe:
```

# MODULOVIDEO = SIM
# MODULOREDE = SIM
```
## Exemplos de uso

- Estrutura mínima de um aplicativo PIG:
```
cpp
#include "PIG.h"

PIGEvento evento;      // evento a tratar por frame
PIGTeclado meuTeclado; // mapeamento do teclado

int main(int argc, char* args[]) {
    // Cria a janela/aplicação
    CriaJogo("Meu Jogo");

    // Inicializa o teclado (uma vez)
    meuTeclado = GetTeclado();

    // Loop principal
    while (JogoRodando()) {
        // Captura um evento desde o último frame
        evento = GetEvento();

        // Atualize seu estado de jogo aqui (entrada, física, etc.)

        // Início do desenho do frame
        IniciaDesenho();

        // Faça aqui suas chamadas de desenho na ordem desejada

        // Finaliza e apresenta o frame
        EncerraDesenho();
    }

    // Finaliza a aplicação
    FinalizaJogo();
    return 0;
}
```
Dicas:
- GetEvento() retorna um evento ocorrido desde a última iteração do loop principal.
- Envolva toda a sua renderização entre IniciaDesenho() e EncerraDesenho().
- Utilize o Makefile para ativar apenas os módulos que seu projeto realmente usa, reduzindo dependências e tempo de build.

## Novidades

- v0.8.1
  - Labels (CPIGLabel/PIGLabel): textos com pouca alteração de conteúdo ao longo do tempo, com melhor desempenho que renderização caractere a caractere.

- v0.8.0
  - Modularização: habilite/desabilite módulos (vídeo, controladores, etc.) diretamente no Makefile.

## Suporte e contribuição

- Este projeto é open source e voltado a estudantes. Contribuições são bem-vindas!
- Sugestões, issues e PRs ajudam a melhorar a documentação e exemplos.


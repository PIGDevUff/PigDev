***************************************************
                        PIG
***************************************************
                      v 0.8.1

1) Como instalar?
a) Após baixar a PIG (zip), localizar na subpasta /lib os arquivos .zip referentes ao seu SO e descompactá-los nesta mesma subpasta. Se você não pretende utilizar videos, o arquivo .zip relacionado (libVideo_yyy.zip) não precisa ser descompactado.
b) Caso seu SO seja o Windows e você queira compilar os projetos pelo prompt de comando, acrescente no PATH do Windows a subpasta /lib da PIG.
c) Se o seu caso não é o da letra 'b', não é necessária nenhuma modificação adicional, apenas a letra 'a'.

2) Quais compiladores podem ser utilizados?
a) Para todas as situações abaixo, é necessário um compilador C++ compatível com o g++ (GNUC++). Em sistemas Windows, o Mingw32 é o recomendado.
b) Quem preferir utilizar o Code::Blocks, pois há um projeto (/src/Projeto.cbp) já configurado. Recomendamos a versão 17.12 (antiga, mas 100% compatível).
c) Quem preferir o VS-Code, também terá um script de compilação (/src/.vscode/tasks.json) à disposição.
d) Quem utilizar outra IDE deverá configurá-la para que os arquivos da subpasta /include sejam encontrados na compilação e os arquivos da subpasta /lib sejam encontrados na ligação (linking).
e) Caso durante a instalação da IDE ou do Compilador seja perguntado o tipo de thread a ser utilizado, escolha as threads POSIX.

3) Como compilar projetos na PIG?
a) A partir da versão 0.8.0, a PIG utiliza um Makefile para compilar os projetos.
b) O Makefile pode ser editado para alterar as preferências do programador (por sua conta e risco...).  
c) Com o Code::Blocks:
   c1) Abrir o arquivo /src/Projeto.cbp primeiro e depois o /src/main.cpp.
   c2) Clicar no botão de compilar.
d) Com o VS-Code:
   d1) Abrir a subpasta /src.
   d2) Clicar em Terminal>Run Task... e escolher a task "Compilar Makefile".
e) Com outras IDE:
   e1) Configurar a IDE para executar o arquivo Makefile (usando make ou mingw32-make).
   e2) Talvez seja necessário realizar o procedimento indicado no item 2, letra 'd'.
f) Pelo terminal/prompt:
   f1) Ir até a subpasta /src.
   f2) Executar make (ou mingw32-make) para compilar o projeto.

4) Como executar o projeto após ter sido compilado?
a) Com o Code::Blocks, basta clicar no botão de executar.
b) Com o VS-Code, basta escolher a task "Executar Makefile".
c) Com outras IDE, deve ser necessário configurar a IDE para executar o projeto pelo Makefile (usando make run ou mingw32-make run).
d) Pelo terminal/prompt:
   d1) Ir até a subpasta /src.
   d2) Executar make run (ou mingw32-make run) para executar o projeto.
   d3) Se o projeto já tiver sido compilado, também é possível chamar o executável diretamente pelo terminal/prompt, mas, neste caso, provavelmente será necessário acrescentar a subpasta /lib ao PATH do sistema, independente do SO.
   d4) Uma alternativa ao item anterior consiste em trazer as bibliotecas dinâmicas (.dll, .so ou .dylib) para a subpasta /src.

What´s new?
(v0.8.1)
1) É possível criar Labels (CPIGLabel/PIGLabel), que são textos com pouco modificação de conteúdo ao longo do tempo.
Os Labels podem ser criados com um conteúdo (texto), uma fonte e uma cor, posteriormente modificavéis. Os Labels têm desempenho melhor que os métodos Escreve...(), pois não é necessário renderizar caractere por caractere.

(v0.8.0)
1) A PIG agora é modularizável, uma vez que a maioria dos projetos não utiliza todos os subsistemas da PIG. Por exemplo, é possível dispensar o módulo de video ou o módulo de Controladores.
   As alterações podem ser feitas diretamente no Makefile mudando o valor "SIM" do referido módeulo para qualquer outro valor ou até mesmo comentando a linha do módulo.

***************************************************
                        PIG
***************************************************
                      v 0.8.0

1) Como instalar?
a) Após baixar a PIG (zip), localizar na subpasta /lib os arquivos .zip referentes ao seu SO e descompactá-los nesta mesma subpasta. Se você não pretende utilizar videos, o arquivo .zip relacionado (libVideo_yyy.zip) não precisa ser descompactado.
b) Caso seu SO seja o Windows e você queira compilar os projeto pelo prompt de comando, acrescente no PATH do Windows a subpasta /lib da PIG.
c) Se o seu caso não é o da letra 'b', não é necessária nenhuma modificação adicional, apenas a letra 'a'.

2) Quais compiladores podem ser utilizados?
a) Para todas as situações abaixo, é necessário um compilador C++ compatível com o g++ (GNUC++). Em sistemas Windows, o Mingw32 é o recomendado.
b) Quem preferir utilizar o Code::Blocks, pois há um projeto (/src/Projeto.cbp) já configurado. Recomendamos a versão 17.12 (antiga, mas 100% compatível).
c) Quem preferir o VS-Code, também terá um script decompilação (/src/.vscode/tasks.json) à disposição.
d) Quem utilizar outra IDE deverá configurá-la para que os arquivos da subpasta /include sejam encontrados na compilação e os arquivos da subpasta /lib sejam encontrados na ligação (linking).
e) Caso durante a instalação da IDE ou do Compilador seja perguntado o tipo de thread a ser utilizado, escolha as threads POSIX.

3) Como compilar projetos na PIG?
a) A partir da versão 0.8.0, a PIG utiliza um Makefile para compilar os projetos.
b) O Makefile pode ser editado para alterar as preferências do programador (por sua conta e risco...).  
c) Com o Code::Blocks:
   c1) Abrir o arquivo /src/Projeto.cbp primeiro e depois o /src/main.cpp.
   c2) Clicar no botão de compilar e executar.
d) Com o VS-Code:
   d1) Abrir a subpasta /src.
   d2) Clicar em Terminal>Run Task... e escolher a taks adequada (só compilar, só executar ou compilar e executar)
e) Pelo terminal/prompt:
   e1) Ir até a subpasta /src.
   e2) Executar make (ou mingw32-make) para compilar o projeto.
   e3) Executar make run (ou mingw32-make run) para executar o projeto. 
f) Com outras IDE:
   f1) Configurar a IDE para executar o arquivo Makefile (usando make ou mingw32-make).
   f2) Configurar a IDE para executar o projeto pelo Makefile (usando make run ou mingw32-make run).

4) What´s new?
a) A PIG agora é modularizável, uma vez que a maioria dos projetos não utiliza todos os subsistemas da PIG. Por exemplo, é possível dispensar o módulo de video ou o módulo de Controladores.
   As alterações podem ser feitas diretamente no Makefile mudando o valor "SIM" do referido módeulo para qualquer outro valor ou até mesmo comentando a linha do módulo.

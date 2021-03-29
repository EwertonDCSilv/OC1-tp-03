# OC1 2020/2 - Trabalho Prático 3 - 

## Alunos
**Nome**:Ewerton Silva Santos; **Matricula**:2016058140\
**Nome**:Isabelle Vieira Barbosa; **Matricula**: 2018046475\
**Nome**:Matheus Dias; **Matricula**:2019054862

## Como executar
Para compilar e executar um teste bis bash:
``` 
./execute.sh 
```
Na opção via bash pode ser necessário realizar: chmod +x ./execute.sh para tornar executável.\

Para realizar apenas a compilação basta executar a instrução:
``` bash
make
``` 
Para compilar e executar:
``` bash
make run
```
Para compilar e executar um teste:
``` bash
make test
```

# Disposição das pastas
```
+-- bin
|   +-- main          // Arquivo main compilado
+-- build 
|   +-- cache.o       // Binario classe DataCache
|   +-- memory.o      // Binario classe Memory
|   +-- utility.o     // Binario modulo utility
+-- include
|   +-- cache.hpp     // Header classe DataCache
|   +-- memory.hpp    // Header classe Memory
|   +-- utility.hpp   // Header modulo utility
+-- program
|   +-- main.cpp      // Arquivo main do projeto
+-- src
|   +-- cache.cpp     // Codigo classe DataCache
|   +-- memory.cpp    // Codigo classe Memory
|   +-- utility.cpp   // Codigo modulo utility
+-- test  
|   +-- input
|   |   +-- 00.in     // Arquivo de entrada primeiro caso
|   |   +-- 01.in     // Arquivo de entrada segundo caso
|   +-- output
|   |   +-- 00.out    // Arquivo de saida do primeiro caso  
|   |   +-- 01.out    // Arquivo de saida do segundo caso
+-- Makefile          // Makefile do projeto
+-- README.md
+-- diffTest.py       // Script em python para chegar o resultado
+-- alunos.txt        // Alunos responsaveis pelo trabalho
+-- execute.sh        // Script bash para execução simplificada
```

## Sobre o trabalho
Esse trabalho consiste na implementação de uma pequena hierarquia de memória. Nessa hierarquia, existe uma CPU que irá realizar operações de leitura e escrita em um subsistema de memória. Esse subsistema consiste em uma pequena memória cache e uma memória de dados.
A CPU pode disparar operações de escrita e leitura na memória. Operações de leitura enviam um endereço que desejam cessar, esse endereço é passado para a cache que retorna o dado caso um hit ocorra, ou busca um bloco na memória de dados caso um miss ocorra.
Nas operações de escrita, recebe-se um endereço e um dado, primeiro atualiza-se o bloco correspondente
àquele endereço na cache e marca-se tal bloco como "sujo".  Quando surge a necessidade de substituir um bloco já marcado como "sujo" por um novo valor na cache, temos que primeiro atualizar o valor na memória de dados com os dados do bloco "sujo", e depois atualizamos a cache com os dados do novo bloco.
Para implementar tal sistema, faca as seguintes considerações:
- Sua memória de dados consegue armazenar 4096 palavras de 32 bits.

- Sua cache tem a capacidade de armazenar 256 blocos.  Cada bloco da cache contém 16 bytes, que correspondem a 4 palavras de 32 bits, que resultam em 128 bits no total.
- Sua cache utiliza Mapeamento Direto para alocar os blocos.
- Para operações de escrita na memória você deve utilizar a técnica de Frite Bach.
- Os endereços que a CPU fornece contém 12 bits (4096 = 2^12).

Para que seja possível testar o seu sistema, o seu programa deve ser capaz de ler um arquivo em que cada linha representa uma requisição da CPU, contendo as seguintes informações:
- Endereço N para acesso `a memória. (0 <= N <= 2^12)
- Tipo da operação: 0 para leitura, 1 para escrita
- Dado para operação de escrita. Um dado contendo 32 bits a ser escrito na memória
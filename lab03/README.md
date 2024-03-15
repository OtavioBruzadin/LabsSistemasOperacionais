## Como compilar o programa:

Para compilar códigos em C, é necessário instalar o compilador gcc.
```bash
sudo dnf install gcc
```
Para instalar o editor nano devemos utilizar o seguinte comando:
```bash
sudo dnf install nano
```
Para criar e editar um arquivo `.c` utilizamos o seguinte comando:
```bash
nano lab03.c
```
Após a criação e edição  para compilar, devemos utilizar o comando

```bash
gcc -pthread lab03.c -o result
```
Adicionamos `-pthread` para garantir que o codigo seja compilado com suporte a threads

## Como executar o programa:

Para apresentar o resultado na tela, basta utilizarmos o comando abaixo

```bash
./result
```

---

## Comprovando a execução do programa:
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/31077442/e8a7bebf-3cb7-4517-a1d0-9c69e6520848)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/31077442/660f156b-c9ba-4fc4-a6f2-b6f8c997c79e)

Este programa em C cria uma thread filho usando a função clone() para executar uma função específica (threadFunction).

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/31077442/8a24bec3-2cd7-400d-b8c1-67b93ea77ca9)
Para a execucao do programa utilizamos as seguintes bibliotecas:

stdlib.h e malloc.h: Utilizamos para alocação dinâmica de memória com malloc() e free().
sys/types.h e sys/wait.h: utilizadas para definições de tipos e funções para manipulação de processos, como waitpid().
signal.h: Utilizada para configurar manipuladores de sinal com sigaction().
sched.h: utilizado para criar uma nova thread com clone().
stdio.h: Utilizada para entrada e saída de dados.

O processo pai configura um manipulador de sinal (sig_handler) para o sinal SIGUSR1, que será enviado pela thread filho quando ela terminar de executar sua função. A thread filho por sua vez é criada em uma pilha separada, definida pela macro FIBER_STACK, que representa o tamanho da pilha. E a função threadFunction é a função que será executada pela thread filho, nela, uma mensagem é impressa indicando que a thread filho está encerrando e, em seguida, é enviado um sinal SIGUSR1 para o processo pai.
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/31077442/bc732085-68fd-4581-b496-a10a0a6983d0)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/31077442/b1d49fe7-a4e7-41a5-a227-b6b07cbf7668)


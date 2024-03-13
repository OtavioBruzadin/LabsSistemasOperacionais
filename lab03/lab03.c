#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>

// Define o tamanho da pilha para a thread
#define FIBER_STACK (1024*64)

// Variável compartilhada entre a thread filho e o processo pai
int shared_int = 0;

// Handler para o sinal enviado pela thread filho
void sig_handler(int signum) {
    // Verifica se o sinal recebido é SIGUSR1
    if (signum == SIGUSR1) {
        // Altera o valor do inteiro compartilhado
        shared_int = 42;
    }
}

// Função que será executada pela thread filho
int threadFunction(void* argument) {
    // Imprime uma mensagem indicando que a thread filho está saindo
    printf("Filho: thread encerrando\n");

    // Envia um sinal SIGUSR1 para o processo pai
    kill(getppid(), SIGUSR1);

    return 0;
}

int main() {
    void* stack;
    pid_t pid;
    struct sigaction sa;

    // Configura o handler para o sinal SIGUSR1
    sa.sa_handler = sig_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    // Registra o handler de sinal
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Aloca a pilha para a thread
    stack = malloc(FIBER_STACK);
    // Verifica se a alocação foi bem-sucedida
    if (stack == NULL) {
        perror("malloc: não foi possível alocar a pilha");
        exit(EXIT_FAILURE);
    }

    // Exibe o valor inicial do inteiro compartilhado
    printf("Main: valor inicial do inteiro compartilhado: %d\n", shared_int);

    // Imprime uma mensagem indicando a criação da thread filho
    printf("Main: criando thread filho\n");

    // Chama o sistema clone para criar a thread filho
    pid = clone(&threadFunction, (char*)stack + FIBER_STACK,
                SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0);
    // Verifica se a chamada do clone foi bem-sucedida
    if (pid == -1) {
        perror("clone");
        exit(EXIT_FAILURE);
    }

    // Aguarda o sinal SIGUSR1 enviado pela thread filho
    while (shared_int == 0) {
        // Aguarda o sinal de término da thread filho
        printf("Main: aguardando sinal do filho...\n");
        sleep(1); // Aguarda por 1 segundo antes de verificar novamente
    }

    // Exibe o valor do inteiro compartilhado, que foi alterado pela thread filho
    printf("Main: valor do inteiro compartilhado alterado pela thread filho: %d\n", shared_int);

    // Libera a pilha alocada
    free(stack);
    // Imprime uma mensagem indicando o término do programa
    printf("Main: thread filho terminou e pilha liberada.\n");
    return 0;
}

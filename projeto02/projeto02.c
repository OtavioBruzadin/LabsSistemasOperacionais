#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <pthread.h>

// 64kB stack
#define FIBER_STACK 1024*64

struct c {
    int saldo;
    pthread_mutex_t mutex;
};
typedef struct c conta;

conta from, to;
int valor;

// A função de transferência agora usa mutex para sincronizar o acesso aos saldos
int transferencia(void *arg) {
    pthread_mutex_lock(&from.mutex); // Bloqueia o mutex de 'from'
    if (from.saldo >= valor) {
        from.saldo -= valor;
        pthread_mutex_lock(&to.mutex); // Bloqueia o mutex de 'to' dentro da condição
        to.saldo += valor;
        pthread_mutex_unlock(&to.mutex); // Libera o mutex de 'to'
    }
    pthread_mutex_unlock(&from.mutex); // Libera o mutex de 'from'
    printf("Transferência concluída com sucesso!\n");
    printf("Saldo de c1: %d\n", from.saldo);
    printf("Saldo de c2: %d\n", to.saldo);
    return 0;
}

int main() {
    void *stack;
    pid_t pid;
    int i, status;

    // Inicializa os mutexes
    pthread_mutex_init(&from.mutex, NULL);
    pthread_mutex_init(&to.mutex, NULL);

    // Aloca a pilha
    stack = malloc(FIBER_STACK);
    if (stack == 0) {
        perror("malloc: could not allocate stack");
        exit(1);
    }

    // Todas as contas começam com saldo 100
    from.saldo = 100;
    to.saldo = 100;

    printf("Transferindo 10 para a conta c2\n");
    valor = 10;
    for (i = 0; i < 10; i++) {
        pid = clone(&transferencia, (char*)stack + FIBER_STACK,
            SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0);
        if (pid == -1) {
            perror("clone");
            exit(2);
        }
    }

    // Espera por todas as threads filhas
    for (i = 0; i < 10; i++) {
        wait(&status); // Aguarda qualquer filho terminar
    }

    // Libera a pilha
    free(stack);
    printf("Transferências concluídas e memória liberada.\n");

    // Destroi os mutexes
    pthread_mutex_destroy(&from.mutex);
    pthread_mutex_destroy(&to.mutex);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define FIBER_STACK 1024*64

struct conta {
    int saldo;
    pthread_mutex_t mutex;
};

typedef struct conta Conta;

Conta from, to;
int valor;
pthread_mutex_t transfer_mutex;

void *transferencia(void *args) {
    pthread_mutex_lock(&transfer_mutex);

    Conta *sender = ((Conta**)args)[0];
    Conta *receiver = ((Conta**)args)[1];

    pthread_mutex_lock(&sender->mutex);
    pthread_mutex_lock(&receiver->mutex);

    if (sender->saldo >= valor) {
        sender->saldo -= valor;
        receiver->saldo += valor;
    }

    pthread_mutex_unlock(&receiver->mutex);
    pthread_mutex_unlock(&sender->mutex);

    pthread_mutex_unlock(&transfer_mutex);

    printf("Transferência concluída com sucesso!\n");
    printf("Saldo de c1: %d\n", from.saldo);
    printf("Saldo de c2: %d\n", to.saldo);

    return NULL;
}

int main() {
    pthread_t threads[100]; // Array para armazenar threads
    int i;

    // Inicializa os mutexes
    pthread_mutex_init(&from.mutex, NULL);
    pthread_mutex_init(&to.mutex, NULL);
    pthread_mutex_init(&transfer_mutex, NULL);

    // Todas as contas começam com saldo 100
    from.saldo = 100;
    to.saldo = 100;

    printf("Transferindo 10 de from para to\n");
    valor = 10;
    for (i = 0; i < 50; i++) {
        if (pthread_create(&threads[i], NULL, transferencia, (void*[]){&from, &to}) != 0) {
            perror("pthread_create");
            exit(2);
        }
    }

    printf("Transferindo 5 de to para from\n");
    valor = 5;
    for (i = 50; i < 100; i++) {
        if (pthread_create(&threads[i], NULL, transferencia, (void*[]){&to, &from}) != 0) {
            perror("pthread_create");
            exit(2);
        }
    }

    // Espera por todas as threads
    for (i = 0; i < 100; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(3);
        }
    }

    // Destroi os mutexes
    pthread_mutex_destroy(&from.mutex);
    pthread_mutex_destroy(&to.mutex);
    pthread_mutex_destroy(&transfer_mutex);

    printf("Transferências concluídas e memória liberada.\n");

    return 0;
}

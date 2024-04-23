#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4   // Definindo o número de threads
#define MAT_SIZE 4      // Tamanho da matriz e do vetor

// Estrutura para armazenar os dados para cada thread
typedef struct {
    int id;             // ID da thread
    int size;           // Tamanho da matriz
    int *vector;        // Ponteiro para o vetor
    int (*matrix)[MAT_SIZE]; // Ponteiro para a matriz
    int *result;        // Ponteiro para o vetor de resultado
} thread_data;

// A função que cada thread vai executar
void *multiply(void *arg) {
    thread_data *data = (thread_data *) arg;
    int start = data->id * (data->size / NUM_THREADS);
    int end = start + (data->size / NUM_THREADS);

    for (int i = start; i < end; i++) {
        data->result[i] = 0;
        for (int j = 0; j < data->size; j++) {
            data->result[i] += data->matrix[i][j] * data->vector[j];
        }
    }

    pthread_exit(NULL);
}

int main() {
    int matrix[MAT_SIZE][MAT_SIZE] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    int vector[MAT_SIZE] = {2, 3, 5, 7}; // Novo vetor de exemplo
    int result[MAT_SIZE] = {0};

    pthread_t threads[NUM_THREADS];
    thread_data data[NUM_THREADS];

    // Criando threads
    for (int i = 0; i < NUM_THREADS; i++) {
        data[i].id = i;
        data[i].size = MAT_SIZE;
        data[i].vector = vector;
        data[i].matrix = matrix;
        data[i].result = result;
        int rc = pthread_create(&threads[i], NULL, multiply, (void *) &data[i]);
        if (rc) {
            printf("Erro ao criar thread: %d\n", rc);
            exit(-1);
        }
    }

    // Aguardando as threads terminarem
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Exibindo o vetor resultado
    printf("Vetor resultado:\n");
    for (int i = 0; i < MAT_SIZE; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    pthread_exit(NULL);
}

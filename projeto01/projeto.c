#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_PESSOAS 104

typedef struct {
    int tempo_chegada;
    int direcao;
} Pessoa;

int direcao_atual = -1; // -1 indica que a escada está parada
sem_t sem_escada;
int ultimo_momento = 0;

void *pessoa_thread(void *arg) {
    Pessoa *pessoa = (Pessoa *)arg;
    
    sleep(pessoa->tempo_chegada);
    
    sem_wait(&sem_escada);
    if (direcao_atual == -1 || direcao_atual == pessoa->direcao) {
        direcao_atual = pessoa->direcao;
        ultimo_momento = pessoa->tempo_chegada + 10;
    }
    sem_post(&sem_escada);
    
    return NULL;
}

int main() {
    int n;
    Pessoa pessoas[MAX_PESSOAS];
    pthread_t threads[MAX_PESSOAS];
    FILE *entrada, *saida;

    // Abre o arquivo de entrada
    entrada = fopen("entrada.txt", "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    // Abre o arquivo de saída
    saida = fopen("saida.txt", "w");
    if (saida == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        fclose(entrada);
        return 1;
    }

    sem_init(&sem_escada, 0, 1);

    // Lê o número de pessoas do arquivo de entrada
    fscanf(entrada, "%d", &n);
    
    // Lê os dados de cada pessoa do arquivo de entrada
    for (int i = 0; i < n; i++) {
        fscanf(entrada, "%d %d", &pessoas[i].tempo_chegada, &pessoas[i].direcao);
    }

    fclose(entrada);

    // Cria uma thread para cada pessoa
    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, pessoa_thread, (void *)&pessoas[i]);
    }

    // Aguarda todas as threads terminarem
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    // Escreve o último momento em que a escada parou no arquivo de saída
    fprintf(saida, "%d\n", ultimo_momento);

    fclose(saida);

    sem_destroy(&sem_escada);

    return 0;
}

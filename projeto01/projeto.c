#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_PESSOAS 104

typedef struct {
    int tempoDeChegada;
    int direcao;
} Pessoa;

int direcaoAtual = -1; // -1 indica que a escada está parada
sem_t semEscada;
int ultimoMomento = 0;

void *threadPessoa(void *arg) {
    Pessoa *pessoa = (Pessoa *)arg;

    sleep(pessoa->tempoDeChegada);

    sem_wait(&semEscada);
    if (direcaoAtual == -1 || direcaoAtual == pessoa->direcao) {
        direcaoAtual = pessoa->direcao;
        ultimoMomento = pessoa->tempoDeChegada + 10;
    }
    sem_post(&semEscada);

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

    sem_init(&semEscada, 0, 1);

    // Lê o número de pessoas do arquivo de entrada
    fscanf(entrada, "%d", &n);

    // Lê os dados de cada pessoa do arquivo de entrada
    for (int i = 0; i < n; i++) {
        fscanf(entrada, "%d %d", &pessoas[i].tempoDeChegada, &pessoas[i].direcao);
    }

    fclose(entrada);

    // Cria uma thread para cada pessoa
    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, threadPessoa, (void *) &pessoas[i]);
    }

    // Aguarda todas as threads terminarem
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    // Escreve o último momento em que a escada parou no arquivo de saída
    fprintf(saida, "%d\n", ultimoMomento);

    fclose(saida);

    sem_destroy(&semEscada);

    return 0;
}

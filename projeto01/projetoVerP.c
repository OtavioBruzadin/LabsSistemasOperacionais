#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h> // Para as permissões de acesso à memória compartilhada

#define SHM_NAME "/escada_shm"
#define SEM_NAME "/escada_sem"


typedef struct {
    int direcaoAtual;
    int ultimoMomento;
} EstadoEscada;

void simula_pessoa(int tempoChegada, int direcao) {
    sleep(tempoChegada);

    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    EstadoEscada* estado = (EstadoEscada*)mmap(0, sizeof(EstadoEscada), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    sem_t* sem = sem_open(SEM_NAME, 0);

    sem_wait(sem);
    if (estado->direcaoAtual == -1 || estado->direcaoAtual == direcao) {
        estado->direcaoAtual = direcao;
        estado->ultimoMomento = tempoChegada + 10;
    }
    sem_post(sem);

    munmap(estado, sizeof(EstadoEscada));
    close(shm_fd);
    sem_close(sem);
}

int main() {
    FILE *inputFile = fopen("entrada.txt", "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    int n;
    fscanf(inputFile, "%d", &n);

    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(EstadoEscada));
    EstadoEscada* estado = (EstadoEscada*)mmap(0, sizeof(EstadoEscada), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    estado->direcaoAtual = -1;
    estado->ultimoMomento = 0;
    munmap(estado, sizeof(EstadoEscada));
    close(shm_fd);

    sem_t* sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);

    for (int i = 0; i < n; ++i) {
        int tempoChegada, direcao;
        fscanf(inputFile, "%d %d", &tempoChegada, &direcao);
        if (fork() == 0) {
            simula_pessoa(tempoChegada, direcao);
            exit(0);
        }
    }

    fclose(inputFile);

    for (int i = 0; i < n; ++i) {
        wait(NULL);
    }

    shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    estado = (EstadoEscada*)mmap(0, sizeof(EstadoEscada), PROT_READ, MAP_SHARED, shm_fd, 0);

    FILE *outputFile = fopen("saida2.txt", "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        return 1;
    }

    fprintf(outputFile, "%d\n", estado->ultimoMomento);
    fclose(outputFile);

    munmap(estado, sizeof(EstadoEscada));
    close(shm_fd);

    shm_unlink(SHM_NAME);
    sem_close(sem);
    sem_unlink(SEM_NAME);

    return 0;
}

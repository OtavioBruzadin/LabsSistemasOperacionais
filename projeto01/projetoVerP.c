#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>

int momentoChegada = 0;

// Função para criar um processo filho que atualiza o momento de chegada
void criarProcesso(int *momentoChegada, int t) {
    pid_t pid;
    int fd[2];

    // Cria um pipe para comunicação entre processos
    if (pipe(fd) < 0) {
        exit(0);
    }

    // Cria um novo processo filho
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork failed");
    } else if (pid == 0) {
        // Processo filho: escreve o novo momento de chegada no pipe
        close(fd[0]); // Fecha a extremidade de leitura do pipe
        *momentoChegada = t; // Atualiza o momento de chegada
        write(fd[1], momentoChegada, sizeof(int)); // Escreve o momento de chegada no pipe
        close(fd[1]); // Fecha a extremidade de escrita do pipe
        exit(0);
    } else {
        // Processo pai: lê o novo momento de chegada do pipe
        close(fd[1]); // Fecha a extremidade de escrita do pipe
        wait(NULL); // Aguarda o término do processo filho
        read(fd[0], momentoChegada, sizeof(int)); // Lê o novo momento de chegada do pipe
        close(fd[0]); // Fecha a extremidade de leitura do pipe
    }
}

// Função para processar as pessoas nas filas
void processoPessoas(int filaPessoas[], int filaInicial0[], int filaInicial1[], int direcao) {
    int lugarFila[] = {0, 0}; // Índices para percorrer as filas
    criarProcesso(&momentoChegada, filaInicial0[0]); // Inicia o processo com o primeiro tempo de chegada
    int direcaoAux = direcao; // Direção atual

    while (lugarFila[0] < filaPessoas[0] || lugarFila[1] < filaPessoas[1]) {
        // Verifica qual fila tem a próxima pessoa a entrar na escada
        if ((filaInicial0[lugarFila[0]] < filaInicial1[lugarFila[1]] && lugarFila[0] < filaPessoas[0]) || filaPessoas[1] == 0 || filaPessoas[1] == lugarFila[1]) {
            // Se a próxima pessoa na fila 0 chegar antes da próxima na fila 1, ou se a fila 1 estiver vazia
            if (filaInicial0[lugarFila[0]] >= momentoChegada) {
                // Se a próxima pessoa na fila 0 chegar após o momento atual, atualiza o momento de chegada e avança na fila
                criarProcesso(&momentoChegada, filaInicial0[lugarFila[0]] + 10);
                lugarFila[0]++;
                direcaoAux = 0; // Define a direção como 0 (para cima)
            }

            if (lugarFila[0] + lugarFila[1] == 0) {
                // Se não há pessoas em nenhuma fila, atualiza o momento de chegada e avança uma unidade de tempo
                criarProcesso(&momentoChegada, momentoChegada + 10);
                lugarFila[0]++;
            }

            if (filaInicial0[lugarFila[0]] <= momentoChegada && lugarFila[0] < filaPessoas[0]) {
                // Se a próxima pessoa na fila 0 já está disponível e ainda há pessoas na fila 0
                if (direcaoAux == 1) {
                    // Se a direção anterior era para baixo, ajusta o tempo de chegada da pessoa anterior
                    while (filaInicial0[lugarFila[0]] <= momentoChegada && lugarFila[0] < filaPessoas[0]) {
                        lugarFila[0]++;
                    }
                    filaInicial0[lugarFila[0] - 1] = momentoChegada;
                    criarProcesso(&momentoChegada, momentoChegada + 10);
                }
                while (filaInicial0[lugarFila[0]] <= momentoChegada && lugarFila[0] < filaPessoas[0]) {
                    // Avança na fila 0 atualizando o momento de chegada para cada pessoa
                    criarProcesso(&momentoChegada, momentoChegada + (filaInicial0[lugarFila[0]] - filaInicial0[lugarFila[0] - 1]));
                    lugarFila[0]++;
                }
                direcaoAux = 0; // Define a direção como 0 (para cima)
            }
        } else if ((filaInicial0[lugarFila[0]] > filaInicial1[lugarFila[1]] && lugarFila[1] < filaPessoas[1]) || filaPessoas[0] == 0 || filaPessoas[0] == lugarFila[0]) {
            // Se a próxima pessoa na fila 1 chegar antes da próxima na fila 0, ou se a fila 0 estiver vazia
            if (filaInicial1[lugarFila[1]] > momentoChegada) {
                // Se a próxima pessoa na fila 1 chegar após o momento atual, atualiza o momento de chegada e avança na fila
                criarProcesso(&momentoChegada, filaInicial1[lugarFila[1]] + 10);
                lugarFila[1]++;
                direcaoAux = 1; // Define a direção como 1 (para baixo)
            }

            if (lugarFila[0] + lugarFila[1] == 0) {
                // Se não há pessoas em nenhuma fila, atualiza o momento de chegada e avança uma unidade de tempo
                criarProcesso(&momentoChegada, momentoChegada + 10);
                lugarFila[1]++;
            }

            if (filaInicial1[lugarFila[1]] <= momentoChegada && lugarFila[1] < filaPessoas[1]) {
                // Se a próxima pessoa na fila 1 já está disponível e ainda há pessoas na fila 1
                if (direcaoAux == 0) {
                    // Se a direção anterior era para cima, ajusta o tempo de chegada da pessoa anterior
                    while (filaInicial1[lugarFila[1]] <= momentoChegada && lugarFila[1] < filaPessoas[1]) {
                        lugarFila[1]++;
                    }
                    filaInicial1[lugarFila[1] - 1] = momentoChegada;
                    criarProcesso(&momentoChegada, momentoChegada + 10);
                }
                while (filaInicial1[lugarFila[1]] <= momentoChegada && lugarFila[1] < filaPessoas[1]) {
                    // Avança na fila 1 atualizando o momento de chegada para cada pessoa
                    criarProcesso(&momentoChegada, momentoChegada + (filaInicial1[lugarFila[1]] - filaInicial1[lugarFila[1] - 1]));
                    lugarFila[1]++;
                }
                direcaoAux = 1; // Define a direção como 1 (para baixo)
            }
        }
    }
}

int main() {
    FILE *file = fopen("entrada.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo de entrada");
        return 1;
    }

    FILE *saida = fopen("saida2.txt", "w");
    if (saida == NULL) {
        perror("Erro ao criar o arquivo de saída");
        fclose(file);
        return 1;
    }

    int n, direcao;
    fscanf(file, "%d", &n);

    int *filaInicial0 = mmap(NULL, n * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int *filaInicial1 = mmap(NULL, n * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int filaPessoas[] = {0, 0};

    // Lê os dados do arquivo de entrada e preenche as filas iniciais
    while (filaPessoas[0] + filaPessoas[1] < n) {
        int aux;
        fscanf(file, "%d", &aux);
        int direcaoAux;
        fscanf(file, "%d", &direcaoAux);

        if (filaPessoas[0] + filaPessoas[1] == 0) {
            direcao = direcaoAux;
        }

        if (direcaoAux == 0) {
            filaInicial0[filaPessoas[0]] = aux;
            filaPessoas[0]++;
        } else {
            filaInicial1[filaPessoas[1]] = aux;
            filaPessoas[1]++;
        }
    }

    // Processa as pessoas nas filas
    processoPessoas(filaPessoas, filaInicial0, filaInicial1, direcao);

    // Escreve o tempo de saída da escada rolante no arquivo de saída
    fprintf(saida, "Tempo de saída da escada rolante: %d\n", momentoChegada);

    // Fecha os arquivos e desfaz o mapeamento da memória
    fclose(file);
    fclose(saida);
    munmap(filaInicial0, n * sizeof(int));
    munmap(filaInicial1, n * sizeof(int));

    return 0;
}

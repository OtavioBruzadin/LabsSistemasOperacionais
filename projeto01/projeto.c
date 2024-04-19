#include <stdio.h>
#include <pthread.h>

// Definindo o número máximo de pessoas na fila
#define MAX_PESSOA 1000

// Definição da estrutura para representar uma pessoa na fila
typedef struct {
    int momentoChegada; // Momento em que a pessoa chegou à fila
    int direcao; // Direção para onde a pessoa se dirige (0 para cima, 1 para baixo)
} Pessoa;

// Definição da estrutura para representar a fila de pessoas
typedef struct {
    Pessoa filaInicial0[MAX_PESSOA]; // Fila de pessoas que vão para cima
    int count0; // Número de pessoas na fila que vão para cima
    Pessoa filaInicial1[MAX_PESSOA]; // Fila de pessoas que vão para baixo
    int count1; // Número de pessoas na fila que vão para baixo
} FilaPessoa;

// Variável global que representa o momento de referência, inicializada com 0
int referencia = 0;

// Função executada por cada thread que representa uma pessoa na fila
void* threadPessoa(void* args) {
    // Convertendo o argumento para o tipo FilaPessoa
    FilaPessoa* filaPessoa = (FilaPessoa *) args;
    Pessoa primeira; // Variável para representar a primeira pessoa a ser processada

    // Definindo a primeira pessoa com base na menor chegada em ambas as filas
    if (filaPessoa->count0 == 0) {
        primeira = filaPessoa->filaInicial1[0];
    }
    else if (filaPessoa->count1 == 0){
         primeira = filaPessoa->filaInicial0[0];
    }
    else {
        if (filaPessoa->filaInicial0[0].momentoChegada < filaPessoa->filaInicial1[0].momentoChegada) {
            primeira = filaPessoa->filaInicial0[0];
        } else {
            primeira = filaPessoa->filaInicial1[0];
        }
    }

    int aux0 = 0, aux1 = 0;

    // Loop principal para processar todas as pessoas na fila
    while (aux0 < filaPessoa->count0 || aux1 < filaPessoa->count1) {
        
        // Direção 0 para direção 1
        if (primeira.direcao == 0) {
            // Se ainda houver pessoas na fila 0 e a pessoa puder entrar na escada ou a fila 1 estiver vazia
            if ((aux0 < filaPessoa->count0 && (filaPessoa->filaInicial0[aux0].momentoChegada <= referencia) || (filaPessoa->filaInicial0[aux0].momentoChegada > referencia && filaPessoa->filaInicial0[aux0].momentoChegada < filaPessoa->filaInicial1[aux1].momentoChegada)) || aux1 == filaPessoa->count1) {
                primeira = filaPessoa->filaInicial0[aux0];               
                ++aux0;   
            // Se o tempo de chegada da pessoa for maior que o tempo de referência ou a fila 0 estiver vazia
            } else if (filaPessoa->filaInicial0[aux0].momentoChegada > referencia || aux0 == filaPessoa->count0) {
                // Muda a direção para a fila 1
                primeira = filaPessoa->filaInicial1[aux1];
                if (referencia > primeira.momentoChegada) primeira.momentoChegada = referencia;
                ++aux1;
                // Atualiza o momento de chegada para as próximas pessoas na fila 1
                int i = aux1;
                while (referencia > filaPessoa->filaInicial1[i].momentoChegada && i < filaPessoa->count1) {
                    filaPessoa->filaInicial1[i].momentoChegada = referencia;
                    ++i;
                }
            } 
        // Direção 1 para direção 0
        } else if (primeira.direcao == 1) {
            // Se ainda houver pessoas na fila 1 e a pessoa puder entrar na escada ou a fila 0 estiver vazia
            if ((aux1 < filaPessoa->count1 && filaPessoa->filaInicial1[aux1].momentoChegada <= referencia || (filaPessoa->filaInicial1[aux1].momentoChegada > referencia && filaPessoa->filaInicial1[aux1].momentoChegada < filaPessoa->filaInicial0[aux0].momentoChegada)) || aux0 == filaPessoa->count0) {
                primeira = filaPessoa->filaInicial1[aux1]; 
                ++aux1;
            // Se o tempo de chegada da pessoa for maior que o tempo de referência ou a fila 1 estiver vazia
            } else if (filaPessoa->filaInicial1[aux1].momentoChegada > referencia || aux1 == filaPessoa->count1) {
                // Muda a direção para a fila 0
                primeira = filaPessoa->filaInicial0[aux0];
                if (referencia > primeira.momentoChegada) primeira.momentoChegada = referencia;
                ++aux0;
                // Atualiza o momento de chegada para as próximas pessoas na fila 0
                int i = aux0;
                while (referencia > filaPessoa->filaInicial0[i].momentoChegada && i < filaPessoa->count0) {
                    filaPessoa->filaInicial0[i].momentoChegada = referencia;
                    ++i;
                }                
            }
        }   
        // Atualiza o momento de referência para o próximo momento de chegada
        referencia = primeira.momentoChegada + 10;
    }
    return NULL;
}

int main() {
    pthread_t thread_id;

    // Abrir o arquivo para leitura
    FILE *file = fopen("entrada.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Número de pessoas
    int n;
    Pessoa pessoa;
    fscanf(file, "%d", &n);

    Pessoa filaInicial0[MAX_PESSOA]; // Fila de pessoas que vão para cima
    Pessoa filaInicial1[MAX_PESSOA]; // Fila de pessoas que vão para baixo

    int count0 = 0, count1 = 0;

    // Ler todas as pessoas do arquivo
    for (int i = 0; i < n; ++i) {
        fscanf(file, "%d %d", &pessoa.momentoChegada, &pessoa.direcao);
        if (pessoa.direcao == 0) filaInicial0[count0++] = pessoa;
        else filaInicial1[count1++] = pessoa;        
    }

    // Fechar o arquivo após a leitura
    fclose(file);

    // Configurar os argumentos para a thread
    FilaPessoa filaPessoa;

    for (int i = 0; i < count0; i++){
         filaPessoa.filaInicial0[i] = filaInicial0[i];
    }

    filaPessoa.count0 = count0;

    for (int i = 0; i < count1; i++) {
        filaPessoa.filaInicial1[i] = filaInicial1[i];
    }

    filaPessoa.count1 = count1;

    // Criar a thread para processar as pessoas na fila
    pthread_create(&thread_id, NULL, threadPessoa, (void *) &filaPessoa);

    // Aguardar a conclusão da thread
    pthread_join(thread_id, NULL);

    // Abrir o arquivo de saída para escrita
    FILE *saida = fopen("saida.txt", "w");
    if (saida == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        return 1;
    }

    // Escrever o valor de referencia no arquivo de saída
    fprintf(saida, "Tempo de saída da escada rolante: %d\n", referencia);

    // Fechar o arquivo de saída
    fclose(saida);

    return 0;
}

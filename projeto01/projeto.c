#include <stdio.h>
#include <pthread.h>
#define MAX_PESSOA 100

typedef struct {
    int momentoChegada;
    int direcao;
} Pessoa;


typedef struct {
    Pessoa filaInicial0[MAX_PESSOA];
    int count0;
    Pessoa filaInicial1[MAX_PESSOA];
    int count1;
} FilaPessoa;


int referencia = 0;

void* threadPessoa(void* args) {
    FilaPessoa* filaPessoa = (FilaPessoa *) args;
    Pessoa primeira;

    // Define o primeiro valor;
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

    while (aux0 < filaPessoa->count0 || aux1 < filaPessoa->count1) {
        
        // direção 0 para a 1
        if (primeira.direcao == 0) {

            if ((aux0 < filaPessoa->count0 && (filaPessoa->filaInicial0[aux0].momentoChegada <= referencia) || (filaPessoa->filaInicial0[aux0].momentoChegada > referencia && filaPessoa->filaInicial0[aux0].momentoChegada < filaPessoa->filaInicial1[aux1].momentoChegada)) || aux1 == filaPessoa->count1) {
                primeira = filaPessoa->filaInicial0[aux0];               
                ++aux0;   

            // se o momento de chegada for maior que o tempo de saída ou a fila tiver sido completamente utilizada 
            } else if (filaPessoa->filaInicial0[aux0].momentoChegada > referencia || aux0 == filaPessoa->count0) {
                // muda a direção da escada rolante
                primeira = filaPessoa->filaInicial1[aux1];
                if (referencia > primeira.momentoChegada) primeira.momentoChegada = referencia;
                ++aux1;

                // se o tempo de saída for maior que os seguintes
                int i = aux1;
                while (referencia > filaPessoa->filaInicial1[i].momentoChegada && i < filaPessoa->count1) {
                    filaPessoa->filaInicial1[i].momentoChegada = referencia;
                    ++i;
                }
            } 
          // direção 1 para a 0
        } else if (primeira.direcao == 1) {
            
            // segue na mesma direção se o momento de chegada for menor que o último tempo de saída ou estiver imediatamente ao lado do anterior
            if ((aux1 < filaPessoa->count1 && filaPessoa->filaInicial1[aux1].momentoChegada <= referencia || (filaPessoa->filaInicial1[aux1].momentoChegada > referencia && filaPessoa->filaInicial1[aux1].momentoChegada < filaPessoa->filaInicial0[aux0].momentoChegada)) || aux0 == filaPessoa->count0) {
                primeira = filaPessoa->filaInicial1[aux1]; 
                ++aux1;

            // se o momento de chegada for maior que o tempo de saída ou a fila tiver sido completamente utilizada 
            } else if (filaPessoa->filaInicial1[aux1].momentoChegada > referencia || aux1 == filaPessoa->count1) {
                // muda a direção da escada rolante, considerando um novo momento de chegada com base no tempo de espera
                primeira = filaPessoa->filaInicial0[aux0];
                if (referencia > primeira.momentoChegada) primeira.momentoChegada = referencia;
                ++aux0;

                // se o tempo de saída for maior que os seguintes
                int i = aux0;
                while (referencia > filaPessoa->filaInicial0[i].momentoChegada && i < filaPessoa->count0) {
                    filaPessoa->filaInicial0[i].momentoChegada = referencia;
                    ++i;
                }                
            }
        }   
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

    // número de pessoas
    int n;
    Pessoa pessoa;
    fscanf(file, "%d", &n);

    Pessoa filaInicial0[MAX_PESSOA];
    Pessoa filaInicial1[MAX_PESSOA];

    int count0 = 0, count1 = 0;

    // Ler todos os valores do arquivo
    for (int i = 0; i < n; ++i) {
        fscanf(file, "%d %d", &pessoa.momentoChegada, &pessoa.direcao);
        if (pessoa.direcao == 0) filaInicial0[count0++] = pessoa;
        else filaInicial1[count1++] = pessoa;        
    }

    // Fechar o arquivo após a leitura
    fclose(file);

    // Configurando os argumentos para a thread
    FilaPessoa filaPessoa;

    for (int i = 0; i < count0; i++){
         filaPessoa.filaInicial0[i] = filaInicial0[i];
    }

    filaPessoa.count0 = count0;

    for (int i = 0; i < count1; i++) {
        filaPessoa.filaInicial1[i] = filaInicial1[i];
    }

    filaPessoa.count1 = count1;

    pthread_create(&thread_id, NULL, threadPessoa, (void *) &filaPessoa);

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

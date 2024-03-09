#include <stdio.h>      // Inclui a biblioteca padrão de entrada e saída em C
#include <stdlib.h>     // Inclui a biblioteca padrão de C
#include <unistd.h>     // Inclui a biblioteca que fornece acesso às funções do sistema operacional relacionadas a operações de sistema
#include <sys/wait.h>  // Inclui a biblioteca que contém declarações de funções e constantes associadas à espera de processos filhos no sistema
#include <string.h>     // Inclui a biblioteca de manipulação de strings em C

#define BUFFER_SIZE 256  // Define o tamanho do buffer

int main() {
    int pipefd[2];                      // Declara um array para armazenar descritores de arquivo do pipe
    pid_t pid;                          // Declara uma variável para armazenar o ID do processo
    char message_to_child[BUFFER_SIZE]; // Declara uma matriz para armazenar a mensagem enviada para o processo filho
    char message_to_parent[BUFFER_SIZE];// Declara uma matriz para armazenar a mensagem enviada para o processo pai
    char concatenated_message[BUFFER_SIZE * 2]; // Declara uma matriz para armazenar a mensagem concatenada

    // Cria um pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");   // Imprime uma mensagem de erro se a função pipe() falhar
        exit(EXIT_FAILURE); // Termina o programa com status de falha
    }

    // Cria um novo processo filho
    pid = fork();

    // Verifica se a criação do processo filho falhou
    if (pid == -1) {
        perror("fork");   // Imprime uma mensagem de erro se a função fork() falhar
        exit(EXIT_FAILURE); // Termina o programa com status de falha
    }

    // Código do processo filho
    if (pid == 0) {
        close(pipefd[1]);   // Fecha o descritor de arquivo de escrita do pipe no processo filho

        // Lê a mensagem enviada pelo processo pai através do pipe
        read(pipefd[0], message_to_child, BUFFER_SIZE);
        printf("Child process received message: %s\n", message_to_child); // Imprime a mensagem recebida do processo pai

        // Escreve uma mensagem de resposta para o processo pai através do pipe
        char reply[] = "Message received by child process!";
        write(pipefd[0], reply, strlen(reply) + 1);

        close(pipefd[0]); // Fecha o descritor de arquivo de leitura do pipe no processo filho
    }
        // Código do processo pai
    else {
        close(pipefd[0]); // Fecha o descritor de arquivo de leitura do pipe no processo pai

        // Solicita ao usuário que insira uma mensagem para enviar ao processo filho
        printf("Enter message to send to child process: ");
        fgets(message_to_parent, BUFFER_SIZE, stdin);
        message_to_parent[strcspn(message_to_parent, "\n")] = '\0'; // Remove o caractere de nova linha da mensagem lida

        // Escreve a mensagem para o processo filho através do pipe
        write(pipefd[1], message_to_parent, strlen(message_to_parent) + 1);

        // Lê a resposta do processo filho através do pipe
        read(pipefd[1], message_to_parent, BUFFER_SIZE);
        printf("Parent process received reply: %s\n", message_to_parent); // Imprime a resposta recebida do processo filho

        // Solicita ao usuário que insira uma string adicional para concatenar com a resposta do processo filho
        printf("Enter additional string to concatenate: ");
        fgets(concatenated_message, BUFFER_SIZE, stdin);
        concatenated_message[strcspn(concatenated_message, "\n")] = '\0'; // Remove o caractere de nova linha da string lida

        // Concatena a string adicional com a resposta do processo filho
        strcat(message_to_parent, concatenated_message);
        printf("Concatenated message: %s\n", message_to_parent); // Imprime a mensagem concatenada

        close(pipefd[1]); // Fecha o descritor de arquivo de escrita do pipe no processo pai
        wait(NULL);        // Aguarda a conclusão do processo filho
    }

    return 0; // Retorna 0 para indicar que o programa foi executado com sucesso
}


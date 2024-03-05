#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 256

int main() {
    int pipefd[2];
    pid_t pid;
    char message_to_child[BUFFER_SIZE];
    char message_to_parent[BUFFER_SIZE];
    char concatenated_message[BUFFER_SIZE * 2];

 
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

 
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(pipefd[1]);

        
        read(pipefd[0], message_to_child, BUFFER_SIZE);
        printf("Child process received message: %s\n", message_to_child);

       
        char reply[] = "Message received by child process!";
        write(pipefd[0], reply, strlen(reply) + 1);

        close(pipefd[0]); 
    } else {
        close(pipefd[0]); 

     
        printf("Enter message to send to child process: ");
        fgets(message_to_parent, BUFFER_SIZE, stdin);
        message_to_parent[strcspn(message_to_parent, "\n")] = '\0'; 
        write(pipefd[1], message_to_parent, strlen(message_to_parent) + 1);

    
        read(pipefd[1], message_to_parent, BUFFER_SIZE);
        printf("Parent process received reply: %s\n", message_to_parent);

    
        printf("Enter additional string to concatenate: ");
        fgets(concatenated_message, BUFFER_SIZE, stdin);
        concatenated_message[strcspn(concatenated_message, "\n")] = '\0'; 

        strcat(message_to_parent, concatenated_message);

        printf("Concatenated message: %s\n", message_to_parent);

        close(pipefd[1]);

       
        wait(NULL);
    }

    return 0;
}

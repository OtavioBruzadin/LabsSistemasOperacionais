Conclusão Lab Sistemas Operacionais

O objetivo desta atividade laboratorial foi a criação de um programa em C que nos permita ver como a sincronia entre as tarefas é realizada por meio de troca de mensagens e memória compartilhada.

![Imagem do WhatsApp de 2024-03-09 à(s) 14 32 57_551a95bb](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/89026599/b0ebfa84-f930-47cc-a562-45f247788777)

![Imagem do WhatsApp de 2024-03-09 à(s) 14 33 06_9bbf4abf](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/89026599/9eb7857c-fe2c-4059-be75-8cda8cb65765)

Neste código é possível perceber a inclusão de novas bibliotecas para que o programa em C possa funcionar corretamente, dentre elas estão ***stdlib.h***, ***unistd.h***, ***sys/wait.h*** e ***string.h*** além dessas bibliotecas também devemos definir um tamanho de *Buffer* máximo que neste caso foi definido como 256.

- **utdlib.h** contém funções de alocação de memória, controle de processos, etc.
- **unistd.h** é a biblioteca que fornece acesso as funções do sistema operacional relacionado às operações como *fork()*, *pipe()*, etc.
- **sys/wait.h** contém declarações de funções e constantes associadas à espera de processos filhos no sistema.
- **string.h** é a biblioteca de manipulação de *strings* em C.

Para o início da função *main()* devemos criar as variáveis *int pipefd[2]*, que possui a função de declarar um *array* de dois elementos e serve para armazenas os descritores de arquivo para um pipe; *pid_t pid*, que declara uma variável que armazena ID do processo, e a criação de três variáveis *char*, a **message_to child, message_to_parent** e **concatenated_message** estas três variáveis declaram respectivamente uma matriz para armazenamento da mensagem enviada pelo filho e pelo pai, e a declaração de uma matriz para armazenar a mensagem concatenada.

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/89026599/c7eb2ad4-94ce-4f6e-b524-9bd6639419f7)

A criação do *pipe* é feita com um *if (pipe(pipefd) == -1)*, esse código é feito para testar se a função pipe falhou. A função *pipe()* é usada para criar um pipe não nomeado, e os descritores do arquivo são armazenados no *array* **pipefd**. Caso o erro ocorra, é utilizada a função *perror("pipe")* que imprime uma mensagem de erro e indica que o erro foi no pipe, e a função *exit(EXIT_FAILURE)* encerra o programa com um estatus de falha.

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/89026599/c993a5c5-98fc-4301-ac3f-177f55b0b681)

Agora é necessário criar um novo processo filho utilizando a função *pid = fork()*, após essa linha de código, existirão dois processos em execução, o processo pai e o processo filho, onde o filho é uma cópia exata do pai.

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/89026599/8d3394fc-0602-415d-bb82-ce7931121d4f)

Após a criação do filho, precisamos verificar se sua criação não falhou, então utilizamos mais uma vez a função *if*, sua diferença é que ao invés de usarmos *pipe(pipefd)*, utilizamos o *pid*, e caso ocorra falhas na criação, a mensagem de erro irá indicar que foi no **Fork** e encerrará o programa também.

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/89026599/532f42db-f512-40bd-8e64-d7100746768e)

Com o código funcionando sem falhas até o momento, precisamos configurar o que o processo filho irá fazer. Assim, fazemos a verificação se ele está funcionando utilizando o mesmo comando *if (pid == 0)*, se sim, ele fecha o descritor de arquivo de escrita do pipe no processo filho *close(pipefd[1])*.

Após isso, ele lê a mensagem enviada pelo processo pai através do pipe, *read(pipefd[0], message_to_child, BUFFER_SIZE)*, e imprime a mensagem recebida pelo do processo pai *printf("Child process received message: $s\n", message_to_child)*

Em seguida o processo filho envia uma respota ao processo pai através do pipe, utilizando a função *char reply[] = "Message received by child process"*, a função *write(pipefd[0], reply, strlen(reply) + 1)* escreve a mensagem de resposta no pipe usando o descritor de arquivo de leitura *pipefd[0]*. O *strlen(reply) + 1* garante que a mensagem completa, incluindo o caractere nulo de terminação da string, seja escrita no pipe.

É utilizamos um *close(pipefd[0]* para fechar o descritor de arquivo de leitura do pipe no processo filho.

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/89026599/020523d2-ab2d-436f-a0a6-dc2db01b0621)

O código para do processo pai é similar ao do filho, ele inicia caso o *pid != 0*, e começa utilizando fechando o descritor de arquivo de leitura do pipe no processo pai com a função *close(pipefd[0])*.
Agora utilizamos a função *fgets(message_to_parent, BUFFER_SIZE, stdin)* para que o usuário escreva uma mensagem que será enviada para o filho, e *message_to_parent[strcspn(message_to_parent, "\n")] = '\0'* que serve para remover o caractere de nova linha da mensagem lida.

Com a função *write(pipefd[1], message_to_parent, strlen(message_to_parent) + 1)* é enviada a mensagem do processo pai para o processo filho através do pipe.

## Como compilar o programa:

Para compilar códigos em C, é necessário instalar o compilador gcc.
```bash
sudo dnf install gcc
```
Para instalar o editor nano devemos utilizar o seguinte comando:
```bash
sudo dnf install nano
```
Para criar e editar um arquivo `.c` utilizamos o seguinte comando:
```bash
nano lab.c
```
Após a criação e edição  para compilar, devemos utilizar o comando

```bash
gcc lab.c -o result
```
## Como executar o programa:

Para apresentar o resultado na tela, basta utilizarmos o comando abaixo

```bash
./result
```

---

## Comprovando a execução do programa:

O objetivo desta atividade laboratorial foi a criação de um programa em C que nos permita ver como a sincronia entre as tarefas é realizada por meio de troca de mensagens.
 
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

Com o código funcionando sem falhas até o momento, precisamos configurar o que o processo filho irá fazer. Assim, fazemos a verificação se ele está funcionando utilizando o mesmo comando if (pid == 0), se sim, ele fecha o descritor de arquivo de escrita do pipe no processo filho close(pipefd[1]).

Após isso, ele lê a mensagem enviada pelo processo pai através do pipe, read(pipefd[0], message_to_child, BUFFER_SIZE), e imprime a mensagem recebida pelo do processo pai printf("Child process received message: $s\n", message_to_child)

Em seguida o processo filho envia uma respota ao processo pai através do pipe, utilizando a função char reply[] = "Message received by child process", a função write(pipefd[0], reply, strlen(reply) + 1) escreve a mensagem de resposta no pipe usando o descritor de arquivo de leitura pipefd[0]. O strlen(reply) + 1 garante que a mensagem completa, incluindo o caractere nulo de terminação da string, seja escrita no pipe.

É utilizamos um close(pipefd[0] para fechar o descritor de arquivo de leitura do pipe no processo filho.

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/89026599/020523d2-ab2d-436f-a0a6-dc2db01b0621)

O código para do processo pai é similar ao do filho, ele inicia caso o pid != 0, e começa utilizando fechando o descritor de arquivo de leitura do pipe no processo pai com a função close(pipefd[0]).


Agora utilizamos a função fgets(message_to_parent, BUFFER_SIZE, stdin) para que o usuário escreva uma mensagem que será enviada para o filho, e message_to_parent[strcspn(message_to_parent, "\n")] = '\0' que serve para remover o caractere de nova linha da mensagem lida.

Com a função write(pipefd[1], message_to_parent, strlen(message_to_parent) + 1) é enviada a mensagem do processo pai para o processo filho através do pipe. E as próximas linhas de código são muito parecidas com o que ocorre com o processo filho.

Para a concatenção entre a mensagem do processo pai para o processo filho, é solicitado ao usuário que o mesmo insira uma string adicional para concatenar com a resposta enviada pelo processo filho é utilizado assim a função fgets(concatenated_message, BUFFER_SIZE, stdin) e para a remoção dos caracteres da nova linha da string lida é feita pela função concatenated_message[strcspn(concatenated_message, "\n")] = '\0'.
É necessário concatenar a string adicional com a resposta do processo filho usando o strcat(message_to_parent, concatenated_message) e assim é imprimir a mensagem concatenada.
Para finalizar devemos fechar o descritor de arquivo de escrita do pipe no processo pai e aguardar a conclusão do processo filho, devemos usar a função close(pipefd[1]) e wait(NULL) respectivamente.

Agora que o arquivo está pronto é necessário compilá-lo utilizando o GCC, utilizamos o comando *gcc **nome do arquivo** -o **nome após a compilação***, assim ficando como *gcc **lab02.c** -o **result***.
E para fazermos o teste é necessário utilizar o comando **./result**.

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/89026599/e09c31ab-1d9e-4c2e-804c-becdfa9aadb0)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/78da5c1d-bdd0-4121-b7c7-160cb0c0fdf3)

O resultado ocorreu conforme o esperado.








**Questões a serem respondidas**

- 1: Você é capaz de identificar os trechos executados por pai e filho?

Executado pelo pai = ![Imagem do WhatsApp de 2024-03-07 à(s) 15 34 41_efaae1f2](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/89026599/6e3aa889-92f7-4094-a1c0-3c4f5fbf20df)

Pois o *pid é maior que 0*

Executado pelo filho = ![Imagem do WhatsApp de 2024-03-07 à(s) 15 34 11_d0bc76f9](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/89026599/fb2eb9fc-dfa7-45c7-a2a7-b4c783e22abb)

Pois o *pid == 0*

- 2: Quantos processos serão criados?

![Imagem do WhatsApp de 2024-03-07 à(s) 14 34 38_5f5f1e1d](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/89026599/c80d5af8-c5ad-43f9-86e0-74a68296b311)

Serão criados 8 processos, pois devemos levar em consideração que o número total de processos criados é igual a 2^n, como é possivel perceber no print, existem 3 linhas de código com a função *fork()*, portanto será 2^3 = 8.

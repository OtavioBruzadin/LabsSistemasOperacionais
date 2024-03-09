Conclusão Lab Sistemas Operacionais

O objetivo desta atividade laboratorial foi a criação de um programa em C que nos permita ver como a sincronia entre as tarefas é realizada por meio de troca de mensagens e memória compartilhada.

![Imagem do WhatsApp de 2024-03-09 à(s) 14 32 57_551a95bb](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/89026599/b0ebfa84-f930-47cc-a562-45f247788777)

![Imagem do WhatsApp de 2024-03-09 à(s) 14 33 06_9bbf4abf](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/89026599/9eb7857c-fe2c-4059-be75-8cda8cb65765)

Neste código é possível perceber a inclusão de novas bibliotecas para que o programa em C possa funcionar corretamente, dentre elas estão ***stdlib.h***, ***unistd.h***, ***sys/wait.h*** e ***string.h*** além dessas bibliotecas também devemos definir um tamanho de *Buffer* máximo que neste caso foi definido como 256.

- **utdlib.h** contém funções de alocação de memória, controle de processos, etc.
- **unistd.h** é a biblioteca que fornece acesso as funções do sistema operacional relacionado às operações como *fork()*, *pipe()*, etc.
- **sys/wait.h** contém declarações de funções e constantes associadas à espera de processos filhos no sistema.
- **string.h** é a biblioteca de manipulação de *strings* em C.

Para o início da função *main()* devemos criar as variáveis *pipefd[2]*, que possui a função de declarar um *array* de dois elementos e serve para armazenas os descritores de arquivo para um pipe.

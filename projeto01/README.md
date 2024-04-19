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
nano projeto.c
```
Após a criação e edição  para compilar, devemos utilizar o comando

```bash
gcc projeto.c -o result -lpthread
```
## Como executar o programa:

Para apresentar o resultado na tela, basta utilizarmos o comando abaixo

```bash
./result
```

---


QUESTÕES A SEREM RESPONDIDAS:
 
1. Estratégia para evitar que duas pessoas acessem a escada rolante ao mesmo tempo:
   
    -THREADS:
   Dentro do looping principal a direção das pessoas é identificada, se a direção for 0, a pessoa só poderá entrar se ainda houver pessoas na fila 0 e o tempo de chegada da primeira pessoa na fila 0 for menor ou igual ao tempo de referência, ou se o tempo de chegada da primeira pessoa na fila 0 estiver entre o tempo de referência e o tempo de chegada da primeira pessoa na fila 1, ou se a fila 1 estiver vazia.
   
   Agora, se a direção for 1, a lógica será a mesma, mas considerando a fila 1 ao invés da fila 0.

   Assim após cada interação a referência é usada para o proximo "momentoChegada" para que a pessoa atenda as condições explicadas acima.

    -PROCESSOS:

   Estratégia para evitar que duas pessoas acessem a escada rolante ao mesmo tempo:
   
   Usamos um pipe de comunicação, a função criarProcesso utiliza um pipe para comunicação entre processos. O pipe é um mecanismo que permite a comunicação entre o processo pai e o processo filho. em seguida quando a função criarProcesso é chamada, um novo processo filho é criado usando a função fork(). Isso resulta em dois processos: o processo pai e o processo filho, eles utilizam justamente o pipe para comunicação, onde o pai eescreve o novo momento de chegada no pipe, e o filho lê esse valor. O filho atualiza o "momentoChegada" e o pai espera o processo do filho com a função "wait()".

   Essa abordagem garante que apenas uma pessoa entre na escada por vez, pois cada processo filho é responsável por atualizar o "momentoChegada", pois o o pipe garante que o momento de chegada seja atualizado de forma sequencial, permitindo que apenas uma pessoa entre na escada por vez.


2. Como garantir que somente uma das direções está ativa de cada vez:
   
    -THREADS:
   
    Essencialmente, o código alterna entre as direções (0 e 1) com base nas condições fornecidas, garantindo que apenas uma direção esteja ativa de cada vez.

    No início da função threadPessoa, a variável primeira é inicializada com a primeira pessoa da fila, a escolha é feita com base na pessoa que chegou primeiro em ambas as filas. Em seguida vem o looping, que rodará enquanto ainda houver pessoas em qualquer uma das filas.

    Já as condições de mudança seriam: Se a direção for 0 e não houver mais pessoas na fila que vai para essa mesma direção, ou se o tempo de chegada da próxima pessoa na fila que vai para cima for maior que o tempo de referência, ou se a fila que vai para cima estiver vazia, então a direção é alterada para 1. E para a direção 1 é essencialmente a mesma coisa, porém considerando a fila 1 ao invés da 0, e no final alternando para 0.


    -PROCESSOS:

   Como garantir que somente uma das direções está ativa de cada vez:

   A variável direcaoAux é usada para controlar a direção atual em que as pessoas estão se movendo na escada. Inicialmente, ela é inicializada com a direção fornecida pelo arquivo de entrada, em seguida o código verifica qual fila tem a próxima pessoa a entrar na escada. Isso é feito comparando os tempos de chegada das próximas pessoas em ambas as filas: Se a próxima pessoa na fila 0 chegar antes da próxima na fila 1 (ou se a fila 1 estiver vazia), a direção atual é definida como 0 .Se a próxima pessoa na fila 1 chegar antes da próxima na fila 0 (ou se a fila 0 estiver vazia), a direção atual é definida como 1.

   Quando a direção muda, o momento de chegada é ajustado de acordo. Isso é feito para garantir que as pessoas na fila correspondente aguardem o tempo adequado antes de entrar na escada. Alternando entre as direções com base nos tempos de chegada das próximas pessoas em cada fila, fazendo assim com que as pessoas entrem na escada na ordem apropriada, evitando a sobreposição ou o tempo de espera desnecessário.

3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.

  Implementação com Threads:

-Utiliza threads para representar cada pessoa na fila.
-Compartilha memória entre as threads para acessar e modificar as informações da fila.
-Pode ser mais leve em termos de recursos, pois as threads compartilham o mesmo espaço de endereço virtual.
-Menor sobrecarga de comunicação entre processos, já que não é necessário o uso explícito de mecanismos de comunicação, como pipes ou memória compartilhada.
  
  Implementação com Processos:

-Utiliza processos separados para processar as pessoas na fila.
-Cada processo tem sua própria cópia da memória, o que implica em menos preocupações com a sincronização de acesso à memória compartilhada.
-Mais robusta em termos de segurança e isolamento de dados, já que os processos têm espaços de endereçamento separados.
-Requer o uso de mecanismos explícitos de comunicação entre processos, como pipes ou memória compartilhada, para troca de dados entre os processos.

A escolha entre threads e processos depende das características específicas do problema, dos requisitos de desempenho e das considerações de segurança e robustez. Em geral, para este problema específico, a implementação com threads provavelmente seria mais eficiente, já que estamos lidando com um número relativamente pequeno de pessoas na fila, e desde que seja adequadamente sincronizada para evitar condições de corrida e outros problemas de concorrência, as threads mostram ser mais bem aproveitadas.



## Comprovando a execução do programa:
Prints versão utilizando processos:

![imagemSO1](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/77bd1ad8-171e-454a-9da5-45a72acd99ad)
![imagemSO2](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/dc440767-e1ec-432a-a1e9-0240654c3871)
![imagemSO3](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/88f1d440-54af-495a-861b-671a1ba6569c)
![imagemSO6](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/3566c794-888c-45ac-85e5-780532cebae0)
![imagemSO4](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/fed9ea18-fbc8-47bf-beae-908cec1ed66f)


Prints versão utilizando threads:

![imagemSO5](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/fc1cdc65-dd13-4e27-b524-3785bf6e1ede)
![imagemSO7](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/a6d2b20e-9472-4d02-af02-ac77694adf71)
![imagemSO4](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/fed9ea18-fbc8-47bf-beae-908cec1ed66f)
![imagemSO8](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/1be3464c-405f-4ef8-b949-b4a3356adf6b)

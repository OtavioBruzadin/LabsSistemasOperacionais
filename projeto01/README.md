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
nano projetoVerP.c
```
Após a criação e edição  para compilar, devemos utilizar o comando:

Para threads
```bash
gcc projeto.c -o result -lpthread -lrt
```

Para processos
```bash
gcc projetoVerP.c -o result -lpthread -lrt
```

## Como executar o programa:

Para incluir o exemplo, deve-se colocar dentro do arquivo entrada.txt, basta utilizarmos o comando:

```bash
nano entrada.txt
```

Para apresentar o resultado, basta utilizarmos o comando:

```bash
./result
```

O resultado de threads aparecerá no arquivo saida.txt, basta utilizarmos o comando:

```bash
nano saida.txt
```

O resultado de processos aparecerá no arquivo saida.txt, basta utilizarmos o comando:

```bash
nano saida2.txt
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

-Requer o uso de mecanismos explícitos de comunicação entre processos, como pipes, para troca de dados entre os processos.

A escolha entre threads e processos depende das características específicas do problema, dos requisitos de desempenho e das considerações de segurança e robustez. Em geral, para este problema específico, a implementação com threads seria mais eficiente, já que estamos lidando com um número relativamente pequeno de pessoas na fila, e desde que seja adequadamente sincronizada para evitar condições de corrida e outros problemas de concorrência, as threads mostram ser mais bem aproveitadas.



## Comprovando a execução do programa:
Prints versão utilizando processos:

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/8d4da809-8fab-49b7-b049-a3755f58b29a)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/2a1a775d-6e69-44f6-beec-9bfdb4d09c6b)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/f9c557a9-a474-4e35-ab5d-f9f11d800f45)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/ddd06fce-1f40-45aa-9d71-57fca56a9691)

E1

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/fa33b52a-023e-4902-9d63-01a863698314)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/a990407d-f35d-4b56-946f-2638899fa80d)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/a7859c41-578f-4e1d-9189-808ee8968a42)

E2

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/b5f27c6f-8a42-49c3-bff5-6d36ffe9b52b)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/7b43e01e-381b-40cd-856d-dc54eeb7dce7)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/bc3d6e48-7d6a-4822-b4fb-7374b86facc2)

E3

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/1b409fe8-123f-44f9-9660-dced1deb9b35)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/4bb9e9a8-b85e-490f-a158-155a103c48d5)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/47b53dfa-4cf5-453e-919f-b4ce06e26ccb)

E4

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/4b1be794-b2d5-41f2-b6f4-3530e14523eb)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/7c159df8-a27b-4417-9386-ff08c73c3155)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/81aa512c-c514-48b6-be0b-77139fcd18ba)

E5

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/148850e1-b6e0-4ff1-87ce-4dbc9da5a461)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/225e9008-e66c-479e-8838-aef5df1fc5d3)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/bdeb757a-09f4-4f95-822f-15ee5f49087d)

E9

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/b3869d35-1326-4d68-a1c7-3292f6883fcd)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/85dd4f8f-1a4b-49bb-a7dc-2b96c43475ea)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/b3ad9a40-721f-425a-8d39-3abe4f08c216)

E15

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/159c69c9-30f4-4f68-a38a-9f1ba2918434)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/9e0dede0-077a-4f68-b5ec-f5b3ea0c1f97)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/8d8ca70a-bee6-4fa0-9efe-d5c42570cd66)

Prints versão utilizando threads:

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/2b543d7d-5898-4e5f-8044-24e4e66c082a)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/bfc6dc2a-cd34-43a8-8e94-9126eec0f814)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/7e7e1a8f-2f56-490b-a575-ab9029acc456)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/ff968d25-7417-4313-bcfa-d75ce07c5fbc)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/417b97bc-4083-42cd-a3ec-dcc6ffc67973)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/d74899e4-8102-4b5e-b215-e4825df0fdd2)

E1

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/4ddd2dad-61d4-40a6-a4da-219e869de179)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/7233cc22-06b2-413f-899f-924cd88f2b34)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/9d784739-9b2b-42a9-9424-4b74d54262bc)

E2

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/d66eb112-de22-4218-84f6-8efe9d36bff2)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/477e5049-ff07-4798-b1d5-60cbc82a7a00)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/9df47d2a-8408-46f9-87f8-0442fd9264c3)

E3

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/da5bde76-89b2-4843-b775-79e911aaf3ed)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/a55ddf2e-41d6-456f-a56e-b7d931c65866)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/e52b83d8-0b45-4155-822a-906f967952e2)

E4

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/c5667ebd-24ab-4d91-8a7e-0c614d571dd9)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/fdfd5708-e18d-4f2b-8e04-e901039b35af)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/fa265fbf-ab70-4ae7-8e6c-d3bb33a0c473)

E5

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/472089bb-2d56-4e24-a36e-fab1bb2f37dd)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/7200f309-935a-4484-9f57-5c0f97e9658f)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/f9539eb2-9338-4d01-8669-10162953448d)

E9

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/19cfd9da-8937-4fde-b238-e575f3e565cc)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/c1578fd3-7605-4253-9a80-3d34068d756e)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/85e73ccc-2359-45d5-b7db-fa785d5c6838)

E15

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/538e8ad8-26fe-4e90-8269-7f88ebb16058)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/45aef23d-a429-453f-aad9-18479e584d1a)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/bb8679dc-a9eb-41da-8c13-9d3f1c9a38a2)

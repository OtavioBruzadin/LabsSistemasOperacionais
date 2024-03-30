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
    Para isso foi utilizado um semáforo (`sem_t sem_escada;`) para controlar o acesso à escada rolante. O semáforo é inicializado com o valor 1 (`sem_init(&sem_escada, 0, 1);`), indicando que, inicialmente, uma thread (pessoa) pode acessar a região crítica – neste caso, a escada rolante.
   
    Antes de uma thread acessar a escada rolante (modificar o estado da direção atual ou calcular o último momento), ela deve adquirir o semáforo usando `sem_wait(&sem_escada);`. Isso decrementa o valor do semáforo. Se o valor for 0, isso significa que outra thread já está acessando a escada rolante, e a thread atual será bloqueada até que o semáforo seja liberado (seu valor incrementado novamente) pela thread que está na região crítica.

    Após a thread realizar as operações necessárias (como entrar na escada rolante ou aguardar pela direção correta), ela libera o semáforo usando `sem_post(&sem_escada);`, permitindo que outra thread entre na região crítica. Este mecanismo garante que apenas uma thread por vez possa modificar o estado da escada rolante ou calcular o momento de sua utilização.


    -PROCESSOS:


2. Como garantir que somente uma das direções está ativa de cada vez:
    -THREADS:
    A direção atual da escada rolante é controlada pela variável global `int direcao_atual;`, que é inicialmente definida como -1, que demonstra que a escada está parada. A direção pode ser alterada para 0 (indicando uma direção) ou 1 (indicando a direção oposta) conforme a necessidade das pessoas que estão chegando.
   
   Dentro da função `pessoa_thread`, após adquirir o semáforo, a thread verifica se a direção atual da escada rolante corresponde à direção desejada pela pessoa (`if (direcao_atual == -1 || direcao_atual == pessoa->direcao)`). Se a direção for a mesma ou a escada estiver parada, a pessoa pode "entrar" na escada rolante, e a direção atual é atualizada para refletir a direção dessa pessoa.
   
   Essa checagem e atualização da direção acontecem dentro da região crítica protegida pelo semáforo, o que garante que apenas uma direção esteja ativa em qualquer momento, e uma mudança de direção só pode ocorrer se nenhuma outra pessoa estiver utilizando a escada rolante em uma direção diferente. Isso efetivamente garante que a escada rolante só se mova em uma direção por vez, conforme as pessoas entram na escada rolante.


    -PROCESSOS:


3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.


## Comprovando a execução do programa:
![imagemSO1](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/77bd1ad8-171e-454a-9da5-45a72acd99ad)
![imagemSO2](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/dc440767-e1ec-432a-a1e9-0240654c3871)
![imagemSO3](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/88f1d440-54af-495a-861b-671a1ba6569c)
![imagemSO4](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/fed9ea18-fbc8-47bf-beae-908cec1ed66f)
![imagemSO5](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/fc1cdc65-dd13-4e27-b524-3785bf6e1ede)
![imagemSO6](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/3566c794-888c-45ac-85e5-780532cebae0)
![imagemSO7](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/a6d2b20e-9472-4d02-af02-ac77694adf71)
![imagemSO8](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/1be3464c-405f-4ef8-b949-b4a3356adf6b)

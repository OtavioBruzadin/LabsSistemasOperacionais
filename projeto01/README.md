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

   Estratégia para evitar que duas pessoas acessem a escada rolante ao mesmo tempo:
   
   Utilizamos um semáforo POSIX, identificado por SEM_NAME, para controlar o acesso à região crítica do programa, que inclui a verificação e atualização da direção atual da escada rolante, bem como do último momento em que alguém utilizou a escada. O semáforo é inicializado com o valor 1 (sem_t* sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);)
Isso significa que, em qualquer momento, apenas um processo pode entrar na região crítica. Quando um processo (representando uma pessoa) quer acessar a escada rolante, ele primeiro tenta "travar" (ou "esperar por") o semáforo usando sem_wait(sem);. Isso reduz o contador do semáforo. Se o contador for maior que zero, o processo pode entrar na região crítica. Se o contador for zero, isso significa que outro processo já está na região crítica, e o processo atual será bloqueado até que o semáforo seja liberado (incrementado) por outro processo.
Após a conclusão da atualização da direção atual da escada rolante e do último momento, o processo libera o semáforo usando sem_post(sem);, permitindo que outro processo entre na região crítica.


3. Como garantir que somente uma das direções está ativa de cada vez:
   
    -THREADS:
   
    A direção atual da escada rolante é controlada pela variável global `int direcao_atual;`, que é inicialmente definida como -1, que demonstra que a escada está parada. A direção pode ser alterada para 0 (indicando uma direção) ou 1 (indicando a direção oposta) conforme a necessidade das pessoas que estão chegando.
   
   Dentro da função `pessoa_thread`, após adquirir o semáforo, a thread verifica se a direção atual da escada rolante corresponde à direção desejada pela pessoa (`if (direcao_atual == -1 || direcao_atual == pessoa->direcao)`). Se a direção for a mesma ou a escada estiver parada, a pessoa pode "entrar" na escada rolante, e a direção atual é atualizada para refletir a direção dessa pessoa.
   
   Essa checagem e atualização da direção acontecem dentro da região crítica protegida pelo semáforo, o que garante que apenas uma direção esteja ativa em qualquer momento, e uma mudança de direção só pode ocorrer se nenhuma outra pessoa estiver utilizando a escada rolante em uma direção diferente. Isso efetivamente garante que a escada rolante só se mova em uma direção por vez, conforme as pessoas entram na escada rolante.


    -PROCESSOS:

   Como garantir que somente uma das direções está ativa de cada vez:

   
    Para controlar a direção da escada rolante e garantir que apenas uma direção esteja ativa em qualquer momento, utilizamos uma variável compartilhada (direcao_atual) dentro da estrutura EstadoEscada que é mapeada em uma área de memória compartilhada entre todos os processos:


typedef struct {
    int direcao_atual;
    int ultimo_momento;
} EstadoEscada;


A lógica implementada na função simula_pessoa assegura que, antes de qualquer processo modificar a direção atual, ele verifica se a direção desejada é igual à direção atual ou se a escada está parada (direcao_atual == -1). Isso é feito dentro da região crítica protegida pelo semáforo, garantindo que as verificações e atualizações sejam feitas de maneira atômica, sem interferência de outros processos:

if (estado->direcao_atual == -1 || estado->direcao_atual == direcao) {
    estado->direcao_atual = direcao;
    estado->ultimo_momento = tempo_chegada + 10;
}

Essa abordagem assegura que a escada só mude de direção quando ninguém estiver usando-a na direção oposta e que apenas uma direção esteja ativa em cada momento, mantendo a sincronização e lógica esperadas conforme o enunciado do problema.




3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.


Na solução do problema da escada rolante, threads são mais práticas devido ao compartilhamento direto do espaço de memória, facilitando a atualização e acesso a estados comuns, como a direção da escada e o momento de uso. Processos, tendo espaços de memória isolados, requerem mecanismos de comunicação inter-processo para compartilhar estados, complicando a implementação. Portanto, threads são mais eficientes para este problema, oferecendo uma solução mais simples e direta para sincronização e compartilhamento de dados entre as "pessoas" acessando a escada rolante."


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

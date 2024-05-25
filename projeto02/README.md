## Como compilar o programa:

Para compilar códigos em C, é necessário instalar o compilador gcc.
```bash
sudo dnf install gcc
```
Para instalar o editor nano devemos utilizar o seguinte comando:
```bash
sudo dnf install nano
```
Para criar e editar um arquivo `.c` utilizamos o comando:
```bash
nano projeto02.c
```
Após a criação e edição  para compilar, devemos utilizar o comando:
```bash
gcc -o result projeto02.c -lpthread
```
## Como executar o programa:
```bash
./result
```



## Comprovando a execução do programa:
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/10bcc0e0-5752-45a4-ab72-ef039022c059)


## Código:

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/a70298ed-4b80-4da9-b539-8dc7adecfd1c)

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/12d6faa8-2c9e-4e6c-a0bf-fda0ac3f9fb5)

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/255dfdcf-b705-46fe-a70c-d3790f88405a)

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/77cbdde0-18e5-49c4-846b-2cd1dcc330cd)



## 

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/cef2da46-4218-4342-a698-f0b2ae3c1abe)

## Provando os requisitos:

1 - É possível realizar mais de uma tranferência por conta do mutex(to.mutex) e utilizando pthread_mutex_init impedir que haja deadlocks e problemas na hora de transferir valores de uma conta para outra.


2 - A conta from pode enviar mais de uma transação simultânea por conta da função mutex(from.mutex).


3 - Há uma verificação na função transferência que supre este requisito.

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/92bab806-1b01-4102-a629-a802b342cd84)

Se a valor do saldo for menor que a valor da transação, o código não executará o trecho em questão.


4 - Sim, graças aos ponteiros Sender e Receiver, que fazem com que não importa se é o to ou o from que precise dar ou receber, ele só precisa estar disponivel e com saldo.

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/ccbc198b-00f5-47a8-999a-44b2573fc7b0)

5 - Sim, ele funciona para 100 transações, no exemplo do codigo funcionando fizemos para menos para caber em um print só, mas basicamente ele vai tentar executar as transações 50x de um para o outro, qnd alcançar o limite do saldo ele vai apenas printar o resto para acabar o loop, nessa situação c2 estará com 200 de saldo, pois todo dinheiro foi transferido para ele; em seguida o código vai para o proximo loop e faz a mesma coisa, fazendo com que a conta c1 fique com todo o saldo no final. Essa é a saída para esse exemplo que usamos.

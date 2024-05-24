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

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/21c1034b-b6e5-421e-97ba-578f11d15a02)

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/6a0ccc7f-6160-4f3e-aca1-2f2a766a3be2)

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

5 - Basta mudar o loop de threads para o tamanho preferível, mas ele pode sim fazer até 100 transações.



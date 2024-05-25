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

5 - Basta modificar o array de threads para o tamanho preferível, e adicionar mais transferências nos loops for que criam as threads, mas ele pode sim fazer até 100 transações.
Como por exemplo:

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/55d7089b-5388-4a5e-a5f3-b6be4457766c)

Aumentar esse valor de 15 pra 100

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/e45a9258-a62a-4fc6-be86-6a8b4ed4d6d8)

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/0ef2da01-e13d-47d1-856f-36e0a5b5ef62)

E esses loops para: 
for (i = 0; i < 50; i++) do 'from' pro 'to' 

E: 
for (i = 50; i < 100; i++) do 'to' pro 'from'





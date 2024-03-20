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

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
nano lab03.c
```
Após a criação e edição  para compilar, devemos utilizar o comando

```bash
gcc -pthread lab03.c -o result
```
Adicionamos `-pthread` para garantir que o codigo seja compilado com suporte a threads

## Como executar o programa:

Para apresentar o resultado na tela, basta utilizarmos o comando abaixo

```bash
./result
```

---

Este programa em C cria uma thread filho usando a função clone() para executar uma função específica (threadFunction).

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/31077442/8a24bec3-2cd7-400d-b8c1-67b93ea77ca9)

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/31077442/bc732085-68fd-4581-b496-a10a0a6983d0)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/31077442/b1d49fe7-a4e7-41a5-a227-b6b07cbf7668)


## Comprovando a execução do programa:
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/31077442/e8a7bebf-3cb7-4517-a1d0-9c69e6520848)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/31077442/660f156b-c9ba-4fc4-a6f2-b6f8c997c79e)

O resultado ocorreu conforme o esperado.

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
nano pthread.c
```
Após a criação e edição  para compilar, devemos utilizar o comando:
```bash
gcc pthread.c -o result -lpthread -lrt
```

## Como executar o programa:

Para apresentar o resultado na tela, basta utilizarmos o comando abaixo

```bash
./result
```

---

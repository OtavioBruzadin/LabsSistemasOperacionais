Conclusao lab1 SO

Após terminarmos de efetuar o login e todas as credenciais necessárias no servidor da AWS para que tudo funcione da forma desejada, foi iniciado a atividade de laboratório 01 de Sistemas Operacionais.
O objetivo desta atividade é a criação e execução de um código **Hello World!** em qualquer linguagem de programação (optamos pela linguagem C).

De início foi necessário fazer a instalação do pacote Development Tool para a compilação do código juntamente com a instalação de um editor de texto, o editor escolhido foi o Nano.
sudo dnf groupinstall 'Development Tools'
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/ff3227f5-f493-40f1-9d7e-e637eb1bfbf7)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/6f052c5f-173b-4cc5-9273-f3e2d0262a80)

Depois da confirmação 'y' do comando

![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/61742dd0-49dc-4e2e-8a2b-586487244aa8)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/7d5f17e6-c2e7-4c4c-919e-0d141c6cc12b)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/c3cf330b-8cd1-4c9d-9191-9c2c81c95852)
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/146960599/01b78448-d1dc-441c-b21f-d781579e61d3)


![Imagem do WhatsApp de 2024-03-03 à(s) 13 33 54_583a0b1c](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/89026599/7945f87c-7d15-4c3d-8b01-e930fbd51845)

Com a instalação concluída de ambos, compilador e editor, é necessário criar o arquivo .c da atividade. Para a criação é necessário o comando nano *nome do arquivo*.c, para esta atividade o arquivo foi nomeado como **lab01.c**

![Imagem do WhatsApp de 2024-03-03 à(s) 13 39 35_c2033982](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/89026599/16511ae9-d9cd-4eb2-9a79-6d5c573fb322)

Efetuando o comando o editor é aberto automaticamente
![Imagem do WhatsApp de 2024-03-03 à(s) 13 40 06_7b05cef3](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/89026599/72392e17-3f37-469e-a207-8791285589b2)

E é necessário seguir os passos tradicionais da linguagem C, a importação da biblioteca padrão (stdio.h) e a função Main. Dentro da função main efetuamos o objetivo da atividade (a criação de um printf Hello World!)

![Imagem do WhatsApp de 2024-03-03 à(s) 13 42 00_7159c773](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/89026599/d074f80f-c10a-41f0-a9ae-15b84e0434b1)

Após o arquivo ser salvo e fechado, é necessário compilar o programa para que ele possa funcionar, assim é utilizado o comando gcc *nome do arquivo.c* -o *nome do arquivo após a compilação*. Assim o comando fica da seguinte forma: **gcc lab01.c -o lab01**

![Imagem do WhatsApp de 2024-03-03 à(s) 13 44 01_595295c6](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/89026599/1cb8fc3d-5f9a-4339-be03-dfa59053eaf5)

Para finalizarmos, é necessário checar se a saída encontrada é de fato a desejada, **Hello World!**. O necessário para fazermos essa verificação é a utilização do comando *./nome do arquivo*, então utilizamos o comando **./lab01**

![Imagem do WhatsApp de 2024-03-03 à(s) 13 45 45_2bde063e](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/89026599/9768b3ac-ca6c-4622-aecc-be48649cf4f8)

Com a atividade finalizada, é necessário dar upload da mesma no repositório do Github. Primeiramente utilizamos **git init** para inicializar o repositorio local, seguido de **git add** *nome do arquivo* (lab01), para adicioná-lo ao próximo commit para o repositório, logo em seguida **git commit** para aplicar as alterações feitas no repositorio local, e em seguida um **git push** para enviar as alterações ao repositório remoto.

(É possível notar que o nome do arquivo está helloworld.c, isso se deve pois outro integrante realizou os prints para esta parte)

![Screenshot from 2024-02-27 09-26-16](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/31077442/79248ed4-1093-4405-b403-b4d5b7df768d)
![Screenshot from 2024-02-27 09-27-08](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/31077442/f7150e16-1119-4ba5-bf79-10da0c001d09)
![Screenshot from 2024-02-27 09-27-19](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/31077442/b34a0a6e-912a-45be-ad3b-58b1542edc7d)

Nesta última imagem está a confirmação de que o programa foi commitado e está dentro do repositório no Github
![image](https://github.com/OtavioBruzadin/LabsSistemasOperacionais/assets/31077442/11ac5ac4-fcbd-403a-ac1c-5595404bc395)

Conclusão Final

Como podemos ver nos prints acima o arquivo lab01.c foi executado com exito na maquina virtual da AWS, com isso realizamos o processo de commit e push do arquivo para o repositorio no Github utilizando o terminal da maquina virtual. 

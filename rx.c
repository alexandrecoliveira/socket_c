//https://www.youtube.com/watch?v=GaxjJvMnz-I
#include <stdio.h>
#include <stdlib.h>     //Permite o uso de atoi
#include <unistd.h>     //Permite usar a funcao close()
#include <sys/types.h>  //Permite usar constantes relacionadas a sockets
#include <sys/socket.h> //Permite usar funcoes relacionadas a sockets
#include <arpa/inet.h>  //Permite usar funcoes htonl, htons
#include <string.h>     //Permite usar strlen

int calcula_soma(int n)
{
    int soma = 0;
    for(int i = 1; i <= n; i++)    
        soma += i;
    return soma;
}

int main() 
{
    int server, client, numero_cli;
    unsigned int csize;
    char buffer[10];                                 //guarda o recebido pela funcao recv()
    struct sockaddr_in caddr;    
    struct sockaddr_in saddr;
    
    server = socket(AF_INET, SOCK_STREAM, 0);        //familia, tipo, 0
    saddr.sin_family         = AF_INET;              //família de protocolos, aqui IPV4
    saddr.sin_addr.s_addr    = htonl(INADDR_ANY);    //endereço local utilizado pelo socket     
    saddr.sin_port           = htons(2006);          //porta utilizada pelo socket

    csize = sizeof(caddr);
    
    bind(server, (struct sockaddr*) &saddr, sizeof(saddr)); //bind associa o socket ao endereço especificado na sctruct
    listen(server, 2);                                      //maximo de conexoes simultaneas

    while(1)
    {
        client = accept(server, (struct sockaddr*) &caddr, &csize);   //espera por conexoes
        recv(client, buffer, sizeof(buffer), 0);            //recebe os dados do cliente e retorna o tam dos dados recebidos
        numero_cli = atoi(buffer);                          //converte o buffer para int
        numero_cli = calcula_soma(numero_cli);
        sprintf(buffer, "%d", numero_cli);                  //imprime formatado(converte) 
//        printf("buffer: %ld\n", strlen(buffer));
        send(client, buffer , 2, 0);           //envia dados pelo socket      
        puts(buffer);
        numero_cli = 0;        
        sprintf(buffer, "        %d", 0);        
        fflush(stdout);                                     //limpa o buffer e move os dados para a saida padrao (tela, disco)
        close(client);  
    }
    return 0;
}

//pode-se usar o comando echo -e "mensagem\0" | nc localhost 2006

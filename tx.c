//https://www.binarytides.com/socket-programming-c-linux-tutorial/
#include <stdio.h>
#include <unistd.h>     //Permite usar a funcao close()
#include <sys/types.h>  //Permite usar constantes relacionadas a sockets
#include <sys/socket.h> //Permite usar funcoes relacionadas a sockets
#include <arpa/inet.h>  //Permite usar funcoes htonl, htons
#include <string.h>     //Permite usar strlen

int main() 
{
    int socket_desc, nro = 5, tam_recv = 0;
	struct sockaddr_in server;
    char msg[10], server_reply[1025];    

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);      //Existe o SOCK_DGRAM que significa UDP
    if(socket_desc == -1)
        printf("Erro ao criar o socket");        
    server.sin_addr.s_addr = inet_addr("127.0.0.1");    //"Convert an IP address to a long format"
	server.sin_family = AF_INET;                        //Diz que é IPV4
	server.sin_port = htons( 2006 );                    //Porta de destino

	//Connect to remote server
	if (connect(socket_desc , (struct sockaddr *) &server , sizeof(server)) < 0)
	{	    
		puts("Erro ao conectar");
		return 1;
	}
		
	puts("Conectado.\n");
	//Arrumar a exibicao da resposta do server // sujeira 
//	while(1)
//	{
		puts("Digite o numero: ");
//        scanf("%d", &nro);          //escaneia o número
        sprintf(msg, "%d", nro);    //imprime formatado(converte) 
        
        if( send(socket_desc , msg , strlen(msg) , 0) < 0)
        {
	        puts("Falha no envio");
	        return 1;
        }
        puts("Dados enviados\n");
        
        //Receive a reply from the server
        if( ( tam_recv = recv(socket_desc, server_reply , 1024 , 0)) < 0)
	        puts("recv falhou");
        puts("Server diz: ");
        server_reply[tam_recv-3] = "\0";
        puts(server_reply);
//        puts("Continuar <S> <N>: ");
//        scanf(" %1[^\n]", msg);
//        if(strcmp(msg, "N") == 0)
//        {        
//            break;
//        }
//	}
	puts("Conexão encerrada");    	
	return 0;
}

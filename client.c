/****************** CLIENT CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
//the thread function
int clientSocket;
int exitFun =0;
void *connection_handler(char *);
int main(){
	
	char buffer[1024];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;

	/*---- Create the socket. The three arguments are: ----*/
	/* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	/*---- Configure settings of the server address struct ----*/
	/* Address family = Internet */
	serverAddr.sin_family = AF_INET;
	/* Set port number, using htons function to use proper byte order */
	serverAddr.sin_port = htons(7891);
	/* Set IP address to localhost */
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//    serverAddr.sin_addr.s_addr = inet_addr("172.20.114.25");
	/* Set all bits of the padding field to 0 */
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	/*---- Connect the socket to the server using the address struct ----*/
	addr_size = sizeof serverAddr;
	connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

	/*---- Read the message from the server into the buffer ----*/
	//recv(clientSocket, buffer, 1024, 0);

	/*---- Print the received message ----*/
	//printf("Data received: %s\n",buffer);


	pthread_t sniffer_thread;
        
        if( pthread_create( &sniffer_thread , NULL ,  connection_handler , "Hello") < 0)
        {
            perror("could not create thread");
            return 1;
        } 
   
	while (!exitFun);
	close(clientSocket);
	return 0;
}

void *connection_handler(char * sendBuff)
{

    int n; char buffer[1024];
	
	printf("Client: Receiving Message...\n");
	/*---- Read the message from the server into the buffer ----*/
	recv(clientSocket, buffer, 1024, 0);

	/*---- Print the received message ----*/
	printf("Data received: %s\n",buffer);

    return 0;
}

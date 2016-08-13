#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

char passenc[256],bool_equation[256];

void encrypt(char *password)
{
	//hard coded for now
	strcpy(passenc,"1010101010");
}

void booleq()
{
	//hard coded for now
	strcpy(bool_equation,"a.b.c.d+e+f.g+h.i.j");
}

int getserversolu()
{
	//for now
	return 1;
}

int verifyclient(char buffer[256])
{
	int serversolu=getserversolu();
	if(serversolu==atoi(buffer))
		return 1;
	else
		return 0;
}

void error(const char *msg)
{
perror(msg);
exit(1);
}

int main(int argc, char *argv[])
{
int sockfd, newsockfd, portno,isverified=1;
socklen_t clilen;
char buffer[256],username[256];
char password[]="qwerasdf123#";
struct sockaddr_in serv_addr, cli_addr;
int n;
if (argc < 2) 
{
	fprintf(stderr,"ERROR, no port provided\n");
	exit(1);
}
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0)
	error("ERROR opening socket");
bzero((char *) &serv_addr, sizeof(serv_addr));
portno = atoi(argv[1]);

serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = INADDR_ANY;
serv_addr.sin_port = htons(portno);

if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	error("ERROR on binding");

listen(sockfd,5);
clilen = sizeof(cli_addr);

newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
if (newsockfd < 0)
	error("ERROR on accept");

//Accept username
bzero(username,256);
n = read(newsockfd,username,255);
if (n < 0) 
	error("ERROR reading from socket");

//Run algorithm
while(isverified)
{
	//call encrypt function to encrypt the password
	encrypt(password);

	//generate boolean equation
	booleq();
	bzero(buffer,256);
	strcpy(buffer,bool_equation);

	//send message to the client
	// printf("Server: ");
	// fgets(buffer,255,stdin);
	n = write(newsockfd,buffer,strlen(buffer));
	if (n < 0) 
		error("ERROR writing to socket");

	//recieve message from the client
	bzero(buffer,256);
	n = read(newsockfd,buffer,255);
	if (n < 0) 
		error("ERROR reading from socket");
	printf("Client: %s\n",buffer);

	isverified=verifyclient(buffer);

}
close(newsockfd);
close(sockfd);
return 0;
}
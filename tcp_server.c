//tcp server

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
	int sockfd,newsock;
	struct sockaddr_in server,client;
	char buffer[1024];
	socklen_t len=sizeof(client);
	
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=INADDR_ANY;
	
	bind(sockfd,(struct sockaddr *)&server,sizeof(server));
	listen(sockfd,5);
	printf("waiting for connection....\n");
	newsock=accept(sockfd,(struct sockaddr *)&client,&len);
	
	read(newsock,buffer,sizeof(buffer));
	printf("message:%s\n",buffer);
	
	send(newsock,"hello client",12,0);
	close(newsock);
	close(sockfd);
	return 0;

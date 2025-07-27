//tcp client

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arp/inet.h>

int main(){
	int sockfd;
	struct sockadd_in server;
	char buffer[1024]="hello from client";
	socklen_t len=sizeof(server);
	
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	connect(sockfd,(struct sockaddr *)&server,len);
	
	send(sockfd,buffer,strlen(buffer),0);
	read(sockfd,buffer,sizeof(buffer));
	printf("server:%s\n",buffer);
	
	close(sockfd);
	return 0;
}

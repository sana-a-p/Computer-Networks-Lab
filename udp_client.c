// udp client

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main(){
	int sockfd;
	struct sockadd_in server;
	socklen_t len=sizeof(server);
	char buffer[1024]="hello from client";
	char response[1024];
	
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	
	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	printf("sending message to server....\n");
	
	sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&server,len);
	
	recvfrom(sockfd,response,sizeof(response),0(struct sockaddr *)&server,&len);
	
	printf("message:%s\n",reponse);
	
	close(sockfd);
	return 0;
}

// udp server

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
	int sockfd;
	struct sockaddr_in server,client;
	char buffer[1024];
	socklen_t len=sizeof(client);
	
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	
	server.sin_family=AF_INET;
	sever.sin_port=htons(8080);
	server.sin_addr.s_addr=INADDR_ANY;
	
	bind(sockfd,(struct sockaddr *)&server,sizeof(server));
	
	recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&client,&len);
	printf("message:%s\n",buffer);
	
	sendto(sockfd,"hello client",12,0,(struct sockaddr *)&client,len);
	
	close(sockfd);
	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<string.h>

#define TOTPACK 10
#define WINDSIZE 4

int ackrecv(){
	return rand()%10<7;
}

int main(){
	srand(time(0));
	
	int base=1;
	int nextseqnum=1;
	
	while(base<=TOTPACK){
		printf("----sending window----\n");
		while(nextseqnum<base+WINDSIZE && nextseqnum<=TOTPACK){
			printf("sendeing packet %d ....\n",nextseqnum);
			nextseqnum ++;
		}
		sleep(1);
		printf("----receiving window ----\n");
		for(int i=base;i<nextseqnum;i++){
			if(ackrecv()){
				printf("received ack for packet %d ...\n",i);
			}
			else{
				printf("ack for packet %d lost..\n",i);
				printf("restransmitting packet %d\n",i);
				nextseqnum=i;
			}
			
		}
		base=nextseqnum;
		sleep(1);
	}
	return 0;
}

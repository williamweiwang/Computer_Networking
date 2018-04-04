#define SRV_IP "127.0.0.1"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
     
#define BUFLEN 512
#define NPACK 50
#define PORT 9930
#define BUF_SIZE 1000

#define SLOW_START 1
#define C_AVOID 2

 /* diep(), #includes and #defines like in the server */

struct sockaddr_in initial(){
	struct sockaddr_in si_other;

	memset((char *) &si_other, 0, sizeof(si_other));
    	si_other.sin_family = AF_INET;
    	si_other.sin_port = htons(PORT);
    	if (inet_aton(SRV_IP, &si_other.sin_addr)==0){
    		fprintf(stderr, "inet_aton() failed\n");
    		return si_other;
    	}

	return si_other;
}

 
int connect_socket(void){
     	int s;
     
    	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
    		perror("socket");
	
    	return s;
}

void close_socket(int s){
	close(s);
}

void print_cwnd(int cwnd){
	printf("CWND = %d\n", cwnd);
}

void print_duplicate(){
	printf("3 duplicate ack\n");
}

void print_timeout(){
	printf("Time out\n");
}

int main(void){
	struct sockaddr_in si_other, recv_ip;
	int s, i, slen=sizeof(si_other), rlen = sizeof(recv_ip);
     	char buf[BUFLEN];

	struct timeval tv;
  	fd_set readfds;

	si_other = initial();
	s = connect_socket();

	int send_buffer[NPACK + 1];
	int cwnd = 1;
	double cwnd_double = 1.0;
	int lastByteSent = 0;
	int lastByteAcked = 0;
	int ssthresh = 10;

	int pre_acked;
	int acked = 0;
	int duplicate_ack = 0;

	int state = SLOW_START;

	for(i = 0; i < NPACK + 1; i++){
		send_buffer[i] = i;
	}

/* Insert your codes below */

/* Insert your codes above */

	close_socket(s);
	return 0;
}

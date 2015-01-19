#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(){
	int s;
	char c=' ';
	s = socket (AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in server;
     	server.sin_family = AF_INET;
     	server.sin_port   = 50789;
     	server.sin_addr.s_addr = inet_addr ("141.57.9.14");

	//Petition

	char buff[100];
	int l;

	while(c != EOF){
		printf("Insert message: ");
		if (fgets(buff, sizeof(buff), stdin) == NULL) break;
		l = sendto(s, buff, sizeof(buff), 0, (struct sockaddr *)&server, sizeof(server));
	
		//Server response
		l = read (s, buff, 100);
		printf("Response: %s\n", buff);
		
/*		c = getchar();
		if (c != EOF)
		while (getchar() != '\n');*/
	}
        strcpy(buff, "ENDE");
        l = sendto(s, buff, sizeof(buff), 0, (struct sockaddr *)&server, sizeof(server));
	close(s);
	printf("Kommunikation beendet\n");
	return 0;
}

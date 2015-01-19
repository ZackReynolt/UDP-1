#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(){
	//Gen Var
	char c=' ';

	int s;
	s = socket (AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port   = 50789;
	server.sin_addr.s_addr = INADDR_ANY;

	int rc;
	rc = bind (s,(struct sockaddr*)&server, sizeof(server));
	if(rc < 0){
 		perror("bind");
		exit(2);
	}
	
	char buff[100] = {" "};
	char temp[6];
	
	// Read Loop
	while (c != EOF) {
	
		//Wait for the client petition
	
		struct sockaddr_in client;
		int  clen,l;
		clen = sizeof(client);
		l = recvfrom(s, buff, sizeof(buff), 0, (struct sockaddr *)&client, &clen);
		if (l == 0 || l ==-1) break;	
                if (strcmp (buff, "ENDE") ==0) break;
		printf("Message: %sfrom: %s \n", buff, inet_ntoa(client.sin_addr));
		printf("port: %d\n",ntohs(client.sin_port));
	
		//Response to the client
		
		//Change the message
		strcpy(buff,"IP: ");
		strcat(buff,inet_ntoa(client.sin_addr));
		strcat(buff," port: ");
		sprintf(temp, "%d", ntohs(client.sin_port));
		strcat(buff,temp);
		l = sendto(s, buff, sizeof(buff), 0, (struct sockaddr *)&client, clen);
//		c = getchar();
	}
	
	close(s);
	printf("Server beendet\n");
	return 0;
}

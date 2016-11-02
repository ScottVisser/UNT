#include "server.h"

//// Main function ///
int main(void)
    {

	struct tcpSeg tcpOut = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	struct tcpSeg tcpIn = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	char buffer[1024];	
	int sockfd, newsockfd, portno, n;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	short int headerlenMultsof32bit = 6;

	printf("Openning socket to accept client connection\n");
	printf("Please enter port number: ");
	scanf("%d", &portno);	

//// Openning Socket ////
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
     	if (sockfd < 0) 
         error("ERROR opening socket");
     	bzero((char *) &serv_addr, sizeof(serv_addr));

     	serv_addr.sin_family = AF_INET;
     	serv_addr.sin_addr.s_addr = INADDR_ANY;
     	serv_addr.sin_port = htons(portno);

     	if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");

	printf("socket created, waiting for client...\n");

////// Listen and accept new connection ////
     	listen(sockfd,5);
     	clilen = sizeof(cli_addr);
     	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, 
                 &clilen);
      	if (newsockfd < 0) 
         error("ERROR on accept");
	printf("\nClient connection made\n\n");


	int x = 0;
	while (1) 
	{
//Read tcp seg
		read(newsockfd, buffer, sizeof(buffer));
		sscanf(buffer, "%hu %hu %d %d %hd %hd %hd %hd %d", &tcpIn.sourcePort, &tcpIn.destPort, &tcpIn.seqNum, &tcpIn.ackNum, &tcpIn.reserve, &tcpIn.recWindow, &tcpIn.checksum, &tcpIn.urgentdp, &tcpIn.options);

//Print tcp seg
		printf("Tcp seg recieved:\n");
		printf("%d\t%d\n", tcpIn.sourcePort, tcpIn.destPort);
		printf("%d\n%d\n", tcpIn.seqNum, tcpIn.ackNum);
		printf("%d\t%d\n", tcpIn.reserve, tcpIn.recWindow);
		printf("%d\t%d\n", tcpIn.checksum, tcpIn.urgentdp);
		printf("%d\n\n", tcpIn.options);

		if (tcpIn.reserve - (headerlenMultsof32bit << 12) == 2) // syn = 1
		{	//generate response
			tcpOut.sourcePort = tcpIn.sourcePort;
			tcpOut.destPort = tcpIn.destPort;
			tcpOut.seqNum = 42;
			tcpOut.ackNum = tcpIn.seqNum + 1;
			tcpOut.reserve = tcpIn.reserve + 16; //set ack = 1 and syn =1 still
			snprintf(buffer, sizeof(buffer), "%d %d %d %d %d %d %d %d %d", tcpOut.sourcePort, tcpOut.destPort, tcpOut.seqNum, tcpOut.ackNum, tcpOut.reserve, tcpOut.recWindow, tcpOut.checksum, tcpOut.urgentdp, tcpOut.options);
			//print response
			printf("Tcp connection granted send:\n");
			printf("%d\t%d\n", tcpOut.sourcePort, tcpOut.destPort);
			printf("%d\n%d\n", tcpOut.seqNum, tcpOut.ackNum);
			printf("%d\t%d\n", tcpOut.reserve, tcpOut.recWindow);
			printf("%d\t%d\n", tcpOut.checksum, tcpOut.urgentdp);
			printf("%d\n\n", tcpOut.options);
			// write back to client
			write(newsockfd, buffer, sizeof(buffer));
		}

		else if (tcpIn.reserve - (headerlenMultsof32bit << 12) == 16) // ack = 1
		{
			printf("------------------------------------\n\n");
		}

		else if (tcpIn.reserve - (headerlenMultsof32bit << 12) == 1) // fin = 1
		{	//generate response
			tcpOut.sourcePort = tcpIn.sourcePort;
			tcpOut.destPort = tcpIn.destPort;
			tcpOut.seqNum = 42;
			tcpOut.ackNum = tcpIn.seqNum + 1;
			tcpOut.reserve = (headerlenMultsof32bit << 12) + 16; //set ack = 1 and syn =1 still
			snprintf(buffer, sizeof(buffer), "%d %d %d %d %d %d %d %d %d", tcpOut.sourcePort, tcpOut.destPort, tcpOut.seqNum, tcpOut.ackNum, tcpOut.reserve, tcpOut.recWindow, tcpOut.checksum, tcpOut.urgentdp, tcpOut.options);
			//print response
			printf("Tcp connection close send ACK:\n");
			printf("%d\t%d\n", tcpOut.sourcePort, tcpOut.destPort);
			printf("%d\n%d\n", tcpOut.seqNum, tcpOut.ackNum);
			printf("%d\t%d\n", tcpOut.reserve, tcpOut.recWindow);
			printf("%d\t%d\n", tcpOut.checksum, tcpOut.urgentdp);
			printf("%d\n\n", tcpOut.options);
			// write back to client
			write(newsockfd, buffer, sizeof(buffer));

			tcpOut.reserve = (headerlenMultsof32bit << 12) + 1;
 			snprintf(buffer, sizeof(buffer), "%d %d %d %d %d %d %d %d %d", tcpOut.sourcePort, tcpOut.destPort, tcpOut.seqNum, tcpOut.ackNum, tcpOut.reserve, tcpOut.recWindow, tcpOut.checksum, tcpOut.urgentdp, tcpOut.options);
			//print response
			printf("Tcp connection close send FIN:\n");
			printf("%d\t%d\n", tcpOut.sourcePort, tcpOut.destPort);
			printf("%d\n%d\n", tcpOut.seqNum, tcpOut.ackNum);
			printf("%d\t%d\n", tcpOut.reserve, tcpOut.recWindow);
			printf("%d\t%d\n", tcpOut.checksum, tcpOut.urgentdp);
			printf("%d\n\n", tcpOut.options);
			// write back to client
			write(newsockfd, buffer, sizeof(buffer));
	
			read(newsockfd, buffer, sizeof(buffer));
			sscanf(buffer, "%hu %hu %d %d %hd %hd %hd %hd %d", &tcpIn.sourcePort, &tcpIn.destPort, &tcpIn.seqNum, &tcpIn.ackNum, &tcpIn.reserve, &tcpIn.recWindow, &tcpIn.checksum, &tcpIn.urgentdp, &tcpIn.options);
			printf("Tcp seg recieved:\n");
			printf("%d\t%d\n", tcpIn.sourcePort, tcpIn.destPort);
			printf("%d\n%d\n", tcpIn.seqNum, tcpIn.ackNum);
			printf("%d\t%d\n", tcpIn.reserve, tcpIn.recWindow);
			printf("%d\t%d\n", tcpIn.checksum, tcpIn.urgentdp);
			printf("%d\n\n", tcpIn.options);
			
			close(newsockfd);
			close(sockfd);
			return 0;
		}
		else 
		 printf("error\n\n");
	}

	close(newsockfd);
	close(sockfd);
return 0;
}
//// End of Main function and program ///


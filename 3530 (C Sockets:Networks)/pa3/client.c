#include "server.h"

//Begin main function
int main(void)
{

// declare variables
	int sockfd;
    	struct sockaddr_in serv_addr;
    	struct hostent *server;
	short int portno;
	char *servername = "cse01";
	struct tcpSeg connectReq = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	struct tcpSeg tcpIn = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	struct tcpSeg tcpOut = {0, 0, 0, 0, 0, 0, 0, 0, 0};

	char buffer[1024]
;
//add error codes for incorrect inputs
	printf("please enter client server socket port number: ");
	scanf("%hd", &portno);
	printf("\n");

    	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    	if (sockfd < 0) 
         error("ERROR opening socket");

    	server = gethostbyname(servername);
    	if (server == NULL) {
        	fprintf(stderr,"ERROR, no such host\n");
        	exit(0);
    	}

//socket connect to server
    	bzero((char *) &serv_addr, sizeof(serv_addr));
    	serv_addr.sin_family = AF_INET;
    	bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    	serv_addr.sin_port = htons(portno);
    	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
         error("ERROR connecting");
	printf("connection successful\n\n");
	
//Populate connection request tcpseg	
	socklen_t len = sizeof(serv_addr);
	if (getsockname(sockfd, (struct sockaddr *) &serv_addr,&len) == -1)
	 printf("error of some sort");

	connectReq.destPort = portno;
	connectReq.sourcePort =  ntohs(serv_addr.sin_port);
	connectReq.seqNum = 10;

	//header length in mults of 32 bits should be 6 or (0110)
	short int headerlenBytes = sizeof(connectReq);
	short int headerlenMultsof32bit = headerlenBytes / 4; // 4bytes per 32bits = Mults of 32bit
	headerlenMultsof32bit = headerlenMultsof32bit << 12;
	connectReq.reserve = headerlenMultsof32bit + 2; // add 2 to set syn bit to 1

	//print binary of headerlength
/*	int c, bin;
	for (c = 15; c>=0; c--)
	{
		bin = headerlenMultsof32bit >> c;
		if (bin & 1)
		 printf("1");
		else
		 printf("0");
	}
	printf("\n\n");
*/

//generate buffer
	snprintf(buffer, sizeof(buffer), "%d %d %d %d %d %d %d %d %d", connectReq.sourcePort, connectReq.destPort, connectReq.seqNum, connectReq.ackNum, connectReq.reserve, connectReq.recWindow, connectReq.checksum, connectReq.urgentdp, connectReq.options);

//print first tcp seg (connection request)
	printf("Tcp connection request send:\n");
	printf("%d\t%d\n", connectReq.sourcePort, connectReq.destPort);
	printf("%d\n%d\n", connectReq.seqNum, connectReq.ackNum);
	printf("%d\t%d\n", connectReq.reserve, connectReq.recWindow);
	printf("%d\t%d\n", connectReq.checksum, connectReq.urgentdp);
	printf("%d\n\n", connectReq.options);
//send first tcp seg
	write(sockfd, buffer, sizeof(buffer));

	read(sockfd, buffer, sizeof(buffer));
	sscanf(buffer, "%hu %hu %d %d %hd %hd %hd %hd %d", &tcpIn.sourcePort, &tcpIn.destPort, &tcpIn.seqNum, &tcpIn.ackNum, &tcpIn.reserve, &tcpIn.recWindow, &tcpIn.checksum, &tcpIn.urgentdp, &tcpIn.options);
//Print tcp seg
	printf("Tcp connection granted recieved:\n");
	printf("%d\t%d\n", tcpIn.sourcePort, tcpIn.destPort);
	printf("%d\n%d\n", tcpIn.seqNum, tcpIn.ackNum);
	printf("%d\t%d\n", tcpIn.reserve, tcpIn.recWindow);
	printf("%d\t%d\n", tcpIn.checksum, tcpIn.urgentdp);
	printf("%d\n\n", tcpIn.options);

//if syn = 1 and ack = 1respond with ack
	if (tcpIn.reserve - (headerlenMultsof32bit == 18)) // syn = 1 and ack = 1
	{	//generate response
		tcpOut.sourcePort = tcpIn.sourcePort;
		tcpOut.destPort = tcpIn.destPort;
		tcpOut.seqNum = connectReq.seqNum + 1;
		tcpOut.ackNum = tcpIn.seqNum + 1;
		tcpOut.reserve = tcpIn.reserve - 2; //set ack = 1 and syn =0 still
		snprintf(buffer, sizeof(buffer), "%d %d %d %d %d %d %d %d %d", tcpOut.sourcePort, tcpOut.destPort, tcpOut.seqNum, tcpOut.ackNum, tcpOut.reserve, tcpOut.recWindow, tcpOut.checksum, tcpOut.urgentdp, tcpOut.options);
		//print response
		printf("Tcp connection granted sending ACK:\n");
		printf("%d\t%d\n", tcpOut.sourcePort, tcpOut.destPort);
		printf("%d\n%d\n", tcpOut.seqNum, tcpOut.ackNum);
		printf("%d\t%d\n", tcpOut.reserve, tcpOut.recWindow);
		printf("%d\t%d\n", tcpOut.checksum, tcpOut.urgentdp);
		printf("%d\n\n", tcpOut.options);
		// write back to client
		write(sockfd, buffer, sizeof(buffer));
		printf("---------------------------------------\n\n");
	}

// generate close tcp connection seg
	tcpOut.seqNum = 10;
	tcpOut.ackNum = 0;
	tcpOut.reserve = headerlenMultsof32bit + 1; //set ack = 1 and syn =0 still
	snprintf(buffer, sizeof(buffer), "%d %d %d %d %d %d %d %d %d", tcpOut.sourcePort, tcpOut.destPort, tcpOut.seqNum, tcpOut.ackNum, tcpOut.reserve, tcpOut.recWindow, tcpOut.checksum, tcpOut.urgentdp, tcpOut.options);
	printf("Tcp close request sending FIN:\n");
	printf("%d\t%d\n", tcpOut.sourcePort, tcpOut.destPort);
	printf("%d\n%d\n", tcpOut.seqNum, tcpOut.ackNum);
	printf("%d\t%d\n", tcpOut.reserve, tcpOut.recWindow);
	printf("%d\t%d\n", tcpOut.checksum, tcpOut.urgentdp);
	printf("%d\n\n", tcpOut.options);
	write(sockfd, buffer, sizeof(buffer));

	read(sockfd, buffer, sizeof(buffer));
	sscanf(buffer, "%hu %hu %d %d %hd %hd %hd %hd %d", &tcpIn.sourcePort, &tcpIn.destPort, &tcpIn.seqNum, &tcpIn.ackNum, &tcpIn.reserve, &tcpIn.recWindow, &tcpIn.checksum, &tcpIn.urgentdp, &tcpIn.options);
//Print tcp seg
	printf("Tcp close connection, ACK Recieved:\n");
	printf("%d\t%d\n", tcpIn.sourcePort, tcpIn.destPort);
	printf("%d\n%d\n", tcpIn.seqNum, tcpIn.ackNum);
	printf("%d\t%d\n", tcpIn.reserve, tcpIn.recWindow);
	printf("%d\t%d\n", tcpIn.checksum, tcpIn.urgentdp);
	printf("%d\n\n", tcpIn.options);

	read(sockfd, buffer, sizeof(buffer));
	sscanf(buffer, "%hu %hu %d %d %hd %hd %hd %hd %d", &tcpIn.sourcePort, &tcpIn.destPort, &tcpIn.seqNum, &tcpIn.ackNum, &tcpIn.reserve, &tcpIn.recWindow, &tcpIn.checksum, &tcpIn.urgentdp, &tcpIn.options);
//Print tcp seg
	printf("Tcp close connection, FIN recieved:\n");
	printf("%d\t%d\n", tcpIn.sourcePort, tcpIn.destPort);
	printf("%d\n%d\n", tcpIn.seqNum, tcpIn.ackNum);
	printf("%d\t%d\n", tcpIn.reserve, tcpIn.recWindow);
	printf("%d\t%d\n", tcpIn.checksum, tcpIn.urgentdp);
	printf("%d\n\n", tcpIn.options);

//generate close tcp ack seg
	tcpOut.sourcePort = tcpIn.sourcePort;
	tcpOut.destPort = tcpIn.destPort;
	tcpOut.seqNum = connectReq.seqNum + 1;
	tcpOut.ackNum = tcpIn.seqNum + 1;
	tcpOut.reserve = headerlenMultsof32bit + 16;
	snprintf(buffer, sizeof(buffer), "%d %d %d %d %d %d %d %d %d", tcpOut.sourcePort, tcpOut.destPort, tcpOut.seqNum, tcpOut.ackNum, tcpOut.reserve, tcpOut.recWindow, tcpOut.checksum, tcpOut.urgentdp, tcpOut.options);
	//print response
	printf("Tcp connection closed sending ACK:\n");
	printf("%d\t%d\n", tcpOut.sourcePort, tcpOut.destPort);
	printf("%d\n%d\n", tcpOut.seqNum, tcpOut.ackNum);
	printf("%d\t%d\n", tcpOut.reserve, tcpOut.recWindow);
	printf("%d\t%d\n", tcpOut.checksum, tcpOut.urgentdp);
	printf("%d\n\n", tcpOut.options);
	// write back to client
	write(sockfd, buffer, sizeof(buffer));

	



 	close(sockfd);
    	return 0;
}

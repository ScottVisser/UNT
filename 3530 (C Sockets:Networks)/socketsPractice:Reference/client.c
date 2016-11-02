//Scott Visser
//CSCE 3530
//PA 1

// COMPILE WITH:
// gcc client.c -o runclient
// ./runclient #serverName# #portnumber#
// (ex: ./runclient cse01 1234)

// Client C file
// Connects to server.c over network with sockets
// once connection success, user inputs a url
// url string message is sent to server via socket
// server sends html code for url
// html code output is saved to file "httpOutput"
//close socket and kill file pointer



// Include libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h> 

//error function
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

//Begin main function
int main(void)
{

// declare variables
    int sockfd, n, i;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char *urequest;
    char *sresponse;
	int portno;
	char *servername;
	char *hostname;
	servername = malloc(256);

	//add error codes for incorrect inputs
	printf("please enter proxy server name (ex: cse01): ");
	scanf("%s", servername);
	printf("\nplease enter client server socket port number: ");
	scanf("%d", &portno);

	printf("\n%s %d\n", servername, portno);

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

	printf("connection successful\n");
	
//successful connection->get user input for url
while (1) {
	urequest = malloc(256);
	sresponse = malloc(100000);
	printf("Please enter full URL link: " );		

//	scanf("%[^\n]%*c", urequest);
	scanf("%s",urequest);
	
	printf("%s\n%d\n", urequest, strlen(urequest));

//send url as message to server
	n = write(sockfd,urequest,strlen(urequest));
 
    if (n < 0) 
         error("ERROR writing to socket");
}
//recieve html code string

/*    n = read(sockfd,sresponse,19999);

    if (n < 0) 
         error("ERROR reading from socket");
	
//	printf("server reply: %s\n", sresponse);

//Print server reply string to file "httpOutput"
	printf("server reply sent to httpOutput");
	FILE	*outputfp;
	outputfp = fopen("httpOutput", "w");
	fprintf(outputfp, "%s", sresponse);
*/
// close socket and delete file pointer
//    fclose(outputfp);

    close(sockfd);
    return 0;
}

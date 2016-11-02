#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h> 

void error(const char *msg);
void process1(void);

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void process1(void)
{

    int sockfd, n, i;
    struct sockaddr_in serv_addr;
    struct hostent *server;
	int portno = 80;
	char *hostname = "www.unt.edu/academics.htm";
	char firstpart[100];
	char secondpart[100];
	char *request;
	char *response;

	request = malloc(100);
	response = malloc(50000);

	for (i=0;i < strlen(hostname); i++)
	{
		if (hostname[i] == '/')
		{
			firstpart[i] = '\0';
			break;
		}
		else
			firstpart[i] = hostname[i];
	}

	int h = 0;
	for (i; i <= strlen(hostname); i++)
	{
		secondpart[h] = hostname[i];
		h++;
	}
  
	printf("\nhostname: %s\n", hostname);
	printf("firstpart = %s\n", firstpart);
	printf("secondpart = %s\n", secondpart);



  sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    server = gethostbyname(firstpart);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

	printf("\n%s = ", server->h_name);
	unsigned int j = 0;
	while (server->h_addr_list[j] != NULL)
	{
		printf("%c", inet_ntoa(*(struct in_addr*)(server->h_addr_list[j])));
		j++;
	}

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);

    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
	{
       	 error("ERROR connecting");
	 close(sockfd);
	 exit(0);
	}

	printf("\nconnection successful\n\n");

	sprintf(request, "HEAD %s HTTP/1.1\r\nHost: %s\r\n\r\n", secondpart, firstpart);
	printf("\n%s\n",request);

	send(sockfd, request, strlen(request),0);
	recv(sockfd, response, 49999, 0);

	printf("\n%s\n", response);	
/*
	FILE * outputfp;
	outputfp = fopen("httpoutput","w");
	fprintf(outputfp, "%s", response);
	int size = ftell(outputfp);
	fclose(outputfp);
	printf("%d\n\n", size);
*/		

    close(sockfd);
}

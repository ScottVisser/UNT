#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>

//prototypes
int processUrl(char *url);
void error(const char *msg);

//error func
void error(const char *msg)
{
    perror(msg);
    exit(1);
}
//process func
int processUrl(char *url)
{
	//variables
	int r = 0;
	time_t t;
	char timestring[25];
	int i, j;
	int sockfd, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char firstpart[100];
	char *secondpart;
	int portno = 80;
	char *request;
	char *response;
	char *status;
	status = malloc(50);
	request = malloc(100);
	secondpart = malloc(100);
	response = malloc(100000);

	// parse the url input
	for (i=0;i < strlen(url); i++)
	{
		if (url[i] == '/')
		{
			firstpart[i] = '\0';
			break;
		}
		else
			firstpart[i] = url[i];	
	}


	j=0;
	for (i; i <= strlen(url); i++)
	{
		secondpart[j] = url[i];
		j++;	
	}

	if (strlen(secondpart) == 0)
	{ 
		secondpart[0] = '/';
		secondpart[1] = '\0';
	}


  sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    server = gethostbyname(firstpart);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }


//	printf("\n%s\n", server->h_name);
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
	 return 0;
	}

	printf("\nconnection successful\n");

	sprintf(request, "HEAD %s HTTP/1.1\r\nHost: %s\r\n\r\n", secondpart, firstpart);
	printf("\n%s\n",request);

	send(sockfd, request, strlen(request),0);
	recv(sockfd, response, 99999, 0);

	int x = 0;
	while (response[x] != '\n')
	{
		status[x] = response[x];
		x++;
	}
	status[x] = '\0';

	if (strcmp(status, "HTTP/1.1 200 OK ") == -1)
	{
		printf("Header: %s\n", status);
//		timestring = malloc(30);
		t = time(NULL);
		snprintf(timestring, sizeof(timestring), "%s", ctime(&t));
//		timestring = ctime(&t);
		FILE	*outputfp;
		outputfp = fopen(timestring, "w");
		fprintf(outputfp, "%s", response);
		fclose(outputfp);
		printf("Web object: %s saved to cache file: %s\n\n", url, timestring);
		r = 1;
	}
	else
	{	
		printf("Error: page cannot be cached\n");
		printf("Status: %s\n", status);
		r = 2;
	}

	close(sockfd);
	return r;

};

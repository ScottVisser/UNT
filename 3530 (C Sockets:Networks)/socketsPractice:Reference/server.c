#include "server.h"

//// Main function ///
int main(void)
    {



     int sockfd, newsockfd, portno, n;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;

	char *urequest = "www.google.com/";
	char *sresponse;
	pid_t pid;

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

////// Listen and accept new connection ////
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, 
                 &clilen);
      if (newsockfd < 0) 
          error("ERROR on accept");

///// Procesing once connection is made ///////

	int returnStatus;

	while (1)
	{
		urequest = malloc(256);
		n = read(newsockfd,urequest,255);
		if (strcmp(urequest, "quit") == 0)
		 break;
		printf("URL requested: %s\n",urequest);

		pid = fork();	
		if (pid == 0)
			processUrl(urequest);
		else
		{
			waitpid(pid, &returnStatus, 0);
		}


/*	sysinput = malloc(strlen("GET ")+strlen(urequest)+strlen(" 80 > output1") + 1);
	strcat(sysinput, "GET ");
	strcat(sysinput, urequest);
	strcat(sysinput, " 80 > output1"); // create sys call string
	system(sysinput); // system call function to place http objectin a file
	
	FILE * outputfp; // create file pointer
	outputfp = fopen("output1", "r");
	int count;
	count = 0;

	// find num of characters in file 
	fseek(outputfp, 0, SEEK_END);
	count = ftell(outputfp);
	fseek(outputfp, 0, SEEK_SET);

	// allocate space for http output buffer/*
	sresponse = malloc(20000);
	httpOutput = malloc(count);

	// read output file contents into http output buffer for client
	fread (httpOutput, 1, count, outputfp);
	fclose(outputfp);

	// write buffer back to client
	n = write(newsockfd, httpOutput, count);

/////Done processing, close connection //////
//	exit(0);
	int ret;
	ret = remove("output1");
*/
	}
	close(newsockfd);
	close(sockfd);
return 0;
}
//// End of Main function and program ///


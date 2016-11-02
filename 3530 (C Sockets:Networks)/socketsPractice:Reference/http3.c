#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(void)
{

	int sockfd, newsockfd, portno, n;
	socklen_t clilen;
	struct sockaddr_in serv_addr;
	//struct sockaddr_in c_addr;


	int i;
	char *url = "www.google.com/fuckoff.htm";
	char firstpart[100];
	char secondpart[100];

	for (i=0;i < strlen(url); i++)
	{
		if (url[i] == '/')
		{
			strncpy(firstpart, url, i);
			firstpart[i] = '\0';
			break;
		}
	}


	for (i; i < strlen(url); i++)
	{
		strcat(secondpart, &url[i]);
		break;
	}

	printf("\nurl: %s %d\n", url, strlen(url));
	printf("firstpart = %s\n", firstpart);
	printf("secondpart = %s\n", secondpart);






return 0;
}

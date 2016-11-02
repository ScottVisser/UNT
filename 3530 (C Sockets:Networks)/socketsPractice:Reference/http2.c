#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


int main(void)
{
	int i;
	char *hostname = "www.unt.edu/academics.htm";
	char firstpart[100];
	char secondpart[100];

	for (i=0;i < strlen(hostname); i++)
	{
		if (hostname[i] == '/')
		{
			strncpy(firstpart, hostname, i);
			firstpart[i] = '\0';
			break;
		}
	}

	for (i; i < strlen(hostname); i++)
	{
		strcat(secondpart, &hostname[i]);
		break;
	}
  
	printf("\nhostname: %s\n", hostname);
	printf("firstpart = %s\n", firstpart);
	printf("secondpart = %s\n", secondpart);

return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(void)
{
	char *buffer;
	buffer = malloc(1000);
/*
//	fgets(buffer, 10000, stdin);

//	bzero(buffer, sizeof(buffer));
	scanf("%[^\n]%*c", buffer);

	printf("%d\n", strlen(buffer));
		
	printf("%s\n", buffer);
	system(buffer);

	system("HEAD / HTTP/1.1|telnet www.google.com 80");
	printf("HEAD / HTTP/1.1");
	system("HEAd / HTTP/1.1");
*/

	FILE *fp;
	fp = fopen("test1", "r");	

	int size1;
//	size1 = fseek(fp,0,SEEK_END);
	size1 = 0;
	char c;
	do
	{
		c = fgetc(fp);
		size1++;	
	} while (c != EOF);
	printf("%d characters i think\n", size1);

	return 0;
}

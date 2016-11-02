#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>

struct tcpSeg
{
	unsigned short int destPort, sourcePort;
	int seqNum;
	int ackNum;
	short int reserve;
	short int recWindow;
	short int checksum;
	short int urgentdp;
	int options;
};

struct tcpDataSeg
{
	unsigned short int destPort, sourcePort;
	int seqNum;
	int ackNum;
	short int reserve;
	short int recWindow;
	short int checksum;
	short int urgentdp;
	int options;
	char data[128];
};




void error(const char *msg);

void error(const char *msg)
{
    perror(msg);
    exit(1);
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <time.h>
#define NREQUEST 7
//typedef enum { false, true } bool;

int random_number(int min_num, int max_num);
void random_request(bool request[]);
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int ticket[7];
    bool request[NREQUEST]; /* 1 for buy 0 to cancel */
    /* To generate aleatory numbers, the seed only is called one time */
    srand (time(NULL));
    /* call funtion to set the action in 7 request */
    random_request(request);

    char buffer[256];
    char buf_in[256];
    char buf_out[256];
    
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);

    /* Now connect to the server */
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

   /* Now ask for a message from the user, this message will be read by server  */
//    printf("Please enter the message: ");
    bzero(buffer,256);
//    fgets(buffer,255,stdin);
     
     int z=0; /* Counter of request */
     int y=0; /* number of tickets received */
	for (z=0;z<NREQUEST;z++){
	    printf("Request %d --> ", z+1); 
	    if (request[z]){ 
        	strcpy(buf_out,"buy");
	    } else {
		strcpy(buf_out,"cancel");
     	}
		/* Send message to the server */
		n = write(sockfd,buf_out,strlen(buf_out));
		if (n < 0) error("ERROR writing to socket");
		if (request[z]){ /* the client received the ticket */
			bzero(buf_in,256);
			n = read(sockfd,buf_in,255);
			/* Convert string buffer into a int ticket[] */
			ticket[y]=atoi(buf_in);
			printf("Recieved the ticket %d \n", ticket[y++]);
		} else { /* The client wait for the IDTicket peticion of server */ 
			bzero(buf_in,256);
            n = read(sockfd,buf_in,255);
		if (strcmp(buf_in,"IDTicket") == 0){
			int t=(y>0)?ticket[--y]:12345;
			printf("Sending the ticket %d to cancel.\n", t);
			/* covert int t to a string buffer */			
			bzero(buf_in,256);
			sprintf(buf_out, "%d", t);
			n = write(sockfd,buf_out,strlen(buf_out));
    		if (n < 0) error("ERROR writing to socket");
		}
	}
    /* Now read server response */
/*    bzero(buffer,256);
    n = read(sockfd,buffer,255);

    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
*/    
    } /* for llop */
    close(sockfd);
    return 0;
}

/* Function to generate random number */
int random_number(int min_num, int max_num)
{
            int result=0,low_num=0,hi_num=0;
            if(min_num<max_num)
            {
                low_num=min_num;
                hi_num=max_num+1; // this is done to include max_num in output.
            }else{
                low_num=max_num+1;// this is done to include max_num in output.
                hi_num=min_num;
            }
//          srand(time(NULL));
            result = (rand()%(hi_num-low_num))+low_num;
            return result;
}

void random_request(bool request[])
{
	int n,result;
	for (n=0;n<NREQUEST;n++){
		result=random_number(0,9);
		if (result==9) /* if is 10% */
			request[n]=0; /* cancel */
		else  /* if 90% */
			request[n]=1; /* buy */	
	printf(" Request %d = %d \n", n+1, request[n]);
	}
} 

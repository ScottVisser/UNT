/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <time.h>
//typedef enum {false, true} bool;

int random_number(int min_num, int max_num);
void doprocessing (int sock, int ticket[],bool ticket_status[], int* a_tickets);

void error(const char *msg)
{
    perror(msg);
    exit(1);
} 

int main( int argc, char *argv[] )
{
   pid_t pid;
   int sockfd, newsockfd, portno;
   socklen_t clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int  n;
   int i,ticket[10];
   bool ticket_status[10]; /* value 1 disposable, 0 given */
   int available_tickets=0;

   /* To generate aleatory numbers, the seed only is called one time */ 
   srand (time(NULL));
   /* create Database of tickets */
   for (i=0;i<10;i++){
      ticket[i]=random_number(10000, 99999);
      ticket_status[i]=true;
      available_tickets+=1;	
    printf("%d %d %d \n", i, ticket[i], ticket_status[i]);
   }
    printf("Available Tickets = %d\n", available_tickets);


   /* Check if the port was introduced in the argument*/	
   if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
   } 
   /* First call to socket() function */
   if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) == -1 )
      error("ERROR in socket");
      

//   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0)
      error("ERROR opening socket");
      
      /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = atoi(argv[1]);
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   
   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
      error("ERROR on binding");
      
   /* Now start listening for the clients, here
   * process will go in sleep mode and will wait
   * for the incoming connection
   */
   
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   
   while (1) 
   {
      newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
      if (newsockfd < 0)
         error("ERROR on accept");
      char *addr1, *addr2;         
      addr1=inet_ntoa(cli_addr.sin_addr);
      printf("Client Address 1: %s\n", addr1);
      /* Show Client's IP  */

      /* Create child process */
      pid = fork();
      if (pid < 0)
         error("ERROR on fork");
               
      if (pid == 0)
         {
         /* This is the client process */
         close(sockfd);
		 doprocessing(newsockfd,ticket,ticket_status,&available_tickets);
         exit(1);
         }
      else
         {
         close(newsockfd);
         }
		 printf("%d\n",available_tickets);
   } 
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

void doprocessing (int sock, int ticket[],bool ticket_status[], int* a_tickets)
{
 
   int n,c;
   int y; /* Counter of ticket */
   int t; /* ticket to cancel */
   char buf_in[256];
   char buf_out[256];
   char buffer[6];
   
 do {

   /* Empty bufer in */
   bzero(buf_in,256);
   
   n = read(sock,buf_in,255);
   if (n < 0){
      error("ERROR reading from socket");
   } else  if(n==0){    /*if read  NULL (Desconection) of client...*/
	/*...print end of conection */
       printf("Ending the conection\n");   
   } else { 
		//printf("Here is the message: %s\n",buf_in);
		printf("The client requests %s --> ",buf_in);
		if (strcmp(buf_in,"buy") == 0){ /* option buy */	
//      pick_ticket(ticket,ticket_status)
      for (y=0;y<10;y++){
	if (ticket_status[y]==1) {ticket_status[y]=0; break;}
	if (y==9){ y=-1; break;}	
      }
      if (y==-1)	{ /* There are no dispensable tickets */
		printf("Sold Out, Sorry there are no more tickets");
        strcmp(buf_out,"0");
	printf("Sorry, We don't have any more tickets available\n");
      } else {	
      	*a_tickets-=1; // remove 1 of the available tickets */
		printf("Sending the ticket %d\n", ticket[y]);
//      bzero(buffer,256);
      	/* covert int ticket[] to a string bufer */
      	sprintf(buf_out, "%d", ticket[y]);
      }
      	n = write(sock,buf_out,strlen(buf_out));	
	bzero(buf_out,256);
      

   } else {     /*the clietn requires cancel */
      /* Send string to rquest the ticket to cancel */
//    bzero(buffer,256);
	printf("\nSending request for ID to cancel...\n");
      strcpy(buf_out,"IDTicket");
      n = write(sock,buf_out,strlen(buf_out));
      printf("Receiving ticket to cancel --> ");
      /* Empty bufer in */
      bzero(buf_in,256);
      n = read(sock,buf_in,255);
      /* Convert string buffer into an int t */
      t=atoi(buf_in);
      printf("Ticket %d canceled \n", t);
//    printf("Ticket %s \n", buf_in);
//      printf("The client requests cancel %d ", t);
   /* Empty buffer out */
   }
   printf("Available Tickets = %d\n", *a_tickets);

   bzero(buf_out,256);
//   n = write(sock,buf_out,strlen(buf_out));
//   n = write(sock,"I got your message",18);
   
   if (n < 0)
      error("ERROR writing to socket");
   }
 }while (n!=0);/*While the client doesnt close the conection*/
//   printf("Finalizo \n");  
}

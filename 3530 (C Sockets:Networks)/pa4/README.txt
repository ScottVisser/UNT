Programing assignment 4
Scott Visser

ReadMe.txt file

Compilation instructions:
As per the assignment page provided, the server should run on cse01 and the client on cse02. The Name of the file being transfered should be included as an input argument on the client side.

ex:
(server side first on cse01)
gcc server.c -o server1
./server

(client side)
gcc client.c -o client1
./client1 Name_of_File.txt 

***Note: both client.c and server.c share a common header file (clientServer.h).  This file must be included in both directories where the c files are being executed from ***

Process:
The server side will prompt the user for a designated destination or server port.  
Please try to avoid using ports with an existing function (80,25,ect).  
Once socket is open, input the same port number on the client side to connect the client to the server. 
Once they are connected, the client generates a tcp connection request segment:

The destination port is the input from before and the source port is obtained using gethostname() and are the same for all tcp segs

the seq num for initial requests from the client is generically set to 10
the seq num for initial responses from the server is generically set to 42

The reserve member of the struct is the 16 bits that contain header lengh, reserved space, and flags.  the leftmost 4 bits of the reserve member represent the header length in multiples of 32 bits.  Since there are 24 bytes in each seg, there would be 6 x 32 bits or 0110.  The right most 6 bits are the flags.

An example of reserve member:
header length = 6 (x32bits) = 0110
reserved/offst = 0 = 000000
flags (ex: ACK) = 010000
=> tcpSeg.reserve = 0110000000010000 = 24592

	
process: 
1) sockets created
2) client generates, prints, and sends tcp open connection request (syn = 1)
3) Server recieves and prints segment\
4) server checks flags
5) server generates, prints, and sends tcp connection granted seg (syn =1 ack =1)
6) Clients recieves and prints tcp response
7) Client checks flags, generates, prints, and sends connection granted ACK tcp seg (Ack =1)
8) Server recieves and prints client's tcp Ack segment
9) Client generates file pointer to argument txt file
10) Client generates and sends tcp data seg containing 128 byte data payload
11) Client waits for ack before sending the next data seg
12) Steps 9 and 10 repeated until file is fully transmitted and all acks recieved
13) For every data seg recieved on server side, the payload is printed to a txt file named "File_Recieved_from_Client.txt" and an ACK seg is sent with the acknowledgement # set to size of payload in bytes
14) Clients generates, prints, and sends tcp close seg (fin=1)
15) Server recieves, prints, and checks flags of client's tcp close request seg
16) Server generates, prints, and sends tcp close ACK response
17) Server generates, prints, and sends tcp close FIN response
18) Client recieves ACK and FIN close connection tcp responses and prints them
19) Client generates, prints, and sends ACK 
20) Server recieves and prints Clients ACK message
21) Both Server and Client terminate process.


Notes:
My program works correctly to the best of my understanding of the requirements outlined on the assignment page except:
-the tcp segs sent/recieved on both the client and server side output is not printed to a file just to the console
-only the data payload of tcp segs recieved on the server side are printed to a file
-checksum is never generated and remains 0 through the whole process.

I included my 1KB test file in the submission folder, but my program should be able to run with any other file as long as it is included as an command input argument.  I noticed that an additional tcp seg data seg is sent with a payload of 0 if the file is exactly 1024 bytes, but it is ACKed and doesn't effect the overall file output.



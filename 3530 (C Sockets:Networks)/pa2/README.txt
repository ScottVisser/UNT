Scott Visser
CSCE 3530
Programming assignment 2

HOW TO COMPILE/RUN
on any of the unt cse machines, simply compile with:
gcc server.c -o runserver
./runserver
(on other machine)
gcc client.c -o runclient
./runclient

There are no additional command line arguments.

The server first prompts the user to enter a 4 digit port number to connect to the client through.
Once socket is created. server waits for clients connection.

The client process prompts user for the server name and port number.
Once connection is made user is prompted to input a url.



HOW IT WORKS/WHAT IT DOES

When the user submits the url, the client sends that url message to the server process.
The server process parses the url for the domain and or suffexs
The server process is forked and the child process opens another tcp socket using port 80
The server parseses the http response header
If the header begins "200 OK", the server caches the full http object into a file
The cached http object file is named after the date, but NOT in the format described on the assignment page

No message is passed back to the client.
The client will be asked to input another url and it will be sent to the server
This will loop 5 times


MY CODE IS MISSING
blacklist functions
a list.txt file to track the cached http objects

// References: 
// http://www.bogotobogo.com/cplusplus/sockets_server_client.php
// https://docs.oracle.com/javase/tutorial/networking/sockets/definition.html
// http://www2.cs.uh.edu/~paris/4330/Sockets.html 

// !*! http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html 

/* An Internet Domain Socket server that accomplishes interprocess communication (IPC)
   The port number is passed as an argument */



#include <netinet/in.h>  // contains constants and structures needed for internet domain addresses.
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <unistd.h>

// Called when a system call fails. 
void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    // sockfd and newsockfd are file descriptors, i.e. array subscripts into the file descriptor table . These two variables store the values returned by the socket system call and the accept system call.
    // portno stores the port number on which the server accepts connections.
    // n is the return value for the read() and write() calls; i.e. it contains the number of characters read or written.
     int sockfd, newsockfd, portno, n; 
     
     // clilen stores the size of the address of the client. This is needed for the accept system call.
     socklen_t clilen;
     // server reads characters from the socket connection into buffer.
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);

     if (sockfd < 0) 
        error("ERROR opening socket");

    // sets all values in a buffer to zero. Thus, this line initializes serv_addr to zeros.
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
              error("ERROR on binding");

     listen(sockfd, 5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");

     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) 
        error("ERROR reading from socket");

     printf("Message recieved: %s\n",buffer); // Server recieves message 
     n = write(newsockfd,"Server recieved message.",25); // Server sends confirmation to client 
     if (n < 0) 
        error("ERROR writing to socket");

     return 0; 
}
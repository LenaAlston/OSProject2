// References: 

// http://www2.cs.uh.edu/~paris/4330/Sockets.html 
// http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html 

#include <netdb.h> 
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

const int BUFF_MAX = 256;

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, port, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char *family[BUFF_MAX], *person[BUFF_MAX], *plaza[BUFF_MAX], *response[BUFF_MAX];
    int arrTime, duration;
    FILE *file = fopen("input.txt", "r+");

    char buffer[BUFF_MAX];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    port = atoi(argv[2]);
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
    serv_addr.sin_port = htons(port);

    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    
    bzero(buffer,BUFF_MAX);
    
    while (!feof(file)) {

        fgets(buffer,255,file);
        n = write(sockfd,buffer,strlen(buffer));

        if (n < 0) 
             error("Client ERROR writing to socket");

        bzero(buffer,BUFF_MAX);
        n = read(sockfd,buffer,BUFF_MAX-1);

        if (n < 0) 
             error("Client ERROR reading from socket");

        printf("%s\n",buffer);  //prints buffer contents written from server 
    }
    printf("end.\n");

    return 0;
}
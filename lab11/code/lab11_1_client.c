#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int sockfd;
    int bytes;
    socklen_t len;
    struct sockaddr_un address;
    int result;
    char buff[100];

    /*  Create a socket for the client.  */

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    /*  Name the socket, as agreed with the server.  */

    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
    len = sizeof(address);

    /*  Now connect our socket to the server's socket.  */

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1) {
        perror("oops: cannot connect!");
        exit(1);

    }

    /*  We can now read/write via sockfd.  */

    bytes = read(0,buff,sizeof(buff));
    if (bytes > 0) {
        printf("read %d bytes from stdin\n", bytes);
        if (write(sockfd,buff,bytes-1) != bytes-1 )
            perror("write error") ;

        bytes=read(sockfd, buff, 100);
        if (bytes>0){
            buff[bytes]='\0';
            printf("read %d bytes from server\n", bytes);
            printf("message from server = %s\n", buff);

        }

    }
    close(sockfd);
    exit(0);

}

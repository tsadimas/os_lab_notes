#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MAX 100

int main(int argc, char **argv)
{
    int sfd, n;
    socklen_t len;
    char sline[MAX], rline[MAX + 1];
    struct sockaddr_in saddr;

    if (argc != 2)
    {
        printf("Usage: %s ipaddress\n", argv[0]);
        return -1;
    }

    sfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &saddr.sin_addr);
    saddr.sin_port = htons(2910);

    printf("Client Running\n");
    while (fgets(sline, MAX, stdin) != NULL)
    {
        len = sizeof(saddr);
        sendto(sfd, sline, strlen(sline), 0, (struct sockaddr *)&saddr, len);
        n = recvfrom(sfd, rline, MAX, 0, NULL, NULL);
        rline[n] = 0;
        fputs(rline, stdout);
    }

    return 0;
}

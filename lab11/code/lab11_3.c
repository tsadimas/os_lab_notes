#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    struct in_addr addr;
    if (argc < 2)
    {
        fprintf(stderr, "usage: ./quad_to_byte [ip_address]\n");
        return -1;
    }

    char *byte_order = malloc(sizeof(argv[1]));
    if (!byte_order)
    {
        fprintf(stderr, "Could not allocate memory for conversion.\n");
        return -1;
    }

    // Convert address to byte order
    if (!inet_pton(AF_INET, argv[1], &addr))
    {
        fprintf(stderr, "Could not convert address\n");
        free(byte_order);
        return -2;
    }

    // Print out network byte order
    fprintf(stdout, "Network byte order: %d\n", addr.s_addr);

    // Convert it back to our dot quad to verify
    if (inet_ntop(AF_INET, &addr.s_addr, byte_order, INET_ADDRSTRLEN) == NULL)
    {
        fprintf(stderr, "Could not convert byte to address\n");
        fprintf(stderr, "%s\n", strerror(errno));
        free(byte_order);
        return -3;
    }

    // Display our dot quad converted from the network byte order
    fprintf(stdout, "Dot quad: %s\n", byte_order);
    free(byte_order);
    return 0;
}

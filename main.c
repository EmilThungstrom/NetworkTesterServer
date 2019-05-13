#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        perror("Usage: server <port> <buffer size>");
        exit(1);
    }

    const int LST_PORT = atoi(argv[1]);
    const int BUFFER_SIZE = atoi(argv[2]);

    int socketId = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddr;
    bzero((char*)&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(LST_PORT);
    serverAddr.sin_addr.s_addr  = INADDR_ANY;
    bind(socketId, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    listen(socketId, 5);

    struct sockaddr_storage serverStorage;
    socklen_t addr_size = sizeof serverStorage;
    printf("Setup complete, listening for connections...\n");
    int newSocket = accept(socketId, (struct sockaddr*)&serverStorage, &addr_size);
    printf("New connection...\n");

    unsigned char buffer[BUFFER_SIZE];
    printf("Starting data transfer...\n");
    while(read(newSocket, buffer, BUFFER_SIZE)){
        printf("%s\n", buffer);
    }
    printf("Transfer complete!\n");

    close(newSocket);
    close(socketId);

}
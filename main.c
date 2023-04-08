#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <unistd.h>
#include "server/Server.h"

void launch(struct Server *server) {

    while(1) {
        char buffer[30000];
        printf("=========Waiting for new connection=========\n");
        int addrlen = sizeof(server->address);
        unsigned int new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t*)&addrlen);

        read( new_socket , buffer, 30000);

        printf("%s\n",buffer);
        write(new_socket , "Hello Buddy!" , 17);
        close(new_socket);
    }

}


int main () {

    WSADATA wsaData;
    int iResult;
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        perror("WSAStartup failed: %d\n");
        exit(1);
    }
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 10, launch);
    server.launch(&server);
    printf("Server created\n");
    return 0;
}


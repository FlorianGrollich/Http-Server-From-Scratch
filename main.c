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
        int new_socket = -1;
        new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t*)&addrlen);
        if (new_socket == -1) {
            perror("accept failed");
        } else {
            int valread = read(new_socket, buffer, 30000);
            if (valread == -1) {
                perror("read failed");
            }
            int result = write(new_socket, "Hello Buddy!", 12);
            if (result == -1) {
                perror("write failed");
            }
            if (close(new_socket) == -1) {
                perror("close failed");
            }
        }
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


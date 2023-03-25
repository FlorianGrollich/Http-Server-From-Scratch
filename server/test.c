#include <stdio.h>
#include <unistd.h>
#include "Server.h"


void launch(struct Server *server) {
    char buffer[30000];
    printf("=========Waiting for new connection=========\n");
    int addrlen = sizeof(server->address);
    int new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t*)&addrlen);

    read( new_socket , buffer, 30000);
    printf("%s\n",buffer );
    write(new_socket , "Hello Buddy!" , 17);
    close(new_socket);
}


int main () {
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 10, launch);
    printf("Server created\n");
    return 0;
}


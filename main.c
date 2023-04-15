#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
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
            printf("%s\n", buffer);
            char *response = "HTTP/1.1 200 OK\r\n"
                             "Content-Type: text/html\r\n"
                             "Content-Length: 146\r\n"
                             "\r\n"
                             "<!DOCTYPE html>\n"
                             "<html>\n"
                             "<head>\n"
                             "  <title>My Page</title>\n"
                             "</head>\n"
                             "<body>\n"
                             "  <h1>Hello, world!</h1>\n"
                             "  <p>This is a paragraph.</p>\n"
                             "</body>\n"
                             "</html>\n";
            int result = write(new_socket, response, strlen(response));
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

    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 10, launch);
    server.launch(&server);
    printf("Server created\n");
    return 0;
}


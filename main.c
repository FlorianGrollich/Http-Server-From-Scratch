#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include "server/Server.h"
#include "server/HTTPRequest.h"
#include "server/HTTPResponse.h"
#include "handleRoutes.h"

void launch(struct Server *server) {

    char* msg[10000] = {};
    int msg_count = 0;

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

            struct HTTPRequest request = http_request_constructor(buffer);


            if(request.Method ==  1) {
                msg[msg_count] = request.Payload;
                msg_count++;
            }

            char* filename = handle_routes(request.URI);

            char* response = get_HTML_response(filename, msg, msg_count);




            // Send the response
            int result = write(new_socket, response, strlen(response));
            free(response);
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


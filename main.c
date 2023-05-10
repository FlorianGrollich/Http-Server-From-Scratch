#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
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
            char *filename = "index.html";
            FILE *fp = fopen(filename, "r");
            if (fp == NULL) {
                perror("file open failed");
                exit(1);
            }
            fseek(fp, 0, SEEK_END);
            long fsize = ftell(fp);
            fseek(fp, 0, SEEK_SET);

            char *html = malloc(fsize + 1);
            if (html == NULL) {
                perror("memory allocation failed");
                exit(1);
            }

            size_t read_size = fread(html, 1, fsize, fp);
            if (read_size != fsize) {
                perror("file read failed");
                exit(1);
            }

            fclose(fp);

            html[fsize] = '\0';
            char response[4096];
            snprintf(response, 4096,
                     "HTTP/1.1 200 OK\r\n"
                     "Content-Type: text/html\r\n"
                     "Content-Length: %ld\r\n"
                     "\r\n"
                     "%s",
                     fsize, html
            );

            // Send the response
            int result = write(new_socket, response, strlen(response));
            if (result == -1) {
                perror("write failed");
            }
            if (close(new_socket) == -1) {
                perror("close failed");
            }

            // Free the memory allocated for the HTML content
            free(html);
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


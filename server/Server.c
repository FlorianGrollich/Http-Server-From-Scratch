//
// Created by F-Gro on 23.03.2023.
//
#include "Server.h"

struct Server server_constructor(int domain, int service, int protocol, u_long innterface, int port, int backlog, void(*launch)(struct Server *server)) {
    struct Server server;

    server.domain = domain;
    server.service = service;
    server.protocol = protocol;
    server.innterface = innterface;
    server.port = port;
    server.backlog = backlog;
    server.launch = launch;

    server.address.sin_family = domain;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(innterface);

    server.socket = socket(domain, service, protocol);

    if(server.socket < 0) {
        perror("Socket creation error: ");
        exit(1);
    }

    if((bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address))) < 0) {
        perror("Bind error: ");
        exit(1);
    }

    if((listen(server.socket, server.backlog)) < 0) {
        perror("Listen error: ");
        exit(1);
    }


    return server;
}
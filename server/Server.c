//
// Created by F-Gro on 23.03.2023.
//
#include "Server.h"

struct Server server_constructor(int domain, int service, int protocol, u_long innterface, int port, int backlog, void(*launch)(void)) {
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




    return server;
}
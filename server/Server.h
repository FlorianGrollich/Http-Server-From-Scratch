#ifndef Server_h
#define Server_h

#include <sys/socket.h>
#include <netinet/in.h>

struct Server {
    int domain;
    int service;
    int protocol;
    u_long innterface;
    int port;
    int backlog;

    struct sockaddr_in address;

    unsigned int socket;

    void (*launch)(struct Server *server);
};


struct Server server_constructor(int domain, int service, int protocol, u_long innterface, int port, int backlog, void(*launch)(struct Server *server));

#endif /* Server_h */

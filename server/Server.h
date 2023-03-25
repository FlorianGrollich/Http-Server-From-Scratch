#ifndef Server_h
#define Server_h

#include <winsock2.h>
#include <ws2tcpip.h>// include this header for u_long type

struct Server {
    int domain;
    int service;
    int protocol;
    u_long innterface;
    int port;
    int backlog;

    struct sockaddr_in address;

    int socket;

    void (*launch)(void);
};

struct Server server_constructor(int domain, int service, int protocol, u_long innterface, int port, int backlog, void(*launch)(void));

#endif /* Server_h */

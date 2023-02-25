#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ws2spi.h>


int main() {
    int server_fd;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("cannot create socket");
        return 0;
    }

    struct sockaddr_in address;
    const int PORT = 8080;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT); if (bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0)
    {
        perror("bind failed");
        return 0;
    }

    return 0;

}

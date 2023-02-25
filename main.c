#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ws2spi.h>


int main() {
    int server_fd;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {

    }

    return 0;

}

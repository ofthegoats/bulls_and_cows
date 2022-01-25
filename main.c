#include "game.h"

#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int port = 8080;
    if (argc >= 2) port = atoi(argv[1]);
    int                sock_fd, player1, player2;
    struct sockaddr_in address;
    int                opt = 1;
    int                addrlen = sizeof(address);

    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        return EXIT_FAILURE;
    }

    if ((setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        == -1) {
        perror("setsockopt failed");
        return EXIT_FAILURE;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(sock_fd, (struct sockaddr*)&address, sizeof(address)) == -1) {
        perror("bind failed");
        return EXIT_FAILURE;
    }

    if (listen(sock_fd, 2) == -1) {
        perror("listen failed");
        return EXIT_FAILURE;
    }

    if ((player1 = accept(sock_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen))
        == -1) {
        perror("accept failed");
        return EXIT_FAILURE;
    }

    if ((player2 = accept(sock_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen))
        == -1) {
        perror("accept failed");
        return EXIT_FAILURE;
    }

    gameloop(player1, player2);

    return EXIT_SUCCESS;
}

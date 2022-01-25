#include "game.h"

#include "basic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void count_matches(char secret[4], char attempt[4], struct counts* c)
{
    int i;
    int secret_counts[10] = {0};
    int attempt_counts[10] = {0};
    int matches = 0;
    // reset count
    c->bulls = 0;
    c->cows = 0;
    for (i = 0; i < 4; i++) {
        secret_counts[char_to_int(secret[i])]++;
        attempt_counts[char_to_int(attempt[i])]++;
    }
    for (i = 0; i < 4; i++) {
        if (secret[i] == attempt[i])
            c->bulls++;
        else if (secret_counts[char_to_int(attempt[i])] > 0)
            c->cows++;
    }
}

bool valid_code(char code[4])
{
    int i;
    for (i = 0; i < 4; i++)
        if (code[i] < 48 || code[i] > 57) return false;
    return true;
}

void get_code(int socket, char code[4])
{
    ssize_t bytes_read;
    char    buffer[1024];
    // check if read was successful
    // and code is valid
    do {
        send(socket, "input secret code: ", 20, 0);
        bytes_read = read(socket, buffer, 1024);
        printf("%s, bytes_read = %zd\n", __FUNCTION__, bytes_read);
        if (bytes_read == -1) {  // error case
            perror("failure reading over socket\n");
            exit(EXIT_FAILURE);
        } else if (bytes_read != 5 || !valid_code(buffer)) {
            send(socket, "code needs to be 4 numbers\n", 28, 0);
        }
    } while (bytes_read != 5 || !valid_code(buffer));
    strncpy(code, buffer, 4);
}

void get_attempt(int socket, char code[4])
{
    ssize_t bytes_read = 0;
    char    buffer[1024];
    // check if read was successful
    // and code is valid
    do {
        send(socket, "input attempt: ", 16, 0);
        bytes_read = read(socket, buffer, 1024);
        printf("%s, bytes_read = %zd\n", __FUNCTION__, bytes_read);
        if (bytes_read == -1) {  // error case
            perror("failure reading over socket\n");
            exit(EXIT_FAILURE);
        } else if (bytes_read != 5 || !valid_code(buffer)) {
            send(socket, "code needs to be 4 numbers\n", 28, 0);
        }
    } while (bytes_read != 5 || !valid_code(buffer));
    strncpy(code, buffer, 4);
}

void send_count(int socket, struct counts* c)
{
    char str[9];
    sprintf(str, "B:%d/C:%d\n", c->bulls, c->cows);
    send(socket, str, 9, 0);
}

void gameloop(int player1, int player2)
{
    char          player1_code[4];
    char          player2_code[4];
    char          player1_attempt[4];
    char          player2_attempt[4];
    struct counts c = {0, 0};
    get_code(player1, player1_code);
    get_code(player2, player2_code);
    while (c.bulls < 4) {
        // player 1 goes first
        get_attempt(player1, player1_attempt);
        count_matches(player2_code, player1_attempt, &c);
        send_count(player1, &c);
        if (c.bulls == 4) announce_winner(player1, player2);
        // player 2
        get_attempt(player2, player2_attempt);
        count_matches(player1_code, player2_attempt, &c);
        send_count(player2, &c);
        if (c.bulls == 4) announce_winner(player2, player1);
    }
}

void announce_winner(int winner, int loser)
{
    send(winner, "you won\n", 9, 0);
    send(loser, "you lost\n", 10, 0);
    exit(EXIT_SUCCESS);
}

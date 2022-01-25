#ifndef GAME_H_
#define GAME_H_

#include <stdbool.h>

struct counts {
    int cows;   // number exists, but is in wrong position
    int bulls;  // number in correct position
};

void count_matches(char[4], char[4], struct counts*);
void get_code(int, char[4]);
void get_attempt(int, char[4]);
void send_count(int, struct counts*);
bool valid_code(char[4]);
void gameloop(int, int);
void announce_winner(int, int);

#endif  // GAME_H_

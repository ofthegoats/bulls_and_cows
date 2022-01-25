#include "game.h"

#include <assert.h>

int main(int argc, char* argv[])
{
    struct counts c = {0, 0};
    count_matches("1234", "9305", &c);
    assert(c.bulls == 0 && c.cows == 1);
    count_matches("5678", "9305", &c);
    assert(c.bulls == 0 && c.cows == 1);
    count_matches("9012", "9305", &c);
    assert(c.bulls == 1 && c.cows == 1);
    count_matches("9087", "9305", &c);
    assert(c.bulls == 1 && c.cows == 1);
    count_matches("1087", "9305", &c);
    assert(c.bulls == 0 && c.cows == 1);
    count_matches("9205", "9305", &c);
    assert(c.bulls == 3 && c.cows == 0);
    count_matches("9305", "9305", &c);
    assert(c.bulls == 4 && c.cows == 0);
    return 0;
}

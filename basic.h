#ifndef CONVERSIONS_H_
#define CONVERSIONS_H_

extern inline int char_to_int(char c)
{
    switch (c) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    }
    return -1;
}

extern inline int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

#endif  // CONVERSIONS_H_

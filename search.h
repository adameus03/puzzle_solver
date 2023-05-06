#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED

#include <cstring>
#include <iostream> //debug

enum PUZZLEDIR {
    LEFT = 'L',
    UP = 'U',
    RIGHT = 'R',
    DOWN = 'D'
};

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long long ull;

PUZZLEDIR* bfs(uint* buffer, const uint& a, const uint& b, uint& output_length, PUZZLEDIR* order);

#endif // SEARCH_H_INCLUDED

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

enum METRIC {
    MANHATTAN,
    HAMMING
};

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long long ull;

PUZZLEDIR* bfs(uint* buffer, const uint& a, const uint& b, uint& output_length, PUZZLEDIR* order);

PUZZLEDIR* dfs(uint* buffer, const uint& a, const uint& b, uint& output_length, PUZZLEDIR* order, const uint& max_depth);

#endif // SEARCH_H_INCLUDED

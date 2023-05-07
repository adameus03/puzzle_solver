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

struct searchstat {
    unsigned int solution_length;
    unsigned long long states_walked;
    unsigned long long states_processed;
    unsigned int max_depth;
    //double runtime_ms;
    unsigned char solution_found;
};

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long long ull;

PUZZLEDIR* bfs(uint* buffer, const uint& a, const uint& b/*, uint& output_length*/, PUZZLEDIR* order, const uint& max_depth, searchstat& stats);

PUZZLEDIR* dfs(uint* buffer, const uint& a, const uint& b/*, uint& output_length*/, PUZZLEDIR* order, const uint& max_depth, searchstat& stats);

ull hamm(uint* buffer, const uint& a, const uint& b);

ull manh(uint* buffer, const uint& a, const uint& b);

PUZZLEDIR* astr(uint* buffer, const uint& a, const uint& b/*, uint& output_length*/, METRIC metric, const uint& max_depth, searchstat& stats);



#endif // SEARCH_H_INCLUDED

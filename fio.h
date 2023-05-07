#ifndef FIO_H_INCLUDED
#define FIO_H_INCLUDED

#include <fstream>
#include <sstream>
#include <string>

typedef unsigned char uchar;
typedef unsigned int uint;

uint* load_puzzle (const char* source_path, uint& a, uint& b);

void store_solution(char* sol, uint len, uchar sol_found, const char* dest_path);


#endif // FIO_H_INCLUDED

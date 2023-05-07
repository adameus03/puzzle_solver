#ifndef FIO_H_INCLUDED
#define FIO_H_INCLUDED

#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

typedef unsigned char uchar;
typedef unsigned int uint;

uint* load_puzzle (const char* source_path, uint& a, uint& b);

void store_no_solution(const char* dest_path);

void store_solution(char* sol, uint len, uchar sol_found, const char* dest_path);

void save_stats(const char* dest_path, const uint& solution_length, const ull& states_walked, const ull& states_processed, const uint& max_depth, const double& runtime_ms);


#endif // FIO_H_INCLUDED

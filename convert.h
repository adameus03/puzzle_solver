#ifndef CONVERT_H_INCLUDED
#define CONVERT_H_INCLUDED

#include "search.h"

PUZZLEDIR* str_to_order(char* order_str);

char* convert_sol(PUZZLEDIR* sol, uint len);

#endif // CONVERT_H_INCLUDED

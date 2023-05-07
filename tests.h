#ifndef TESTS_H_INCLUDED
#define TESTS_H_INCLUDED

#include <iostream>
#include "search.h"
#include "convert.h"

typedef unsigned char uchar;

void checker(const uchar& ok, const char* description);

void inside_checker(const uchar& ok, const char* description);

void conditional_inside_checker(const uchar& toggle, const uchar& ok, const char* description);

void expected_conditional_inside_checker(const uchar& toggle, const uchar& ok, const char* expected, const char* actual, const char* description);



uchar test_bfs();

uchar test_dfs();

uchar test_hamm();

uchar test_manh();

uchar test_astr();


#endif // TESTS_H_INCLUDED

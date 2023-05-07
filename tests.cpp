#include <iostream>
#include "search.h"

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long long ull;

void checker(const uchar& ok, const char* description){
    std::cout << '[' << (ok?"OK":"!!") << "]  " << description << std::endl;
}

void inside_checker(const uchar& ok, const char* description){
    std::cout << '{' << (ok?"good":"!!") << "}  " << description << std::endl;
}


void conditional_inside_checker(const uchar& toggle, const uchar& ok, const char* description){
    if(toggle){
        inside_checker(ok, description);
    }
}
void expected_conditional_inside_checker(const uchar& toggle, const uchar& ok, const char* expected, const char* actual, const char* description){
    if(toggle){
        std::cout << '{' << (ok?"good":"!!") << "}  ( E: " << expected << ", A: " << actual << ") " << description << std::endl;
    }
}

char* convert_sol(PUZZLEDIR* sol, uint len){
    char* output = new char[len+0x1];
    char* oh = output;
    PUZZLEDIR* solt = sol+len;
    while(sol != solt){
        *oh++ = (char)(*sol++);
    }
    *oh = 0x0;
    return output;
}

//PUZZLEDIR* bfs(uint* buffer, const uint& a, const uint& b, uint& output_length, PUZZLEDIR* order)
uchar test_bfs(){
    /*
        TEST 1

        1 2 3
        4 5 6
        7 0 8
    */

    uint* buffer = new uint[0x13];
    *buffer = 0xffffffff;
    *(buffer+0x1) = 0xffffffff;
    *(buffer+0x2) = 0xffffffff;
    *(buffer+0x3) = 0xffffffff;
    *(buffer+0x4) = 0x1;
    *(buffer+0x5) = 0x2;
    *(buffer+0x6) = 0x3;
    *(buffer+0x7) = 0xffffffff;
    *(buffer+0x8) = 0x4;
    *(buffer+0x9) = 0x5;
    *(buffer+0xa) = 0x6;
    *(buffer+0xb) = 0xffffffff;
    *(buffer+0xc) = 0x7;
    *(buffer+0xd) = 0x0;
    *(buffer+0xe) = 0x8;
    *(buffer+0xf) = 0xffffffff;
    *(buffer+0x10) = 0xffffffff;
    *(buffer+0x11) = 0xffffffff;
    *(buffer+0x12) = 0xffffffff;
    /**buffer = 0xffffffff;
    *(buffer+0x1) = 0xffffffff;
    *(buffer+0x2) = 0xffffffff;
    *(buffer+0x3) = 0xffffffff;
    *(buffer+0x4) = 0x0;
    *(buffer+0x5) = 0x1;
    *(buffer+0x6) = 0x2;
    *(buffer+0x7) = 0xffffffff;
    *(buffer+0x8) = 0x5;
    *(buffer+0x9) = 0x6;
    *(buffer+0xa) = 0x3;
    *(buffer+0xb) = 0xffffffff;
    *(buffer+0xc) = 0x4;
    *(buffer+0xd) = 0x7;
    *(buffer+0xe) = 0x8;
    *(buffer+0xf) = 0xffffffff;
    *(buffer+0x10) = 0xffffffff;
    *(buffer+0x11) = 0xffffffff;
    *(buffer+0x12) = 0xffffffff;*/


    uint output_length;
    PUZZLEDIR* order = new PUZZLEDIR[0x4];
    *order = PUZZLEDIR::LEFT;
    *(order+0x1) = PUZZLEDIR::DOWN;
    *(order+0x2) = PUZZLEDIR::RIGHT;
    *(order+0x3) = PUZZLEDIR::UP;

    std::cout << "<BFS CALL>" << std::endl;
    PUZZLEDIR* sol = bfs(buffer, 0x3, 0x3, output_length, order);
    std::cout << "</BFS CALL>" << std::endl;

    std::cout << "<SOL>" << std::endl;
    std::cout << convert_sol(sol, output_length) << std::endl;
    std::cout << "</SOL>" << std::endl;

    uchar retval = 0x1;
    std::cout << "<output_length>" << output_length << "</output_length>" << std::endl;

    if(output_length != 0x1) retval = 0x0;
    else if(*sol != PUZZLEDIR::RIGHT) retval = 0x0;
    /*if(output_length != 0x8) retval = 0x0;*/

    delete[] buffer;
    delete[] order;

    /*
        TEST 2

        0 1 2
        5 6 3
        4 7 8

    */ //return 0x1;

    buffer = new uint[0x13];
    *buffer = 0xffffffff;
    *(buffer+0x1) = 0xffffffff;
    *(buffer+0x2) = 0xffffffff;
    *(buffer+0x3) = 0xffffffff;
    *(buffer+0x4) = 0x0;
    *(buffer+0x5) = 0x1;
    *(buffer+0x6) = 0x2;
    *(buffer+0x7) = 0xffffffff;
    *(buffer+0x8) = 0x5;
    *(buffer+0x9) = 0x6;
    *(buffer+0xa) = 0x3;
    *(buffer+0xb) = 0xffffffff;
    *(buffer+0xc) = 0x4;
    *(buffer+0xd) = 0x7;
    *(buffer+0xe) = 0x8;
    *(buffer+0xf) = 0xffffffff;
    *(buffer+0x10) = 0xffffffff;
    *(buffer+0x11) = 0xffffffff;
    *(buffer+0x12) = 0xffffffff;

    output_length = 0x0;
    order = new PUZZLEDIR[0x4];
    *order = PUZZLEDIR::LEFT;
    *(order+0x1) = PUZZLEDIR::DOWN;
    *(order+0x2) = PUZZLEDIR::RIGHT;
    *(order+0x3) = PUZZLEDIR::UP;

    std::cout << "<BFS CALL>" << std::endl;
    sol = bfs(buffer, 0x3, 0x3, output_length, order);
    std::cout << "</BFS CALL>" << std::endl;

    std::cout << "<SOL>" << std::endl;
    std::cout << convert_sol(sol, output_length) << std::endl;
    std::cout << "</SOL>" << std::endl;

    std::cout << "<output_length>" << output_length << "</output_length>" << std::endl;
    if(output_length != 0x8) retval = 0x0;
    //else if(*sol != PUZZLEDIR::RIGHT) retval = 0x0;

    delete[] buffer;
    delete[] order;



    return retval;

}

//PUZZLEDIR* dfs(uint* buffer, const uint& a, const uint& b, uint& output_length, PUZZLEDIR* order, const uint& max_depth)
uchar test_dfs(){ //return 0x1;
    /*
        TEST 1

        1 2 3
        4 5 6
        7 0 8
    */

    uint* buffer = new uint[0x13];
    *buffer = 0xffffffff;
    *(buffer+0x1) = 0xffffffff;
    *(buffer+0x2) = 0xffffffff;
    *(buffer+0x3) = 0xffffffff;
    *(buffer+0x4) = 0x1;
    *(buffer+0x5) = 0x2;
    *(buffer+0x6) = 0x3;
    *(buffer+0x7) = 0xffffffff;
    *(buffer+0x8) = 0x4;
    *(buffer+0x9) = 0x5;
    *(buffer+0xa) = 0x6;
    *(buffer+0xb) = 0xffffffff;
    *(buffer+0xc) = 0x7;
    *(buffer+0xd) = 0x0;
    *(buffer+0xe) = 0x8;
    *(buffer+0xf) = 0xffffffff;
    *(buffer+0x10) = 0xffffffff;
    *(buffer+0x11) = 0xffffffff;
    *(buffer+0x12) = 0xffffffff;
    /**buffer = 0xffffffff;
    *(buffer+0x1) = 0xffffffff;
    *(buffer+0x2) = 0xffffffff;
    *(buffer+0x3) = 0xffffffff;
    *(buffer+0x4) = 0x0;
    *(buffer+0x5) = 0x1;
    *(buffer+0x6) = 0x2;
    *(buffer+0x7) = 0xffffffff;
    *(buffer+0x8) = 0x5;
    *(buffer+0x9) = 0x6;
    *(buffer+0xa) = 0x3;
    *(buffer+0xb) = 0xffffffff;
    *(buffer+0xc) = 0x4;
    *(buffer+0xd) = 0x7;
    *(buffer+0xe) = 0x8;
    *(buffer+0xf) = 0xffffffff;
    *(buffer+0x10) = 0xffffffff;
    *(buffer+0x11) = 0xffffffff;
    *(buffer+0x12) = 0xffffffff;*/


    uint output_length;
    PUZZLEDIR* order = new PUZZLEDIR[0x4];
    *order = PUZZLEDIR::LEFT;
    *(order+0x1) = PUZZLEDIR::DOWN;
    *(order+0x2) = PUZZLEDIR::RIGHT;
    *(order+0x3) = PUZZLEDIR::UP;

    std::cout << "<DFS CALL>" << std::endl;
    PUZZLEDIR* sol = dfs(buffer, 0x3, 0x3, output_length, order, 20);
    std::cout << "</DFS CALL>" << std::endl;

    std::cout << "<SOL>" << std::endl;
    std::cout << convert_sol(sol, output_length) << std::endl;
    std::cout << "</SOL>" << std::endl;

    uchar retval = 0x1;
    std::cout << "<output_length>" << output_length << "</output_length>" << std::endl;

    ///if(output_length != 0x1) retval = 0x0;
    ///else if(*sol != PUZZLEDIR::RIGHT) retval = 0x0;
    /*if(output_length != 0x8) retval = 0x0;*/

    delete[] buffer;
    delete[] order;

    /*
        TEST 2

        0 1 2
        5 6 3
        4 7 8

    */

    buffer = new uint[0x13];
    *buffer = 0xffffffff;
    *(buffer+0x1) = 0xffffffff;
    *(buffer+0x2) = 0xffffffff;
    *(buffer+0x3) = 0xffffffff;
    *(buffer+0x4) = 0x0;
    *(buffer+0x5) = 0x1;
    *(buffer+0x6) = 0x2;
    *(buffer+0x7) = 0xffffffff;
    *(buffer+0x8) = 0x5;
    *(buffer+0x9) = 0x6;
    *(buffer+0xa) = 0x3;
    *(buffer+0xb) = 0xffffffff;
    *(buffer+0xc) = 0x4;
    *(buffer+0xd) = 0x7;
    *(buffer+0xe) = 0x8;
    *(buffer+0xf) = 0xffffffff;
    *(buffer+0x10) = 0xffffffff;
    *(buffer+0x11) = 0xffffffff;
    *(buffer+0x12) = 0xffffffff;

    output_length = 0x0;
    order = new PUZZLEDIR[0x4];
    *order = PUZZLEDIR::LEFT;
    *(order+0x1) = PUZZLEDIR::DOWN;
    *(order+0x2) = PUZZLEDIR::RIGHT;
    *(order+0x3) = PUZZLEDIR::UP;

    std::cout << "<DFS CALL>" << std::endl;
    sol = dfs(buffer, 0x3, 0x3, output_length, order, 20);
    std::cout << "</DFS CALL>" << std::endl;

    std::cout << "<SOL>" << std::endl;
    std::cout << convert_sol(sol, output_length) << std::endl;
    std::cout << "</SOL>" << std::endl;


    std::cout << "<output_length>" << output_length << "</output_length>" << std::endl;
    ///if(output_length != 0x8) retval = 0x0;
    //else if(*sol != PUZZLEDIR::RIGHT) retval = 0x0;

    delete[] buffer;
    delete[] order;



    return retval;
}
//ull hamm(uint* buffer, const uint& a, const uint& b);
uchar test_hamm(){
    uint* buffer = new uint[0x13];
    *buffer = 0xffffffff;
    *(buffer+0x1) = 0xffffffff;
    *(buffer+0x2) = 0xffffffff;
    *(buffer+0x3) = 0xffffffff;
    *(buffer+0x4) = 0x1;
    *(buffer+0x5) = 0x2;
    *(buffer+0x6) = 0x3;
    *(buffer+0x7) = 0xffffffff;
    *(buffer+0x8) = 0x4;
    *(buffer+0x9) = 0x5;
    *(buffer+0xa) = 0x6;
    *(buffer+0xb) = 0xffffffff;
    *(buffer+0xc) = 0x7;
    *(buffer+0xd) = 0x0;
    *(buffer+0xe) = 0x8;
    *(buffer+0xf) = 0xffffffff;
    *(buffer+0x10) = 0xffffffff;
    *(buffer+0x11) = 0xffffffff;
    *(buffer+0x12) = 0xffffffff;

    ull mtc = hamm(buffer, 0x3, 0x3);
    uchar retval = 0x1;
    if(mtc != 0x1) retval = 0x0;

    std::cout << "HAMM=" << mtc << std::endl;

    delete[] buffer;
    return retval;
}

//ull manh(uint* buffer, const uint& a, const uint& b);
uchar test_manh(){
    uint* buffer = new uint[0x13];
    *buffer = 0xffffffff;
    *(buffer+0x1) = 0xffffffff;
    *(buffer+0x2) = 0xffffffff;
    *(buffer+0x3) = 0xffffffff;
    *(buffer+0x4) = 0x1;
    *(buffer+0x5) = 0x2;
    *(buffer+0x6) = 0x3;
    *(buffer+0x7) = 0xffffffff;
    *(buffer+0x8) = 0x4;
    *(buffer+0x9) = 0x5;
    *(buffer+0xa) = 0x6;
    *(buffer+0xb) = 0xffffffff;
    *(buffer+0xc) = 0x7;
    *(buffer+0xd) = 0x0;
    *(buffer+0xe) = 0x8;
    *(buffer+0xf) = 0xffffffff;
    *(buffer+0x10) = 0xffffffff;
    *(buffer+0x11) = 0xffffffff;
    *(buffer+0x12) = 0xffffffff;

    ull mtc = manh(buffer, 0x3, 0x3);
    uchar retval = 0x1;
    if(mtc != 0x1) retval = 0x0;

    std::cout << "MANH=" << mtc << std::endl;

    delete[] buffer;
    return retval;
}

//PUZZLEDIR* astr(uint* buffer, const uint& a, const uint& b, uint& output_length, METRIC metric, const uint& max_depth)
uchar test_astr(){
    /*
        TEST 1

        1 2 3
        4 5 6
        7 0 8
    */

    uint* buffer = new uint[0x13];
    *buffer = 0xffffffff;
    *(buffer+0x1) = 0xffffffff;
    *(buffer+0x2) = 0xffffffff;
    *(buffer+0x3) = 0xffffffff;
    *(buffer+0x4) = 0x1;
    *(buffer+0x5) = 0x2;
    *(buffer+0x6) = 0x3;
    *(buffer+0x7) = 0xffffffff;
    *(buffer+0x8) = 0x4;
    *(buffer+0x9) = 0x5;
    *(buffer+0xa) = 0x6;
    *(buffer+0xb) = 0xffffffff;
    *(buffer+0xc) = 0x7;
    *(buffer+0xd) = 0x0;
    *(buffer+0xe) = 0x8;
    *(buffer+0xf) = 0xffffffff;
    *(buffer+0x10) = 0xffffffff;
    *(buffer+0x11) = 0xffffffff;
    *(buffer+0x12) = 0xffffffff;
    /**buffer = 0xffffffff;
    *(buffer+0x1) = 0xffffffff;
    *(buffer+0x2) = 0xffffffff;
    *(buffer+0x3) = 0xffffffff;
    *(buffer+0x4) = 0x0;
    *(buffer+0x5) = 0x1;
    *(buffer+0x6) = 0x2;
    *(buffer+0x7) = 0xffffffff;
    *(buffer+0x8) = 0x5;
    *(buffer+0x9) = 0x6;
    *(buffer+0xa) = 0x3;
    *(buffer+0xb) = 0xffffffff;
    *(buffer+0xc) = 0x4;
    *(buffer+0xd) = 0x7;
    *(buffer+0xe) = 0x8;
    *(buffer+0xf) = 0xffffffff;
    *(buffer+0x10) = 0xffffffff;
    *(buffer+0x11) = 0xffffffff;
    *(buffer+0x12) = 0xffffffff;*/


    uint output_length;
    PUZZLEDIR* order = new PUZZLEDIR[0x4];
    *order = PUZZLEDIR::LEFT;
    *(order+0x1) = PUZZLEDIR::DOWN;
    *(order+0x2) = PUZZLEDIR::RIGHT;
    *(order+0x3) = PUZZLEDIR::UP;

    std::cout << "<ASTR CALL (HAMM)>" << std::endl;
    PUZZLEDIR* sol = astr(buffer, 0x3, 0x3, output_length, METRIC::HAMMING, 20);
    std::cout << "</ASTR CALL (HAMM)>" << std::endl;

    std::cout << "<SOL>" << std::endl;
    std::cout << convert_sol(sol, output_length) << std::endl;
    std::cout << "</SOL>" << std::endl;

    uchar retval = 0x1;
    std::cout << "<output_length>" << output_length << "</output_length>" << std::endl;

    if(output_length != 0x1) retval = 0x0;
    else if(*sol != PUZZLEDIR::RIGHT) retval = 0x0;
    /*if(output_length != 0x8) retval = 0x0;*/

    delete[] buffer;
    delete[] order;

    /*
        TEST 2

        0 1 2
        5 6 3
        4 7 8

    */

    buffer = new uint[0x13];
    *buffer = 0xffffffff;
    *(buffer+0x1) = 0xffffffff;
    *(buffer+0x2) = 0xffffffff;
    *(buffer+0x3) = 0xffffffff;
    *(buffer+0x4) = 0x0;
    *(buffer+0x5) = 0x1;
    *(buffer+0x6) = 0x2;
    *(buffer+0x7) = 0xffffffff;
    *(buffer+0x8) = 0x5;
    *(buffer+0x9) = 0x6;
    *(buffer+0xa) = 0x3;
    *(buffer+0xb) = 0xffffffff;
    *(buffer+0xc) = 0x4;
    *(buffer+0xd) = 0x7;
    *(buffer+0xe) = 0x8;
    *(buffer+0xf) = 0xffffffff;
    *(buffer+0x10) = 0xffffffff;
    *(buffer+0x11) = 0xffffffff;
    *(buffer+0x12) = 0xffffffff;

    output_length = 0x0;
    order = new PUZZLEDIR[0x4];
    *order = PUZZLEDIR::LEFT;
    *(order+0x1) = PUZZLEDIR::DOWN;
    *(order+0x2) = PUZZLEDIR::RIGHT;
    *(order+0x3) = PUZZLEDIR::UP;

    std::cout << "<ASTR CALL (MANH)>" << std::endl;
    sol = astr(buffer, 0x3, 0x3, output_length, METRIC::MANHATTAN, 20);
    std::cout << "</ASTR CALL (MANH)>" << std::endl;

    std::cout << "<SOL>" << std::endl;
    std::cout << convert_sol(sol, output_length) << std::endl;
    std::cout << "</SOL>" << std::endl;


    std::cout << "<output_length>" << output_length << "</output_length>" << std::endl;
    if(output_length != 0x8) retval = 0x0;
    //else if(*sol != PUZZLEDIR::RIGHT) retval = 0x0;

    delete[] buffer;
    delete[] order;



    return retval;
}

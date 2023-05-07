#include "search.h"

PUZZLEDIR* str_to_order(char* order_str){
    PUZZLEDIR* output = new PUZZLEDIR[0x4];
    PUZZLEDIR* oh = output;
    PUZZLEDIR* ot = output+0x4;
    while(oh != ot){
        *oh++ = (PUZZLEDIR)*order_str++;
    }

    return output;
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

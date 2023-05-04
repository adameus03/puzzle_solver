#include <cstring>


enum PUZZLEDIR {
    LEFT,
    UP,
    RIGHT,
    DOWN
};

struct node {
    node* origin;
    PUZZLEDIR direction;
};

typedef unsigned int uint;
typedef unsigned long long ull;
typedef node* pnode;

uint hamm(uint* buffer, const uint& a, const uint& b){
    uint output = 0x0;
    for(uint i=0x0; i<a*b; i++){
        output += (*buffer++ != i+1);
    }
    return output;
}

uint final_predicate(uint* buffer, const uint& a, const uint& b){

    for(uint i=0x0; i<a*b; i++){
        if(*buffer++ != i+1) return 0x0;
    }
    return 0x1;
}

PUZZLEDIR* bfs(uint* buffer, const uint& a, const uint& b, uint& output_length){
    /*if(final_predicate(buffer, a, b)){

    }*/
    node root;
    root.origin = NULL;

    pnode* layer = new pnode[0x100000000]; // 2^32

    pnode* lh = layer;
    *lh++ = &root;
    pnode* lt = lh+0x1;

    if(final_predicate(buffer,a,b)){}

    pnode* _lh = lt;
    while(lh != lt){
        *_lh = new node;
        (*_lh)->direction = PUZZLEDIR::LEFT;
        (*_lh)->origin = *lh;
        _lh++;
        *_lh = new node;
        (*_lh)->direction = PUZZLEDIR::UP;
        (*_lh)->origin = *lh;
        _lh++;
        *_lh = new node;
        (*_lh)->direction = PUZZLEDIR::RIGHT;
        (*_lh)->origin = *lh;
        _lh++;
        *_lh = new node;
        (*_lh)->direction = PUZZLEDIR::DOWN;
        (*_lh)->origin = *lh;
        _lh++;
        lh++;
    }
    lt = _lh;

    pnode* tlh = lh;

    while(tlh != lt){

    }

}


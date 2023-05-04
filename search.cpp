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
    unsigned int* state;
    unsigned int* hole;
};

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef node* pnode;

/*ull hamm(uint* buffer, const size_t& len){
    ull output = 0x0;
    uint* bt = buffer+len;
    size_t k=0x1;

    while(buffer != bt){
        output += (*buffer++ != k++);
    }

    return output;
}

uchar final_predicate(uint* buffer, const size_t& len){

    uint* bt = buffer+len;
    size_t k=0x1;

    while(buffer != bt){
        if(*buffer++ != k++) return 0x0;
    }

    return 0x0;
}

uint* zero(uint* buffer, const size_t& len){
    uint* bh = buffer;
    uint* bt = buffer+len;
    while(bh != bt){
        if(!*bh) return bh;
        bh++;
    }
    return NULL;
}*/



ull hamm(uint* buffer, const uint& a, const uint& b){
    uint output = 0x0;
    for(uint i=0x0; i<a*b; i++){
        if(*buffer) output += (*buffer != i+1);
        buffer++;
    }
    return output-a-0x1;
}

uchar final_predicate(uint* buffer, const uint& a, const uint& b){

    ull k=0x1;
    for(uint i=0x0; i<a; i++){
        buffer++;
        for(uint j=0x0; j<b; j++){
            if(*buffer++ != k) return 0x0;
            k++;
        }
    }
    return 0x1;
}

uint* zero(uint* buffer, const size_t& len){
    uint* bh = buffer;
    uint* bt = buffer+len;
    while(bh != bt){
        if(!*bh) return bh;
        bh++;
    }
    return NULL;
}







/**
    @param buffer
        Row-MAXINT-separated buffer of tiles
*/
PUZZLEDIR* bfs(uint* buffer, const uint& a, const uint& b, uint& output_length, PUZZLEDIR* order){
    /*if(final_predicate(buffer, a, b)){

    }*/
    //uint* bh = buffer;
    size_t bl = a*b+a+1;
    //uint* bt = buffer+bl;


    node root;
    root.origin = NULL;
    root.state = new uint[bl];
    memcpy(root.state, buffer, bl);
    root.hole = zero(buffer, bl);

    pnode* layer = new pnode[0x100000000]; // 2^32
    pnode* _layer = new pnode[0x100000000]; // 2^32

    pnode* lh = layer;
    pnode* _lh;// = _layer;
    *lh++ = &root;
    pnode* lt = lh+0x1;

    PUZZLEDIR* orderh;
    PUZZLEDIR* ordert = order+0x4;

    int* enhanced_order = new int[0x4];
    int* enhanced_orderh = enhanced_order;
    int* enhanced_ordert = enhanced_order+0x4;

    while(enhanced_orderh != enhanced_ordert){
        switch(*orderh++){
        case PUZZLEDIR::LEFT:
            *enhanced_orderh++ = -1;
            break;
        case PUZZLEDIR::UP:
            *enhanced_orderh++ = -b-1;
            break;
        case PUZZLEDIR::RIGHT:
            *enhanced_orderh++ = 1;
            break;
        default:
            *enhanced_orderh++ = b+1;
        }
        enhanced_order++;
    }

    if(final_predicate(buffer,a,b)){}


    pnode sol_node = NULL;

    //pnode* _lh = lt;
    while(0x1){
        lh = layer;
        _lh = _layer;
        while(lh != lt){

            orderh = order;
            enhanced_orderh = enhanced_order;

            //IDEa: layer a, layer b
            while(orderh != ordert){
                //(*lh)->tile

                // SWAP TILES, be careful with the above
                uint* target = ((*lh)->hole) + *enhanced_orderh;
                if(target){
                    //_lh - Idea: layer b head?
                    *_lh = new node;
                    (*_lh)->direction = *orderh;
                    (*_lh)->origin = *lh;
                    (*_lh)->state = new uint[bl];
                    memcpy((*_lh)->state, (*lh)->state, bl);
                    (*_lh)->hole = (*lh)->hole;

                    target = ((*_lh)->hole) + *enhanced_orderh;
                    uint temp = *((*_lh)->hole);
                    *((*_lh)->hole) = *target;
                    *target = temp;

                    if(final_predicate((*_lh)->state, a, b)){
                        sol_node = *_lh;
                        goto after_loop;
                    }


                    _lh++;
                }

                orderh++;
                enhanced_orderh++;
            }
            lh++;
        }

        memcpy(layer, _layer, _lh-_layer);

        lt = layer+(_lh-_layer);
    }
    after_loop:
    return NULL;


}


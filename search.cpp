#include <cstring>
#include "search.h"
#include <iostream> //debug


/*enum PUZZLEDIR {
    LEFT,
    UP,
    RIGHT,
    DOWN
};*/

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



/*ull hamm(uint* buffer, const uint& a, const uint& b){
    uint output = 0x0;
    for(uint i=0x0; i<a*b; i++){
        if(*buffer) output += (*buffer != i+1);
        buffer++;
    }
    return output-a-0x1;
}*/

uchar final_predicate(uint* buffer, const uint& a, const uint& b){

    ull k=0x1;
    buffer += (b+0x1);
    for(uint i=0x0; i<a-1; i++){
        for(uint j=0x0; j<b; j++){
            if(*buffer++ != k++) return 0x0;
        }
        buffer++;
    }
    for(uint j=0x0; j<b-1; j++){
        if(*buffer++ != k++) return 0x0;
    }

    return !*buffer;
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
PUZZLEDIR* bfs(uint* buffer, const uint& a, const uint& b, uint& output_length, PUZZLEDIR* order){/* Todo: Terminate if sol not found*/

    if(final_predicate(buffer, a, b)){
        output_length = 0x0;
        return NULL;
    }
    //uint* bh = buffer;
    size_t bl = (a+0x2)*(b+0x1);
    size_t bls = bl*sizeof(uint);
    //uint* bt = buffer+bl;


    node root;
    root.origin = NULL;
    root.state = new uint[bl];
    memcpy(root.state, buffer, bls);
    root.hole = zero(root.state, bl);

    ///std::cout << "  <layer mem alloc>" << std::endl;
    pnode* layer = new pnode[0x10000000]; // 2^28-1
    ///std::cout << "  </layer mem alloc>" << std::endl;
    ///std::cout << "  <_layer mem alloc>" << std::endl;
    pnode* _layer = new pnode[0x10000000]; // 2^28-1
    ///std::cout << "  </_layer mem alloc>" << std::endl;


    pnode* lh = layer;
    pnode* _lh;// = _layer;
    *lh++ = &root;
    pnode* lt = layer+0x1;

    PUZZLEDIR* orderh = order;
    PUZZLEDIR* ordert = order+0x4;

    ///std::cout << "  <enhanced_order mem alloc>" << std::endl;
    int* enhanced_order = new int[0x4];
    ///std::cout << "  </enhanced_order mem alloc>" << std::endl;
    int* enhanced_orderh = enhanced_order;
    int* enhanced_ordert = enhanced_order+0x4;

    while(enhanced_orderh != enhanced_ordert){
        switch(*orderh){
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
        orderh++;
        //enhanced_order++;
    }

    pnode sol_node = NULL;
    uint depth = 0x0;

    //pnode* _lh = lt;

    ///std::cout << "  <while(0x1)>" << std::endl;
    while(0x1){
        lh = layer;
        _lh = _layer;
        depth++;

        ///std::cout << "      <while(lh != lt)>" << std::endl;
        while(lh != lt){

            orderh = order;
            enhanced_orderh = enhanced_order;

            //IDEa: layer a, layer b
            ///std::cout << "          <while(orderh != ordert)>" << std::endl;
            while(orderh != ordert){
                //(*lh)->tile

                // SWAP TILES, be careful with the above
                uint* target = ((*lh)->hole) + *enhanced_orderh;
                ///std::cout << "              <if(*target != 0xffffffff)>" << std::endl;
                if(*target != 0xffffffff){
                    //_lh - Idea: layer b head?
                    ///std::cout << "                  <*_lh mem alloc>" << std::endl;
                    *_lh = new node;
                    ///std::cout << "                  </*_lh mem alloc>" << std::endl;
                    (*_lh)->direction = *orderh;
                    (*_lh)->origin = *lh;
                    (*_lh)->state = new uint[bl];
                    memcpy((*_lh)->state, (*lh)->state, bls);
                    //int debug_diff = ((*lh)->hole)-((*lh)->state);
                    (*_lh)->hole = ((*_lh)->state) + (((*lh)->hole)-((*lh)->state));

                    target = ((*_lh)->hole) + *enhanced_orderh;
                    uint temp = *((*_lh)->hole);
                    *((*_lh)->hole) = *target;
                    *target = temp;

                    (*_lh)->hole = target;

                    if(final_predicate((*_lh)->state, a, b)){
                        sol_node = *_lh;
                        goto after_loop;
                    }


                    _lh++;
                }
                ///std::cout << "              </if(*target != 0xffffffff)>" << std::endl;

                orderh++;
                enhanced_orderh++;
            }
            ///std::cout << "          </while(orderh != ordert)>" << std::endl;
            lh++;
        }
        ///std::cout << "      </while(lh != lt)>" << std::endl;


        memcpy(layer, _layer, (_lh-_layer)*sizeof(node));

        lt = layer+(_lh-_layer);
    }
    ///std::cout << "  </while(0x1)>" << std::endl;

    after_loop:

    ///std::cout << "  <after loop/>" << std::endl;



    /*if(!sol_node){
        output_length = 0x0;
        return NULL;
    }*/

    PUZZLEDIR* sol = new PUZZLEDIR[depth];
    PUZZLEDIR* solh = sol+depth-0x1;
    PUZZLEDIR* solt = sol-0x1;
    pnode nodeh = sol_node;

    while(solh != solt){
        *solh-- = nodeh->direction;
        nodeh = nodeh->origin;
    }



    delete[] layer;
    delete[] _layer;



    output_length = depth;
    return sol;


}

struct small_node {
    small_node* origin = NULL;
    PUZZLEDIR* direction;
    uchar op = 0x0;
};


PUZZLEDIR* dfs(uint* buffer, const uint& a, const uint& b, uint& output_length, PUZZLEDIR* order, const uint& max_depth){
    if(final_predicate(buffer, a, b)){
        output_length = 0x0;
        return NULL;
    }
    //uint* bh = buffer;
    size_t bl = (a+0x2)*(b+0x1);
    //size_t bls = bl*sizeof(uint);
    //uint* bt = buffer+bl;


    small_node root;

    PUZZLEDIR* orderh = order;
    //PUZZLEDIR* ordert = order+0x4;

    ///std::cout << "  <enhanced_order mem alloc>" << std::endl;
    int* enhanced_order = new int[0x4];
    ///std::cout << "  </enhanced_order mem alloc>" << std::endl;
    int* enhanced_orderh = enhanced_order;
    int* enhanced_ordert = enhanced_order+0x4;

    while(enhanced_orderh != enhanced_ordert){
        switch(*orderh){
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
        orderh++;
        //enhanced_order++;
    }


    uint depth = 0x0;
    uint* hole = zero(buffer, bl);

    small_node* head = &root;

    ///std::cout << "  <while(0x1)>" << std::endl;
    while(0x1){
        ///std::cout << "      <condition(head->op<0x4)>" << std::endl;
        if(head->op < 0x4){ //branch (if possible)
            uint* target = hole + *(enhanced_order+(head->op));
            if(*target == 0xffffffff){
                (head->op)++;
                continue;
            }
            //std::cout << "BRANCH" << std::endl;
            //update buffer, depth and hole
            *hole = *target;
            *target = 0x0;
            hole = target;
            depth++;

            //configure new node
            small_node* new_node = new small_node;
            new_node->origin = head;
            new_node->direction = order+(head->op);

            (head->op)++;

            head = new_node;

            //check depth, check final_predicate
            if(depth >= max_depth){
                head->op = 0x4;
            }
            if(final_predicate(buffer, a, b)){
                //do stuff
                break;
            }
        }
        else {
            //std::cout << "RETURN" << std::endl;
            // go to origin after undo move
            if(head->origin){
                //update buffer, depth and hole
                uint* target = hole - *(enhanced_order+((head->direction)-order));
                *hole = *target;
                *target = 0x0;
                hole = target;
                depth--;

                // return to origin
                head = head->origin;
            }
            else { // solution not found
                output_length = 0x0;
                return NULL;
            }
        }
        ///std::cout << "      </condition(head->op<0x4)>" << std::endl;
    }
    ///std::cout << "  </while(0x1)>" << std::endl;

    PUZZLEDIR* sol = new PUZZLEDIR[depth];
    PUZZLEDIR* solh = sol+depth-0x1;
    PUZZLEDIR* solt = sol-0x1;

    while(solh != solt){
        *solh-- = *(head->direction);
        head = head->origin;
    }

    output_length = depth;


    return sol;

}

/*struct astr_node {
    astr_node* origin = NULL;
    PUZZLEDIR* direction;
};*/

struct astr_node {
    astr_node* origin = NULL;
    PUZZLEDIR* direction;
    uchar op = 0x0;
    ull* metrics = NULL;
};

ull hamm(uint* buffer, const uint& a, const uint& b){
    uint output = 0x0;
    size_t sup = a*(b+0x1);
    buffer += (b+0x1);
    size_t k = 0x1;
    for(size_t i=0x2; i<sup; i++){
        if((*buffer) == 0xffffffff){
            buffer++;
            continue;
        }
        output += (*buffer != k++);
        buffer++;
    }
    return output;
}

/*ull umanh(uint pos, uint val, const uint& a, const uint& b){
    uint posx = pos%b;
    uint posy = pos/b;
    uint valx = val%b;
    uint valy = val/b;
}*/

ull manh(uint* buffer, const uint& a, const uint& b){
    ull output = 0x0;
    size_t sup = a*(b+0x1);
    buffer += (b+0x1);
    size_t k = 0x0;
    uint posx, posy, valx, valy;
    for(size_t i=0x1; i<sup; i++){
        if(((*buffer)==0xffffffff)){
            buffer++;
            continue;
        }
        if(!*buffer){
            buffer++;
            k++;
            continue;
        }
        //output += (*buffer != k++);
        posx = k%b;
        valx = ((*buffer)-0x1)%b;
        posy = k/b;
        valy = ((*buffer)-0x1)/b;

        if(posx>valx){
            output += (posx-valx);
        }
        else {
            output += (valx-posx);
        }
        if(posy>valy){
            output += (posy-valy);
        }
        else {
            output += (valy-posy);
        }

        k++;
        buffer++;
    }
    return output;
}

PUZZLEDIR* astr(uint* buffer, const uint& a, const uint& b, uint& output_length, METRIC metric, const uint& max_depth){
    /*astr_node root;

    return NULL;*/

    if(final_predicate(buffer, a, b)){
        output_length = 0x0;
        return NULL;
    }
    //uint* bh = buffer;
    size_t bl = (a+0x2)*(b+0x1);
    //size_t bls = bl*sizeof(uint);
    //uint* bt = buffer+bl;


    astr_node root;
    /* CHANGES */

    PUZZLEDIR* dirs = new PUZZLEDIR[0x4];
    //PUZZLEDIR* dirsh;
    //PUZZLEDIR* dirst = dirs+0x4;
    *dirs = PUZZLEDIR::LEFT;
    *(dirs+0x1) = PUZZLEDIR::DOWN;
    *(dirs+0x2) = PUZZLEDIR::RIGHT;
    *(dirs+0x3) = PUZZLEDIR::UP;

    //PUZZLEDIR* ordert = order+0x4;

    ///std::cout << "  <enhanced_dirs mem alloc>" << std::endl;
    int* enhanced_dirs = new int[0x4];
    int* enhanced_dirsh;
    int* enhanced_dirst = enhanced_dirs+0x4;
    ///std::cout << "  </enhanced_dirs mem alloc>" << std::endl;
    *enhanced_dirs = -1;
    *(enhanced_dirs+0x1) = b+1;
    *(enhanced_dirs+0x2) = 1;
    *(enhanced_dirs+0x3) = -b-1;

    uint depth = 0x0;
    uint* hole = zero(buffer, bl);

    astr_node* head = &root;


    /*//temp buffer for comparing with the actual buffer
    uint* _buffer = new uint[bl];*/

    ///std::cout << "  <while(0x1)>" << std::endl;
    while(0x1){
        ///std::cout << "      <condition(head->op<0x4)>" << std::endl;
        if(!(head->op)){ // calculate metrics
            ull* scores = new ull[0x4];
            ull* scoresh = scores;
            //ull* scorest = scores+0x4;

            enhanced_dirsh = enhanced_dirs;
            while(enhanced_dirsh != enhanced_dirst){
                uint* target = hole + *enhanced_dirsh;
                if((*target) == 0xffffffff){
                    *scoresh = 0xffffffffffffffff;
                }
                else {
                    *hole = *target;
                    *target = 0x0;
                    uint* temp = hole;
                    hole = target;
                    target = temp;

                    *scoresh = metric == METRIC::HAMMING ? hamm(buffer, a, b) : manh(buffer, a, b);

                    *hole = *target;
                    *target = 0x0;
                    hole = target;
                }

                enhanced_dirsh++;
                scoresh++;
            }
            head->metrics = scores;
        }

        if(head->op < 0x4){ //branch (if possible)
            // min
            ull* minscore = head->metrics;
            ull* scoresh = (head->metrics)+0x1;
            ull* scorest = (head->metrics)+0x4;
            while(scoresh != scorest){
                if(*scoresh < *minscore){
                    minscore = scoresh;
                }
                scoresh++;
            }
            *minscore = 0xffffffffffffffff;

            // WHEN NEXT ORDER ELEM KNOWN
            uint* target = hole + *(enhanced_dirs+(minscore-(head->metrics)));
            if(*target == 0xffffffff){
                (head->op)++;
                continue;
            }
            //std::cout << "BRANCH" << std::endl;
            //update buffer, depth and hole
            *hole = *target;
            *target = 0x0;
            hole = target;
            depth++;

            //configure new node
            astr_node* new_node = new astr_node;
            new_node->origin = head;
            new_node->direction = dirs+(minscore-(head->metrics));

            (head->op)++;

            head = new_node;

            //check depth, check final_predicate
            if(depth >= max_depth){
                head->op = 0x4;
            }
            if(final_predicate(buffer, a, b)){
                //do stuff
                break;
            }
        }
        else {
            //std::cout << "RETURN" << std::endl;
            // go to origin after undo move
            if(head->origin){
                //update buffer, depth and hole
                uint* target = hole - *(enhanced_dirs+((head->direction)-dirs));
                *hole = *target;
                *target = 0x0;
                hole = target;
                depth--;

                // return to origin
                head = head->origin;
            }
            else { // solution not found
                output_length = 0x0;
                return NULL;
            }
        }
        ///std::cout << "      </condition(head->op<0x4)>" << std::endl;
    }
    ///std::cout << "  </while(0x1)>" << std::endl;

    PUZZLEDIR* sol = new PUZZLEDIR[depth];
    PUZZLEDIR* solh = sol+depth-0x1;
    PUZZLEDIR* solt = sol-0x1;

    while(solh != solt){
        *solh-- = *(head->direction);
        head = head->origin;
    }

    output_length = depth;


    return sol;
}

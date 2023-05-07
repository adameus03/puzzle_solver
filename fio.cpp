#include <fstream>
#include <sstream>
#include <string>

typedef unsigned char uchar;
typedef unsigned int uint;

//uint* buffer, const uint& a, const uint& b

uint* load_puzzle (const char* source_path, uint& a, uint& b){
    std::ifstream f_in(source_path);
    f_in >> a >> b;

    uint* buffer = new uint[(a+0x2)*(b+0x1)];
    uint* head = buffer;

    for(uint j=0x0; j<b; j++){
        *head++ = 0xffffffff;
    }

    std::string line;
    std::getline(f_in, line);
    for(uint i=0x0; i<a; i++){
        *head++ = 0xffffffff;
        std::getline(f_in, line);
        std::istringstream iss(line);
        for(uint j=0x0; j<b; j++){
            iss >> *head++;
        }
    }

    for(uint j=0x0; j<b; j++){
        *head++ = 0xffffffff;
    }

    return buffer;
}

void store_solution(char* sol, uint len, uchar sol_found, const char* dest_path){
    std::ofstream f_out(dest_path);
    if(sol_found){
        f_out << len << std::endl;
        char* tail = sol+len;
        while(sol != tail){
            f_out << *sol++;
        }
    }
    else {
        f_out << "-1";
    }

}

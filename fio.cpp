#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long long ull;

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

    for(uint j=0x0; j<=b; j++){///
        *head++ = 0xffffffff;
    }

    return buffer;
}

void store_no_solution(const char* dest_path){
    std::ofstream f_out(dest_path);
    f_out << "-1";
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

void save_stats(const char* dest_path, const uint& solution_length, const ull& states_walked, const ull& states_processed, const uint& max_depth, const double& runtime_ms){
    std::ofstream f_out(dest_path);
    if(solution_length == 0xffffffff) f_out << "-1" << std::endl;
    else f_out << solution_length << std::endl;
    f_out << states_walked << std::endl;
    f_out << states_processed << std::endl;
    f_out << max_depth << std::endl;
    f_out << round(runtime_ms*1000.0)/1000.0;
}

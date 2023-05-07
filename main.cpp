#include <iostream>
#include "tests.h"
#include "search.h"
#include "fio.h"
#include "convert.h"

using namespace std;


int main(int argc, char** argv)
{
    /*checker(test_bfs(), "bfs");
    checker(test_dfs(), "dfs");
    checker(test_hamm(), "hamm");
    checker(test_manh(), "manh");
    checker(test_astr(), "astr");*/

    if(argc == 6){
        if(!strcmp("bfs", argv[1])){
            uint a, b;
            uint* buffer = load_puzzle(argv[3], a, b);
            uint solution_length;
            PUZZLEDIR* sol = bfs(buffer, a, b, solution_length, str_to_order(argv[2]));
            store_solution(convert_sol(sol, solution_length), solution_length, 0x1, argv[4]);

        }
        else if(!strcmp("dfs", argv[1])){
            uint a, b;
            uint* buffer = load_puzzle(argv[3], a, b);
            uint solution_length;
            PUZZLEDIR* sol = dfs(buffer, a, b, solution_length, str_to_order(argv[2]), 20);
            store_solution(convert_sol(sol, solution_length), solution_length, 0x1, argv[4]);
        }
        else if(!strcmp("astr", argv[1])){
            METRIC mtc;
            if(!strcmp("manh", argv[2])){
                mtc = METRIC::MANHATTAN;
            }
            else if(!strcmp("hamm", argv[2])){
                mtc = METRIC::HAMMING;
            }
            else {
                std::cout << "Invalid metric! [" << argv[2] << "] Available metrics are" << std::endl;
                std::cout << "  hamm - Hamming metric" << std::endl << "  manh - Manhattan metric" << std::endl;
            }


            uint a, b;
            uint* buffer = load_puzzle(argv[3], a, b);
            uint solution_length;

            PUZZLEDIR* sol = astr(buffer, a, b, solution_length, mtc, 20);
            store_solution(convert_sol(sol, solution_length), solution_length, 0x1, argv[4]);
        }
        else {
            std::cout << "Invalid strategy! Available strategies are" << std::endl;
            std::cout << "  bfs" << std::endl << "  dfs" << std::endl << "  astr" << std::endl;
        }
    }
    else {
        std::cout << "Invalid number of arguments!" << std::endl;
    }

    return 0;
}

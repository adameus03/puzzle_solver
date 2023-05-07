#include <iostream>
#include "tests.h"
#include "search.h"
#include "fio.h"
#include "convert.h"
#include <chrono>
#include <thread>

using namespace std;


int main(int argc, char** argv)
{
    /*checker(test_bfs(), "bfs");
    checker(test_dfs(), "dfs");
    checker(test_hamm(), "hamm");
    checker(test_manh(), "manh");
    checker(test_astr(), "astr");*/

    if(argc == 6){
        char** argvh = argv+0x1;
        char** argvt = argv+argc;
        while(argvh != argvt){
            std::cout << (*argvh++) << ' ';
        }
        //std::cout << std::endl;


        if(!strcmp("bfs", argv[1])){
            uint a, b;
            uint* buffer = load_puzzle(argv[3], a, b);
            searchstat stats;
            std::chrono::time_point<std::chrono::high_resolution_clock> tp_before = std::chrono::high_resolution_clock::now();
            PUZZLEDIR* sol = bfs(buffer, a, b, str_to_order(argv[2]), 20, stats);
            //std::this_thread::sleep_for(std::chrono::milliseconds(10));
            std::chrono::time_point<std::chrono::high_resolution_clock> tp_after = std::chrono::high_resolution_clock::now();
            if(stats.solution_found) store_solution(convert_sol(sol, stats.solution_length), stats.solution_length, stats.solution_found, argv[4]);
            else store_no_solution(argv[4]);
            double runtime_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(tp_after-tp_before).count()/1000000.0;
            save_stats(argv[5], stats.solution_length, stats.states_walked, stats.states_processed, stats.max_depth, runtime_ms);///
            std::cout << "[ " << runtime_ms << " ms ]" << std::endl;
        }
        else if(!strcmp("dfs", argv[1])){
            uint a, b;
            uint* buffer = load_puzzle(argv[3], a, b);
            searchstat stats;
            std::chrono::time_point<std::chrono::high_resolution_clock> tp_before = std::chrono::high_resolution_clock::now();
            PUZZLEDIR* sol = dfs(buffer, a, b, str_to_order(argv[2]), 20, stats);
            //std::this_thread::sleep_for(std::chrono::milliseconds(10));
            std::chrono::time_point<std::chrono::high_resolution_clock> tp_after = std::chrono::high_resolution_clock::now();
            if(stats.solution_found) store_solution(convert_sol(sol, stats.solution_length), stats.solution_length, stats.solution_found, argv[4]);
            else store_no_solution(argv[4]);
            double runtime_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(tp_after-tp_before).count()/1000000.0;
            save_stats(argv[5], stats.solution_length, stats.states_walked, stats.states_processed, stats.max_depth, runtime_ms);///
            std::cout << "[ " << runtime_ms << " ms ]" << std::endl;
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
            //uint solution_length;

            searchstat stats;
            std::chrono::time_point<std::chrono::high_resolution_clock> tp_before = std::chrono::high_resolution_clock::now();
            PUZZLEDIR* sol = astr(buffer, a, b, mtc, 20, stats);
            //std::this_thread::sleep_for(std::chrono::milliseconds(10));
            std::chrono::time_point<std::chrono::high_resolution_clock> tp_after = std::chrono::high_resolution_clock::now();
            if(stats.solution_found) store_solution(convert_sol(sol, stats.solution_length), stats.solution_length, stats.solution_found, argv[4]);
            else store_no_solution(argv[4]);
            double runtime_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(tp_after-tp_before).count()/1000000.0;
            save_stats(argv[5], stats.solution_length, stats.states_walked, stats.states_processed, stats.max_depth, runtime_ms);///
            std::cout << "[ " << runtime_ms << " ms ]" << std::endl;
        }
        else {
            std::cout << "Invalid strategy! Available strategies are" << std::endl;
            std::cout << "  bfs" << std::endl << "  dfs" << std::endl << "  astr" << std::endl;
        }
    }
    else {
        std::cout << "Invalid number of arguments!" << std::endl;
        char** argvh = argv;
        char** argvt = argv+argc;
        unsigned char index = 0x0;
        while(argvh != argvt){
            std::cout << (int)(index++) << ": " << (*argvh++) << std::endl;
        }
    }

    return 0;
}

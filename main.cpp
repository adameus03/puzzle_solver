#include <iostream>
#include "tests.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    checker(test_bfs(), "bfs");

    checker(test_dfs(), "dfs");

    return 0;
}

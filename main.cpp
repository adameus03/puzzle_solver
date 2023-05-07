#include <iostream>
#include "tests.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    checker(test_bfs(), "bfs");

    checker(test_dfs(), "dfs");

    checker(test_hamm(), "hamm");

    checker(test_manh(), "manh");

    return 0;
}

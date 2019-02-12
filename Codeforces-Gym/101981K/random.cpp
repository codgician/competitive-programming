#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
#include <cassert>
using namespace std;

char arr[4] = {'L', 'R', 'U', 'D'};

int main()
{
    srand(19260817);
    int row, column;
    cin >> row >> column;
    char buf;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            cin >> buf;
    for (int i = 0; i < 50000; i++)
        cout << arr[rand() % 4];
    return 0;
}
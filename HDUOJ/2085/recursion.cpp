#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 34
using namespace std;

long long int high[SIZE], low[SIZE];

void init()
{
    high[0] = 1;
    low[0] = 0;
    for (int i = 1; i < SIZE; i++)
    {
        high[i] = 3 * high[i - 1] + 2 * low[i - 1];
        low[i] = high[i - 1] + low[i - 1];
    }
}

int main()
{
    init();
    ios::sync_with_stdio(false);
    int n;
    while (cin >> n)
    {
        if (n == -1)
            break;
        cout << high[n] << ", " << low[n] << endl;
    }
    return 0;
}

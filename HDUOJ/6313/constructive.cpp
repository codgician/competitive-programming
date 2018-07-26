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
using namespace std;

#define SIZE 2210

const int prime = 47;

int arr[SIZE][SIZE];

void init()
{
    memset(arr, 0, sizeof(arr));
    for (int i = 0; i < prime; i++)
    {
        for (int j = 0; j < prime; j++)
        {
            int onePos = i - j;
            for (int m = 0; m < prime; m++)
            {
                onePos = (onePos + j) % prime;
                arr[prime * i + m][prime * j + onePos] = 1;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    init();
    int num = 2000;
    cout << num << endl;
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            cout << arr[i][j];
        }
        cout << endl;
    }
    return 0;
}
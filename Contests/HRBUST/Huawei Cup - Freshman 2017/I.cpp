#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#define SIZE 1000001
using namespace std;

bool arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int digitNum;
    while (cin >> digitNum)
    {
        memset(arr, false, sizeof(arr));
        for (int i = 0; i < digitNum; i++)
        {
            int tmp;
            cin >> tmp;
            if (tmp > 0 && tmp < 1000001)
            {
                arr[tmp - 1] = true;
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            if (!arr[i])
            {
                cout << i + 1 << endl;
                break;
            }
        }
    }
    return 0;
}

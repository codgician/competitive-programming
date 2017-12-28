#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 101
#define C_SIZE 10001
using namespace std;

long long int c1[C_SIZE], c2[C_SIZE];
int minNum[SIZE], maxNum[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int fruitType, portionSize;
    while (cin >> fruitType >> portionSize)
    {
        for (int i = 0; i < fruitType; i++)
        {
            cin >> minNum[i] >> maxNum[i];
        }

        memset(c1, 0, sizeof(c1));
        c1[0] = 1;

        for (int i = 0; i < fruitType; i++)
        {
            memset(c2, 0, sizeof(c2));
            for (int j = minNum[i]; j <= min(maxNum[i], portionSize); j++)
            {
                for (int k = 0; j + k <= portionSize; k++)
                {
                    c2[j + k] += c1[k];
                }
            }
            memcpy(c1, c2, sizeof(c2));
        }
        cout << c1[portionSize] << endl;
    }
    return 0;
}

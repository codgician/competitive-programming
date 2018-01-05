#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 1001
#define FIBO_SIZE 20
using namespace std;

int fibo[FIBO_SIZE];
int sg[SIZE];
int hashArr[SIZE];

void init()
{
    fibo[0] = 1;
    fibo[1] = 2;
    for (int i = 2; i < FIBO_SIZE; i++)
    {
        fibo[i] = fibo[i - 1] + fibo[i - 2];
    }
}

int main()
{
    ios::sync_with_stdio(false);

    // Initialize
    init();
    for (int i = 0; i < SIZE; i++)
    {
        memset(hashArr, false, sizeof(hashArr));
        for (int j = 0; fibo[j] <= i; j++)
        {
            hashArr[sg[i - fibo[j]]] = true;
        }
        for (int j = 0; j < SIZE; j++)
        {
            if (!hashArr[j])
            {
                sg[i] = j;
                break;
            }
        }
    }

    int a, b, c;
    while (cin >> a >> b >> c)
    {
        if (a == 0 && b == 0 & c == 0)
            break;
        if ((sg[a] ^ sg[b] ^ sg[c]) == 0)
            cout << "Nacci" << endl;
        else
            cout << "Fibo" << endl;
    }
    return 0;
}

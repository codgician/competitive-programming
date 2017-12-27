#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 999
using namespace std;

int c1[SIZE], c2[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int n;
    while (cin >> n)
    {
        if (n == 0)
            break;

        for (int i = 0; i <= n; i++)
        {
            c1[i] = 1;
            c2[i] = 0;
        }

        for (int i = 2; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                for (int k = 0; k + j <= n; k += i * i)
                {
                    c2[k + j] += c1[j];
                }
            }
            for (int j = 0; j <= n; j++)
            {
                c1[j] = c2[j];
                c2[j] = 0;
            }
        }
        cout << c1[n] << endl;
    }
    return 0;
}

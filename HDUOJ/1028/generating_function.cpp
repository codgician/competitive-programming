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
        // Initialize coefficients
        for (int i = 0; i <= n; i++)
        {
            c1[i] = 1;
            c2[i] = 0;
        }

        // For the second to the nth expression
        for (int i = 2; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                for (int k = 0; j + k <= n; k += i)
                {
                    c2[j + k] += c1[j];
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

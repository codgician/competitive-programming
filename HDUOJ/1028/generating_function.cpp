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
        memset(c1, 0, sizeof(c1));
        c1[0] = 1;

        for (int i = 0; i < n; i++)
        {
            memset(c2, 0, sizeof(c2));
            for (int j = 0; j <= n; j++)
            {
                for (int k = 0; j * (i + 1) + k <= n; k++)
                {
                    c2[j * (i + 1) + k] += c1[k];
                }
            }
            memcpy(c1, c2, sizeof(c2));
        }
        cout << c1[n] << endl;
    }
    return 0;
}

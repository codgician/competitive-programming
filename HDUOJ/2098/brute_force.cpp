#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 10001
using namespace std;

bool check[SIZE];
int prime[SIZE];
int primePt = 0;

void init()
{
    memset(check, false, sizeof(check));
    for (int i = 2; i < SIZE; i++)
    {
        if (!check[i])
        {
            prime[primePt++] = i;
        }
        for (int j = 0; j < primePt && i * prime[j] < SIZE; j++)
        {
            check[i * prime[j]] = true;
            if (i % prime[j] == 0)
            {
                break;
            }
        }
    }
}

int main()
{
    init();
    ios::sync_with_stdio(false);
    int n;
    while (cin >> n)
    {
        if (n == 0)
            break;
        int ans = 0;
        for (int i = 0; prime[i] < n / 2; i++)
        {
            if (binary_search(prime + 0, prime + primePt, (n - prime[i])))
            {
                ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

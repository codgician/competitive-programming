#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 200
using namespace std;

long long int para[SIZE];
int n;
const int mod = 1e9 + 7;

long long int get2Pow(int n)
{
    int ans = 1;
    for (int i = n; i > 0; i--)
    {
        ans <<= 1;
        ans %= mod;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> n)
    {
        long long int ans = 0;
        int appearTimes = get2Pow(n - 1);
        for (int i = 0; i < n; i++)
        {
            cin >> para[i];
            para[i] %= mod;
            ans += ((para[i] * appearTimes) % mod);
        }
        cin >> para[n];
        ans += para[n];
        cout << ans % mod << endl;
    }
    return 0;
}

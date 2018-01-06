#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int getBitNum(unsigned long long int n)
{
    int ans = 0;
    while (n)
    {
        ans++;
        n >>= 1;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    long long int n, k;
    cin >> n >> k;
    if (k == 1)
    {
        cout << n << endl;
    }
    else
    {
        unsigned long long int ans = (unsigned long long int)1 << getBitNum(n);
        cout << ans - 1 << endl;
    }
    return 0;
}

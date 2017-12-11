#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define C 1000.0
using namespace std;

double getAns(int n, double delta)
{
    int maxi = (n + 1) / 2;
    double ans = delta * (1 + maxi) * maxi;
    if (n & 1)
    {
        ans -= delta * maxi;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int n;
    while (cin >> n)
    {
        if (n == 1)
        {
            cout << 0 << endl;
        }
        else
        {
            double delta = C / (n - 1) - C / n;
            int ans = getAns(n - 2, delta) + 0.5;
            cout << ans << endl;
        }
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

long long int n, r, floort;
double t;

long long int quasiEuclidean(long long int a, long long int b, long long int c, long long int n)
{
    if (n == 0)
        return 0;

    long long int gcd = __gcd(a, __gcd(b, c));
    a /= gcd, b /= gcd, c /= gcd;

    double k = (a * t + b) / c;
    if (k < 1)
    {
        long long int m = n * k;
        return n * m - quasiEuclidean(a * c, -b * c, a * a * r - b * b, m);
    }

    long long int tmp = (n & 1) ? ((n + 1) >> 1) * n : (n >> 1) * (n + 1);
    return (long long int)k * tmp + quasiEuclidean(a, b - c * (long long int)k, c, n);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        cin >> n >> r;
        t = sqrt(r);
        floort = (int)t;

        long long int ans;
        if (floort * floort == r)
            ans = (floort & 1) ? (n & 1 ? -1 : 0) : n;
        else
            ans = n - ((quasiEuclidean(1, 0, 1, n) - (quasiEuclidean(1, 0, 2, n) << 1)) << 1);
        cout << ans << endl;
    }

    return 0;
}
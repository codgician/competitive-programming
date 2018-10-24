#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <functional>
#include <iterator>
#define UPPER_LIMIT ((long long int)1 << k)
using namespace std;

long long int extEuclidean(long long int a, long long int b, long long int &x, long long int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    long long int gcd = extEuclidean(b, a % b, x, y);
    long long int tmp = x;
    x = y;
    y = tmp - y * (a / b);

    return gcd;
}

int main()
{
    ios::sync_with_stdio(false);
    long long int a, b, c, k;
    while (cin >> a >> b >> c >> k)
    {
        if (a == 0 && b == 0 && c == 0 && k == 0)
            break;

        long long int x, y;
        long long int gcd = extEuclidean(c, UPPER_LIMIT, x, y);

        if ((b - a) % gcd != 0)
        {
            cout << "FOREVER" << endl;
            continue;
        }

        long long int ans = x * ((b - a) / gcd);

        if (ans < 0)
            ans = UPPER_LIMIT - (-ans) % UPPER_LIMIT;

        ans = ans % (UPPER_LIMIT / gcd);
        cout << ans << endl;
    }

    return 0;
}
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define INF 9999999
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int n, m, x, y;
    while (cin >> n >> m >> x >> y)
    {
        if (n > m)
            swap(n, m);
        if (x > y)
            swap(x, y);

        int ans = INF;

        // Put it aside violently
        if (x < n)
        {
            if (x == 0)
                ans = 0;
            else
                ans = min(ans, x + 1);
        }
        else if (x % n == 0)
        {
            ans = min(ans, n);
        }
        else
        {
            ans = min(ans, n + 1);
        }

        // Put it into a square
        // and the rest close to it
        int sqrLen = sqrt(x);
        int restNum = x - sqrLen * sqrLen;
        if (restNum == 0)
            ans = min(ans, 2 * sqrLen);
        else if (restNum <= sqrLen)
            ans = min(ans, 2 * sqrLen + 1);
        else
            ans = min(ans, 2 * sqrLen + 2);

        cout << ans << endl;
    }
    return 0;
}

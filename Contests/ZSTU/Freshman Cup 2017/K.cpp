#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int x1, y1, x2, y2, x3, y3, x4, y4;
    while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4)
    {
        if (x1 < x2)
            swap(x1, x2);
        if (x3 < x4)
            swap(x3, x4);
        if (y1 < y2)
            swap(y1, y2);
        if (y3 < y4)
            swap(y3, y4);

        int ax1 = min(x1, x3);
        int ay1 = min(y1, y3);
        int ax2 = max(x2, x4);
        int ay2 = max(y2, y4);

        if (ax1 < ax2 || ay1 < ay2)
        {
            cout << 0 << endl;
        }
        else
        {
            int ans = abs(ax1 - ax2) * abs(ay1 - ay2);
            cout << ans << endl;
        }
    }
    return 0;
}

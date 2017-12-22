#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define INF 99999
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int barLen, sideLen, topLen;
    cin >> barLen >> sideLen >> topLen;
    int sideNum = 4, topNum = 2;

    int ans = 0;
    while (sideNum > 0 && topNum > 0)
    {
        int closestX, closestY, closestVal = INF;
        for (int x = 0; x <= sideNum; x++)
        {
            for (int y = 0; y <= topNum; y++)
            {
                if (sideLen * x + topLen * y <= barLen)
                {
                    if (closestVal > barLen - (sideLen * x + topLen * y))
                    {
                        closestVal = barLen - (sideLen * x + topLen * y);
                        closestX = x;
                        closestY = y;
                    }
                }
            }
        }

        while (sideNum >= closestX && topNum >= closestY)
        {
            sideNum -= closestX;
            topNum -= closestY;
            ans++;
        }
    }

    if (sideNum != 0)
    {
        int t = sideNum / (barLen / sideLen);
        if (sideNum < (barLen / sideLen) || sideNum % (barLen / sideLen) != 0)
        {
            t++;
        }
        ans += t;
    }
    if (topNum != 0)
    {
        int t = topNum / (barLen / topLen);
        if (topNum < (barLen / topLen) || topNum % (barLen / topLen) != 0)
        {
            t++;
        }
        ans += t;
    }
    cout << ans << endl;
    return 0;
}

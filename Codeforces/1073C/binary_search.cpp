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

#define SIZE 200010

int xPfx[SIZE], yPfx[SIZE];
int finalx, finaly;
int len;

bool check(int cntLen)
{
    for (int i = 1; i <= len - cntLen + 1; i++)
    {
        int x = abs(xPfx[i - 1] + xPfx[len] - xPfx[i + cntLen - 1] - finalx);
        int y = abs(yPfx[i - 1] + yPfx[len] - yPfx[i + cntLen - 1] - finaly);
        if (x + y <= cntLen && ((x + y) & 1) == (cntLen & 1))
            return true;
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> len;
    string str;
    cin >> str;

    memset(xPfx, 0, sizeof(xPfx));
    memset(yPfx, 0, sizeof(yPfx));
    for (int i = 0; i < len; i++)
    {
        if (str[i] == 'U')
            yPfx[i + 1] = 1;
        else if (str[i] == 'D')
            yPfx[i + 1] = -1;
        else if (str[i] == 'L')
            xPfx[i + 1] = -1;
        else
            xPfx[i + 1] = 1;

        xPfx[i + 1] += xPfx[i];
        yPfx[i + 1] += yPfx[i];
    }

    cin >> finalx >> finaly;

    int leftPt = 0, rightPt = len;
    int ans = -1;
    while (leftPt <= rightPt)
    {
        int midPt = (leftPt + rightPt) >> 1;
        if (check(midPt))
        {
            rightPt = midPt - 1;
            ans = midPt;
        }
        else
        {
            leftPt = midPt + 1;
        }
    }
    cout << ans << endl;
    return 0;
}
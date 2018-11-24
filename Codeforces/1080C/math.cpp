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
#include <cassert>
using namespace std;

long long int num[2];

pair<long long int, long long int> getNum(long long int x1, long long int y1, long long int x2, long long int y2)
{
    long long int row = abs(x2 - x1) + 1, column = abs(y2 - y1) + 1;
    if (((x1 + y1) & 1) == 0)
        return make_pair((row * column + 1) >> 1, (row * column) >> 1);
    return make_pair((row * column) >> 1, (row * column + 1) >> 1);
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
        long long int row, column;
        cin >> row >> column;

        num[0] = (row * column + 1) >> 1;
        num[1] = (row * column) >> 1;

        long long int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        long long int row1 = abs(x2 - x1) + 1, column1 = abs(y2 - y1) + 1;
        long long int x3, y3, x4, y4;
        cin >> x3 >> y3 >> x4 >> y4;
        long long int row2 = abs(x4 - x3) + 1, column2 = abs(y4 - y3) + 1;

        long long int leftx = max(x1, x3), rightx = min(x2, x4);
        long long int lefty = max(y1, y3), righty = min(y2, y4);
        long long int row3= abs(rightx - leftx) + 1, column3 = abs(righty - lefty) + 1;

        pair<long long int, long long int> oWhitePir = getNum(x1, y1, x2, y2);
        pair<long long int, long long int> oBlackPir = getNum(x3, y3, x4, y4);

        if (leftx <= rightx && lefty <= righty)
        {
            // Has Intersection
            pair<long long int, long long int> oInsPir = getNum(leftx, lefty, rightx, righty);

            long long int oWhiteNum = oWhitePir.first + oBlackPir.first - oInsPir.first;
            long long int oBlackNum = oWhitePir.second + oBlackPir.second - oInsPir.second;

            long long int nWhiteNum = row1 * column1 - row3 * column3;
            long long int nBlackNum = row2 * column2;

            num[0] += nWhiteNum - oWhiteNum;
            num[1] += nBlackNum - oBlackNum;
        }
        else
        {
            long long int oWhiteNum = oWhitePir.first + oBlackPir.first;
            long long int oBlackNum = oWhitePir.second + oBlackPir.second;

            long long int nWhiteNum = row1 * column1;
            long long int nBlackNum = row2 * column2;

            num[0] += nWhiteNum - oWhiteNum;
            num[1] += nBlackNum - oBlackNum;
        }

        cout << num[0] << " " << num[1] << endl;

    }

    return 0;
}
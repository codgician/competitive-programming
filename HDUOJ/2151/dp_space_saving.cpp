#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 101
using namespace std;

int dp[2][SIZE]; // step i, tree j

int main()
{
    ios::sync_with_stdio(false);
    int treeNum, startPos, timeLen, endPos;
    while (cin >> treeNum >> startPos >> timeLen >> endPos)
    {
        if (timeLen % 2 == (startPos % 2 == endPos % 2))
        {
            cout << 0 << endl;
            continue;
        }

        memset(dp, 0, sizeof(dp));
        startPos--;
        endPos--;
        dp[0][startPos] = 1;

        for (int i = 1; i <= timeLen; i++)
        {
            for (int j = 0; j < treeNum; j++)
            {
                dp[1][j] += (dp[0][j - 1] + dp[0][j + 1]);
            }
            for (int j = 0; j < treeNum; j++)
            {
                dp[0][j] = dp[1][j];
                dp[1][j] = 0;
            }
        }

        cout << dp[0][endPos] << endl;
    }
    return 0;
}

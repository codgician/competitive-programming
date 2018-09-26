#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
using namespace std;

#define MAP_SIZE 1010
#define BLOCK_SIZE 40

bool arr[MAP_SIZE][MAP_SIZE];
int dp[MAP_SIZE][MAP_SIZE][BLOCK_SIZE], pfxSum[MAP_SIZE][MAP_SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int row, column, qNum;
    while (cin >> row >> column >> qNum)
    {
        for (int i = 1; i <= row; i++)
        {
            pfxSum[i][0] = 0;
            for (int j = 1; j <= column; j++)
            {
                char ch;
                cin >> ch;
                if (ch == 'X')
                    arr[i][j] = 1;
                else
                    arr[i][j] = 0;

                pfxSum[i][j] = pfxSum[i][j - 1] + arr[i][j];
            }
        }

        int lim = sqrt(row);

        // For div <= lim
        for (int i = 1; i <= row; i++)
        {
            for (int j = 1; j <= column; j++)
            {
                for (int k = 1; k <= lim; k++)
                {
                    dp[i][j][k] = arr[i][j];

                    if (i <= k)
                        continue;

                    if (j - k > 0)
                    {
                        dp[i][j][k] += dp[i - k][j - k][k] + pfxSum[i - k][j] - pfxSum[i - k][j - k];
                    }
                    else
                    {
                        dp[i][j][k] += pfxSum[i - k][j];
                        if (i > (k << 1))
                        {
                            dp[i][j][k] += dp[i - (k << 1)][j][k] + pfxSum[i - (k << 1)][j - 1];
                        }
                    }

                    if (j + k <= column)
                    {
                        dp[i][j][k] += dp[i - k][j + k][k] + pfxSum[i - k][j + k - 1] - pfxSum[i - k][j];
                    }
                    else
                    {
                        dp[i][j][k] += pfxSum[i - k][column] - pfxSum[i - k][j];
                        if (i > (k << 1))
                        {
                            dp[i][j][k] += dp[i - (k << 1)][j][k] + pfxSum[i - (k << 1)][column] - pfxSum[i - (k << 1)][j];
                        }
                    }

                    if (i > (k << 1))
                    {
                        dp[i][j][k] -= dp[i - (k << 1)][j][k];
                    }
                }
            }
        }

        while (qNum--)
        {
            int x, y, div;
            cin >> x >> y >> div;

            if (div <= lim)
            {
                // use pre-initialized data
                cout << dp[x][y][div] << endl;
            }
            else
            {
                // brute force
                int ans = 0;
                for (int i = x; i > 0; i -= div)
                {
                    int leftPt = max(1, y - x + i);
                    int rightPt = min(column, y + x - i);
                    ans += pfxSum[i][rightPt] - pfxSum[i][leftPt - 1];
                }
                cout << ans << endl;
            }
        }
    }

    return 0;
}
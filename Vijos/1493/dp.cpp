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
#define SIZE 101
using namespace std;

int arr[SIZE][SIZE];
long long int dp[SIZE << 1][SIZE][SIZE];
int dir[2][2] = {1, 0, 0, 1};

int main()
{
    ios::sync_with_stdio(false);
    int row, column;
    cin >> row >> column;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            cin >> arr[i][j];
        }
    }

    memset(dp, 0, sizeof(dp));
    for (int i = 0; i <= row + column - 2; i++)
    {
        for (int x1 = 0; x1 < row; x1++)
        {
            for (int x2 = 0; x2 < row; x2++)
            {
                int y1 = i - x1;
                int y2 = i - x2;

                for (int j = 0; j < 4; j++)
                {
                    int nextx1 = x1 + dir[(j & 1) ? 1 : 0][0], nexty1 = y1 + dir[(j & 1) ? 1 : 0][1];
                    int nextx2 = x2 + dir[(j & 2) ? 1 : 0][0], nexty2 = y2 + dir[(j & 2) ? 1 : 0][1];

                    if (nextx1 == nextx2 && nexty1 == nexty2)
                        dp[i + 1][nextx1][nextx2] = max(dp[i + 1][nextx1][nextx2], dp[i][x1][x2] + arr[nextx1][nexty1]);
                    else
                        dp[i + 1][nextx1][nextx2] = max(dp[i + 1][nextx1][nextx2], dp[i][x1][x2] + arr[nextx1][nexty1] + arr[nextx2][nexty2]);
                }
            }
        }
    }

    cout << dp[row + column - 2][row - 1][row - 1] << endl;
    return 0;
}

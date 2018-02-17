#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
#define SIZE 2001
using namespace std;

const double eps = 1e-10;

double dp[SIZE][SIZE], c[SIZE], connLost1Pow[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int queueSize, startPos, k;
    while (cin >> queueSize >> startPos >> k)
    {
        double actFail, connLost, actSuccess, down;
        cin >> actFail >> connLost >> actSuccess >> down;

        if (down < eps)
        {
            cout << "0.00000" << endl;
            continue;
        }

        double connLost1 = connLost / (1 - actFail);
        double actSuccess1 = actSuccess / (1 - actFail);
        double down1 = down / (1 - actFail);

        connLost1Pow[0] = 1;
        for (int i = 1; i <= queueSize; i++)
            connLost1Pow[i] = connLost1Pow[i - 1] * connLost1;

        dp[1][1] = down1 / (1 - connLost1);
        c[1] = down1;
        for (int i = 2; i <= queueSize; i++)
        {
            for (int j = 2; j <= k && j <= i; j++)
                c[j] = actSuccess1 * dp[i - 1][j - 1] + down1;
            for (int j = k + 1; j <= i; j++)
                c[j] = actSuccess1 * dp[i - 1][j - 1];

            dp[i][i] = 0;
            for (int j = 1; j <= i; j++)
            {
                dp[i][i] += connLost1Pow[i - j] * c[j];
            }
            dp[i][i] /= (1 - connLost1Pow[i]);

            dp[i][1] = connLost1 * dp[i][i] + c[1];
            for (int j = 2; j < i; j++)
            {
                dp[i][j] = connLost1 * dp[i][j - 1] + c[j];
            }
        }
        cout << fixed << setprecision(5) << dp[queueSize][startPos] << endl;
    }
    return 0;
}

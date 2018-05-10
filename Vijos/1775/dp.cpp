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
#define LEN_SIZE 360
#define CARD_SIZE 4
using namespace std;

int scoreArr[LEN_SIZE];
int cardArr[CARD_SIZE];
long long int dp[41][41][41][41];

int main()
{
    ios::sync_with_stdio(false);
    int len, cardNum;
    cin >> len >> cardNum;
    for (int i = 0; i < len; i++)
    {
        cin >> scoreArr[i];
    }

    memset(cardArr, 0, sizeof(cardArr));
    for (int i = 0; i < cardNum; i++)
    {
        int cnt;
        cin >> cnt;
        cardArr[--cnt]++;
    }

    memset(dp, 0, sizeof(dp));
    dp[0][0][0][0] = scoreArr[0];
    for (int i = 0; i <= cardArr[0]; i++)
    {
        for (int j = 0; j <= cardArr[1]; j++)
        {
            for (int k = 0; k <= cardArr[2]; k++)
            {
                for (int l = 0; l <= cardArr[3]; l++)
                {
                    int cntPos = i + (j << 1) + (k << 1) + k + (l << 2);
                    if (cntPos >= len)
                        continue;

                    if (i > 0)
                        dp[i][j][k][l] = max(dp[i][j][k][l], dp[i - 1][j][k][l] + scoreArr[cntPos]);
                    if (j > 0)
                        dp[i][j][k][l] = max(dp[i][j][k][l], dp[i][j - 1][k][l] + scoreArr[cntPos]);
                    if (k > 0)
                        dp[i][j][k][l] = max(dp[i][j][k][l], dp[i][j][k - 1][l] + scoreArr[cntPos]);
                    if (l > 0)
                        dp[i][j][k][l] = max(dp[i][j][k][l], dp[i][j][k][l - 1] + scoreArr[cntPos]);
                } 
            }
        }
    }

    cout << dp[cardArr[0]][cardArr[1]][cardArr[2]][cardArr[3]] << endl;

    return 0;
}
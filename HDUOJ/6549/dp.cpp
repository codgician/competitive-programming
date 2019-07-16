#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

int dp[SIZE][20][26];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len, modLim, secLim;
    while (cin >> len >> modLim >> secLim) {
        string str; cin >> str;
        int len = str.size();
        for (int i = 0; i < len; i++)
            for (int j = 0; j < 20; j++)
                fill(dp[i][j] + 0, dp[i][j] + 26, INT_MAX);

        dp[0][1][str[0] - 'a'] = 0;
        for (int i = 0; i < 26; i++)
            if (str[0] - 'a' != i)
                dp[min(modLim - 1, len - 1)][1][i] = 1;

        for (int i = 0; i < len - 1; i++) {
            for (int j = 1; j <= secLim; j++) {
                for (int k = 0; k < 26; k++) {
                    if (dp[i][j][k] == INT_MAX)
                        continue;
                    if (str[i + 1] - 'a' == k)
                        dp[i + 1][j][k] = min(dp[i + 1][j][k], dp[i][j][k]);
                    else
                        dp[i + 1][j + 1][str[i + 1] - 'a'] = min(dp[i + 1][j + 1][str[i + 1] - 'a'], dp[i][j][k]);
                    dp[min(i + modLim, len - 1)][j][k] = min(dp[min(i + modLim, len - 1)][j][k], dp[i][j][k] + 1); 
                }
            }
        }

        int ans = INT_MAX;
        for (int j = 1; j <= secLim; j++)
            for (int k = 0; k < 26; k++)
                ans = min(ans, dp[len - 1][j][k]);
        cout << ans << '\n';
    }

    return 0;
}
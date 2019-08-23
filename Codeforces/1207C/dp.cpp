#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

long long int dp[SIZE][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int len; long long int a, b; cin >> len >> a >> b;
        string str; cin >> str;
        for (int i = 0; i <= len; i++)
            for (int j = 0; j < 2; j++)
                dp[i][j] = LLONG_MAX;

        dp[0][1] = 2 * a + 3 * b;
        dp[0][0] = a + 2 * b;
        for (int i = 1; i < len; i++) {
            if (str[i] == '0') {
                if (dp[i - 1][0] != LLONG_MAX) {
                    dp[i][0] = min(dp[i][0], dp[i - 1][0] + a + b);         // 0 -> 0
                    dp[i][1] = min(dp[i][1], dp[i - 1][0] + 2 * a + 2 * b); // 0 -> 1
                }
                if (dp[i - 1][1] != LLONG_MAX) {
                    dp[i][0] = min(dp[i][0], dp[i - 1][1] + 2 * a + b);     // 1 -> 0
                    dp[i][1] = min(dp[i][1], dp[i - 1][1] + a + 2 * b);     // 1 -> 1
                }
            } else {
                if (dp[i - 1][1] != LLONG_MAX)
                    dp[i][1] = min(dp[i][1], dp[i - 1][1] + a + 2 * b);     // 1 -> 1
            }
        }

        cout << dp[len - 1][0] << '\n';
    }

    return 0;
}
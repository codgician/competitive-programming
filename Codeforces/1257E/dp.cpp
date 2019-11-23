#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

int pos[SIZE], dp[SIZE][3];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int num[3], len = 0;
    for (int t = 0; t < 3; t++)
        cin >> num[t], len += num[t];
    for (int t = 0; t < 3; t++) {
        for (int i = 0; i < num[t]; i++) {
            int cnt; cin >> cnt;
            pos[cnt] = t;
        }
    }
    for (int i = 1; i <= len; i++)
        fill(dp[i] + 0, dp[i] + 3, INT_MAX);
    fill(dp[0] + 0, dp[0] + 3, 0);
    for (int i = 0; i < len; i++)
        for (int j = 0; j < 3; j++)
            for (int k = j; k < 3; k++)
                dp[i + 1][k] = min(dp[i + 1][k], dp[i][j] + (k != pos[i + 1]));
    cout << min({dp[len][0], dp[len][1], dp[len][2]}) << '\n';
    return 0;
}
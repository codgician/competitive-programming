#include <bits/stdc++.h>
using namespace std;

#define SIZE 510

int arr[SIZE];

double dp[2][SIZE][SIZE], dp1[SIZE][SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len, lowLim, uppLim; cin >> len >> lowLim >> uppLim;
    for (int i = 1; i <= len; i++)
        cin >> arr[i];

    memset(dp, 0, sizeof(dp)); dp[0][0][0] = 1;
    for (int i = 1; i <= len; i++) {
        dp[i & 1][0][0] = 1;
        for (int j = 1; j <= i; j++) {
            for (int k = 1; k <= uppLim; k++)
                dp[i & 1][j][k] = dp[(i & 1) ^ 1][j][k];
            for (int k = arr[i]; k <= uppLim; k++)
                dp[i & 1][j][k] += dp[(i & 1) ^ 1][j - 1][k - arr[i]] * j / (len - j + 1);
        }
    }

    double ans = 0;
    for (int i = 1; i <= len; i++) {
        for (int k = 0; k <= uppLim; k++)
            dp1[0][k] = dp[len & 1][0][k];
        for (int j = 1; j <= len; j++) {
            for (int k = 0; k < arr[i]; k++)
                dp1[j][k] = dp[len & 1][j][k];
            for (int k = arr[i]; k <= uppLim; k++)
                dp1[j][k] = dp[len & 1][j][k] - dp1[j - 1][k - arr[i]] * j / (len - j + 1);
        }

        int leftLim = max(0, lowLim - arr[i] + 1), rightLim = min(uppLim - arr[i], lowLim);
        for (int k = leftLim; k <= rightLim; k++)
            for (int j = 1; j < len; j++)
                ans += dp1[j - 1][k] / (len - j + 1);
    }

    cout << fixed << setprecision(12) << ans << '\n';
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

long long int arr[SIZE][2], dp[SIZE][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; cin >> len;
    for (int t = 0; t < 2; t++)
        for (int i = 0; i < len; i++)
            cin >> arr[i][t];

    memset(dp, 0, sizeof(dp));
    dp[0][0] = arr[0][0]; dp[0][1] = arr[0][1];
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < 2; j++) {
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            dp[i + 1][j ^ 1] = max(dp[i + 1][j ^ 1], dp[i][j] + arr[i + 1][j ^ 1]);
        }
    }

    cout << max(dp[len - 1][0], dp[len - 1][1]) << '\n';
    return 0;
}
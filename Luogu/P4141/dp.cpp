#include <bits/stdc++.h>
using namespace std;

#define SIZE 2010

int arr[SIZE];
int dp[SIZE], ans[SIZE][SIZE];
const int mod = 10;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len, siz;
    cin >> len >> siz;
    for (int i = 1; i <= len; i++)
        cin >> arr[i];
    dp[0] = 1;
    for (int i = 1; i <= len; i++)
        for (int j = siz; j >= arr[i]; j--)
            dp[j] = (dp[j] + dp[j - arr[i]]) % mod;
    for (int i = 1; i <= len; i++) {
        ans[i][0] = 1;
        for (int j = 1; j <= siz; j++) {
            if (j >= arr[i])
                ans[i][j] = (dp[j] - ans[i][j - arr[i]] + mod) % mod;
            else
                ans[i][j] = dp[j];
            cout << ans[i][j];
        }
        cout << endl;
    }

    return 0;
}
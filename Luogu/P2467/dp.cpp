#include <bits/stdc++.h>
using namespace std;

#define SIZE 4210

long long int dp[2][SIZE], mod;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int num;
    cin >> num >> mod;
    memset(dp, 0, sizeof(dp));
    dp[0][2] = 1;
    for (int i = 3; i <= num; i++) {
        for (int j = 2; j <= i; j++) {
            dp[i & 1][j] = (dp[i & 1][j - 1] + dp[!(i & 1)][i - j + 1]) % mod;
        }
    }

    long long int ans = 0;
    for (int i = 2; i <= num; i++)
        ans = (ans + dp[num & 1][i]) % mod;
    cout << (ans << 1) % mod << endl;

    return 0;
}
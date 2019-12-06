#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 200010
const int mod = 998244353;
 
long long int dp[SIZE], prob[SIZE];
 
long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = ret * a % mod;
        a = a * a % mod; n >>= 1;
    }
    return ret;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int len; cin >> len;
    long long int inv = fastPow(100, mod - 2, mod);
    for (int i = 1; i <= len; i++)
        cin >> prob[i], prob[i] = prob[i] * inv % mod;
 
    dp[0] = 0;
    for (int i = 1; i <= len; i++) {
        dp[i] = (dp[i - 1] + 1) % mod;
        dp[i] = dp[i] * fastPow(prob[i], mod - 2, mod) % mod;
    }
 
    cout << dp[len] << '\n';
    return 0;
}
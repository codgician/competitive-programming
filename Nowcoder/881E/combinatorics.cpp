#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 12010
 
const int mod = 1e9 + 7;
 
long long int factorial[SIZE], invFactorial[SIZE];
 
long long int fastPow(long long int a, long long int n) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = ret * a % mod;
        a = a * a % mod; n >>= 1;
    }
    return ret;
}
 
void initFactorial() {
    factorial[0] = 1;
    for (int i = 1; i < SIZE; i++)
        factorial[i] = factorial[i - 1] * i % mod;
}
 
void initInvFactorial() {
    invFactorial[SIZE - 1] = fastPow(factorial[SIZE - 1], mod - 2);
    for (int i = SIZE - 2; i >= 0; i--)
        invFactorial[i] = invFactorial[i + 1] * (i + 1) % mod;
}
 
long long int comb(long long int n, long long int m) {
    return m > n ? 0 : factorial[n] * invFactorial[m] % mod * invFactorial[n - m] % mod;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initFactorial(); initInvFactorial();
    int n, m;
    while (cin >> n >> m) {
        long long int ans = comb((n + m) << 1, n + m);
        if (n > 0)
            ans = (ans - comb((n + m) << 1, n - 1) + mod) % mod;
        if (m > 0)
            ans = (ans - comb((n + m) << 1, m - 1) + mod) % mod;
        cout << ans << '\n';
    }
 
    return 0;
}
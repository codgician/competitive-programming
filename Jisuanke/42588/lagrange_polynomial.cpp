#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010
const int mod = 1e9 + 7;

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = ret * a % mod;
        a = a * a % mod; n >>= 1;
    }
    return ret;
}

long long int val1[SIZE], val2[SIZE], pre[SIZE], suf[SIZE], rem[SIZE];
long long int factorials[SIZE], invFactorials[SIZE];

void init(int exp) {
    factorials[0] = 1;
    for (int i = 1; i <= exp + 2; i++)
        factorials[i] = factorials[i - 1] * i % mod;
    invFactorials[exp + 2] = fastPow(factorials[exp + 2], mod - 2, mod);
    for (int i = exp + 1; i >= 0; i--)
        invFactorials[i] = invFactorials[i + 1] * (i + 1) % mod;

    val1[0] = 0; val2[0] = fastPow(2, exp + 1, mod) - 1;
    for (int i = 1; i <= exp + 2; i++) {
        val1[i] = (val1[i - 1] + (fastPow(i << 2, exp + 1, mod) - 1) * fastPow((i << 2) - 1, mod - 2, mod) - 1) % mod;
        val2[i] = (val2[i - 1] + (fastPow((i << 2) + 2, exp + 1, mod) - 1) * fastPow((i << 2) + 1, mod - 2, mod)) % mod;
    }
}

long long int lagrangeCons(long long int x, int exp, long long int * y) {
    x %= mod; pre[0] = x; suf[exp] = x - exp;
    for (int i = 1; i <= exp; i++) 
        pre[i] = pre[i - 1] * (x - i) % mod;
    for (int i = exp - 1; i >= 0; i--)
        suf[i] = suf[i + 1] * (x - i) % mod;

    long long int ret = 0;
    for (int i = 0; i <= exp; i++) {
        long long int cnt = y[i] * (i == 0 ? 1ll : pre[i - 1]) % mod * (i == exp ? 1ll : suf[i + 1]) % mod;
        cnt = cnt * invFactorials[i] % mod * invFactorials[exp - i] % mod;
        cnt = ((exp + i) & 1) ? -cnt : cnt;
        ret = (ret + cnt + mod) % mod;
    }
    return ret;
}

long long int calc(long long int i, int t) {
    if (i == 0)
        return 0;
    if ((i & 3) == 0)
        return ((fastPow(i, t + 1, mod) - 1) * fastPow(i - 1, mod - 2, mod) - 1) % mod;
    if ((i & 3) == 1)
        return t;
    if ((i & 3) == 2)
        return (fastPow(i, t + 1, mod) - 1) * fastPow(i - 1, mod - 2, mod) % mod;
    return t >> 1;
}

long long int solve(long long int x, int t) {
    long long int cyc = ((x + 1) >> 2) - 1, ret = 0;

    if (cyc >= 0) {
        ret = (ret + lagrangeCons(cyc, t + 1, val1)) % mod;
        ret = (ret + lagrangeCons(cyc, t + 1, val2)) % mod;
        ret = (ret + (cyc + 1) % mod * (t + (t >> 1)) % mod) % mod;
    }
    
    for (long long int i = ((cyc + 1) << 2); i <= x; i++)
        ret = (ret + calc(i, t)) % mod;
    return (ret + mod) % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int t; long long int x, y;
    cin >> t >> x >> y; init(t);
    cout << (solve(y, t) - solve(x - 1, t) + mod) % mod << '\n';

    return 0;
}

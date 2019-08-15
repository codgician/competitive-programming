#include <bits/stdc++.h>
using namespace std;
 
const int mod = 1e9 + 7;

long long int quasiEuclidean(long long int a, long long int b, long long int c, long long int n) {
    if (n < 0)
        return 0;
    if (a == 0)
        return (n + 1) % mod * (b / c) % mod;
 
    if (a >= c || b >= c) {
        long long int tmp = ((n & 1) ? ((n + 1) >> 1) % mod * (n % mod) : (n >> 1) % mod * ((n + 1) % mod)) % mod;
        return ((a / c) % mod * (tmp % mod) % mod + (b / c) % mod * ((n + 1) % mod) % mod + quasiEuclidean(a % c, b % c, c, n) % mod) % mod;
    }
    long long int m = ((__int128)a * n + b) / c;
    return (n % mod * (m % mod) % mod - quasiEuclidean(c, c - b - 1, a, m - 1) % mod + mod) % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    long long int n, m; cin >> n >> m;
    long long int ans = 0, p = 1;
    for (int i = 0; p <= m; i++) {
        long long int cst = (m / p) & 1;
        if (cst != 0) {
            long long int cnt = (quasiEuclidean(m, 0, p, n) - (quasiEuclidean(m, 0, p << 1, n) << 1) % mod + mod) % mod;
            ans = (ans + p % mod * cnt % mod) % mod;
        }
        p <<= 1;
    }
    cout << ans << '\n';
    return 0;
}
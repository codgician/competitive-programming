#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010
#define LAG_SIZE 1010
const int mod = 998244353;

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod; n >>= 1;
    }
    return ret;
}

int primes[SIZE], minFac[SIZE], primesPt, lim;
long long int g[SIZE][2], dsc[SIZE], pfx[SIZE], inv2, inv3;
pair<int, int> indx[SIZE];

long long int factorials[SIZE], invFactorials[SIZE];

void initPrimes(int siz, int k) {
    inv2 = fastPow(2, mod - 2, mod); inv3 = fastPow(3, mod - 2, mod);
    fill(minFac + 0, minFac + siz + 1, 0); primesPt = 0;
    for (int i = 2; i <= siz; i++) {
        if (minFac[i] == 0)
            minFac[i] = i, primes[primesPt++] = i;
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], siz / i); j++)
            minFac[i * primes[j]] = primes[j];
    }

    pfx[0] = fastPow(primes[0], k, mod);
    for (int i = 1; i < primesPt && primes[i] <= siz; i++)
        pfx[i] = (pfx[i - 1] + fastPow(primes[i], k, mod)) % mod;
}

long long int val[LAG_SIZE], pre[LAG_SIZE], suf[LAG_SIZE], rem[LAG_SIZE];

void init(int k) {
    factorials[0] = 1;
    for (int i = 1; i < LAG_SIZE; i++)
        factorials[i] = factorials[i - 1] * i % mod;
    invFactorials[LAG_SIZE - 1] = fastPow(factorials[LAG_SIZE - 1], mod - 2, mod);
    for (int i = LAG_SIZE - 2; i >= 0; i--)
        invFactorials[i] = invFactorials[i + 1] * (i + 1) % mod;

    val[0] = 0; val[1] = 1;
    for (int i = 2; i <= k + 1; i++) {
        val[i] = val[i - 1] + fastPow(i, k, mod);
        val[i] = val[i] >= mod ? val[i] - mod : val[i]; 
    }
}

long long int lagrangeCons(long long int x, int len, long long int * y) {
    x %= mod; pre[0] = x; suf[len] = x - len;
    for (int i = 1; i <= len; i++) 
        pre[i] = pre[i - 1] * (x - i) % mod;
    for (int i = len - 1; i >= 0; i--)
        suf[i] = suf[i + 1] * (x - i) % mod;

    long long int ret = 0;
    for (int i = 0; i <= len; i++) {
        long long int cnt = y[i] * (i == 0 ? 1ll : pre[i - 1]) % mod * (i == len ? 1ll : suf[i + 1]) % mod;
        cnt = cnt * invFactorials[i] % mod * invFactorials[len - i] % mod;
        cnt = ((len + i) & 1) ? -cnt : cnt;
        ret = (ret + cnt + mod) % mod;
    }
    return ret;
}

long long int f(int p, int e, int k) {
    return (fastPow(p, e * k, mod) - fastPow(p, (e - 1) * k, mod) + mod) % mod;
}

long long int sieve(long long int x, int pt, long long int n, int k) {
    if (x <= 1 || primes[pt] > x)
        return 0;
    int id = x <= lim ? indx[x].first : indx[n / x].second;
    long long int ret = 0;
    ret -= g[id][0] - pt;
    ret += g[id][1] - (pt == 0 ? 0 : pfx[pt - 1]);
    ret = (ret % mod + mod) % mod;

    for (int i = pt; i < primesPt && 1ll * primes[i] * primes[i] <= x; i++) {
        long long int pk = primes[i], pk1 = 1ll * primes[i] * primes[i];
        for (int e = 1; pk1 <= x; pk = pk1, pk1 *= primes[i], e++)
            ret = (ret + f(primes[i], e, k) * sieve(x / pk, i + 1, n, k) % mod + f(primes[i], e + 1, k)) % mod;
    }

    return (ret + mod) % mod;
}

long long int min25(long long int n, int k) {
    lim = sqrt(n); init(k); initPrimes(lim + 1, k); int dscPt = 0;
    for (long long int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l); long long int v = n / l; dsc[dscPt] = v;
        g[dscPt][0] = dsc[dscPt] - 1;
        g[dscPt][1] = lagrangeCons(dsc[dscPt], k + 1, val) - 1;
        v <= lim ? indx[v].first = dscPt : indx[n / v].second = dscPt; dscPt++;
    }

    for (int i = 0; i < primesPt && primes[i] <= lim; i++) {
        for (int j = 0; j < dscPt && 1ll * primes[i] * primes[i] <= dsc[j]; j++) {
            long long int v = dsc[j] / primes[i];
            int id = v <= lim ? indx[v].first : indx[n / v].second;
            g[j][0] -= (g[id][0] - i) % mod;
            g[j][0] = (g[j][0] + mod) % mod;
            g[j][1] -= fastPow(primes[i], k, mod) * (g[id][1] - (i == 0 ? 0 : pfx[i - 1])) % mod;
            g[j][1] = (g[j][1] + mod) % mod;
        }
    }

    return (sieve(n, 0, n, k) + 1) % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, k; cin >> n >> k;
    cout << min25(n, k) << '\n';
   
    return 0;
}
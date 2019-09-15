#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010
#define P_SIZE 4700000
#define LAG_SIZE 110

const int mod = 1e9 + 7;

long long int val[LAG_SIZE], pre[LAG_SIZE], suf[LAG_SIZE], rem[LAG_SIZE];
long long int factorials[LAG_SIZE], invFactorials[LAG_SIZE], inv2, inv3;
long long int g[SIZE], pfx[SIZE], dsc[SIZE];
pair<int, int> indx[SIZE];

int primes[P_SIZE], minFac[P_SIZE], phi[P_SIZE], i2PhiPfx[P_SIZE], primesPt, lim;

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod; n >>= 1;
    }
    return ret;
}

void initPrimes() {
    inv2 = fastPow(2, mod - 2, mod); inv3 = fastPow(3, mod - 2, mod);
    primesPt = 0; phi[1] = 1;
    for (int i = 2; i < P_SIZE; i++) {
        if (minFac[i] == 0)
            minFac[i] = i, phi[i] = i - 1, primes[primesPt++] = i;
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (P_SIZE - 1) / i); j++) {
            minFac[i * primes[j]] = primes[j];
            if (minFac[i] == primes[j])
                phi[i * primes[j]] = phi[i] * primes[j];
            else
                phi[i * primes[j]] = phi[i] * (primes[j] - 1);
        }
    }

    i2PhiPfx[0] = 0;
    for (int i = 1; i < P_SIZE; i++)
        i2PhiPfx[i] = (i2PhiPfx[i - 1] + 1ll * i * i % mod * phi[i] % mod) % mod;
}

void initPfx(int siz, int k) {
    pfx[0] = fastPow(primes[0], k, mod);
    for (int i = 1; i < primesPt && primes[i] <= siz; i++)
        pfx[i] = (pfx[i - 1] + fastPow(primes[i], k, mod)) % mod;
}

void initFactorials() {
    factorials[0] = 1;
    for (int i = 1; i < LAG_SIZE; i++)
        factorials[i] = (factorials[i - 1] * i) % mod;
}

void initInvFactorials() {
    invFactorials[LAG_SIZE - 1] = fastPow(factorials[LAG_SIZE - 1], mod - 2, mod);
    for (int i = LAG_SIZE - 2; i >= 0; i--) {
        invFactorials[i] = invFactorials[i + 1] * (i + 1) % mod;
    }
}

void init(int k) {
    initFactorials(); initInvFactorials();
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

void initMin25(long long int n, int k) {
    lim = sqrt(n); initPfx(lim + 1, k + 1); int dscPt = 0;
    for (long long int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l); long long int v = n / l; dsc[dscPt] = v;
        g[dscPt] = lagrangeCons(dsc[dscPt], k + 2, val) - 1;
        v <= lim ? indx[v].first = dscPt : indx[n / v].second = dscPt; dscPt++;
    }

    for (int i = 0; i < primesPt && primes[i] <= lim; i++) {
        for (int j = 0; j < dscPt && 1ll * primes[i] * primes[i] <= dsc[j]; j++) {
            long long int v = dsc[j] / primes[i];
            int id = v <= lim ? indx[v].first : indx[n / v].second;
            g[j] -= fastPow(primes[i], k + 1, mod) * (g[id] - (i == 0 ? 0 : pfx[i - 1])) % mod;
            g[j] = (g[j] + mod) % mod;
        }
    }
}

unordered_map<long long int, long long int> mp;
long long int getI2PhiPfx(long long int n) {
    if (n < P_SIZE) 
        return i2PhiPfx[n];
    if (mp.find(n) != mp.end())
        return mp[n];

    const auto sum2 = [](long long int num) {
        num %= mod;
        return num * (num + 1) % mod * inv2 % mod * ((num << 1) + 1) % mod * inv3 % mod;
    };
    const auto sum3 = [](long long int num) {
        num %= mod;
        long long int ret = num * (num + 1) % mod * inv2 % mod;
        return ret * ret % mod;
    };

    long long int ret = sum3(n);
    for (long long int l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ret = (ret - (sum2(r) - sum2(l - 1)) * getI2PhiPfx(n / l) % mod) % mod;
    }

    ret = (ret + mod) % mod; mp[n] = ret;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initPrimes();
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        long long int n, ans = 0; int k; cin >> n >> k;
        init(k + 1); initMin25(n, k);
        for (long long int l = 2, r; l <= n; l = r + 1) {
            r = n / (n / l);
            const auto id = [n](long long int v) {
                return v <= lim ? indx[v].first : indx[n / v].second;
            };
            ans = (ans + (g[id(r)] - g[id(l - 1)]) * getI2PhiPfx(n / l) % mod + mod) % mod;
        }
        cout << ans << '\n';
    }

    return 0;
}
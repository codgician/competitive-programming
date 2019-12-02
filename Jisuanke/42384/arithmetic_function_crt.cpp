#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

int csts[2], mods[2] = {643, 93257};
int minFac[SIZE], primes[SIZE], mu[SIZE], primesPt;
int pfx[SIZE], ppfx[SIZE];

void initMu() {
    memset(minFac, 0, sizeof(minFac));
    mu[1] = 1; primesPt = 0;
    for (int i = 2; i < SIZE; i++) {
        if (minFac[i] == 0) {
            mu[i] = -1;
            minFac[i] = i, primes[primesPt++] = i;
        }
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (SIZE - 1) / i); j++) {
            minFac[i * primes[j]] = primes[j];
            mu[i * primes[j]] = minFac[i] == primes[j] ? 0 : -mu[i];
        }
    }
}

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = a * a % mod; n >>= 1;
    }
    return ret;
}

long long int crt() {
    long long int ret = 0, mod = mods[0] * mods[1];
    for (int i = 0; i < 2; i++)
        ret = (ret + 1ll * csts[i] * mods[i ^ 1] % mod * fastPow(mods[i ^ 1], mods[i] - 2, mods[i]) % mod) % mod;
    return ret;  
}

void initPfx(int n, int len, int k, int mod) {
    const auto fastMod = [mod](long long int n) {
        return n >= mod ? n - mod : n < 0 ? n + mod : n;
    };
    pfx[0] = 0; ppfx[0] = 0; n = 1ll * n * k % (mod - 1);
    for (int i = 1; i <= len; i++) {
        pfx[i] = fastMod(pfx[i - 1] + mu[i] * fastPow(i, n, mod));
        ppfx[i] = fastMod(ppfx[i - 1] + fastPow(i, k, mod));
    }
}

long long int solve(const string & s, int m, int d, int k, int mod) {
    long long int n = 0; k %= mod - 1;
    for (const auto & ch : s)
        n = (n * 10 + ch - '0') % (mod - 1);
    
    initPfx(n, m / d, k, mod);
    long long int ans = 0; int lim = m / d;
    for (int l = 1, r; l <= lim; l = r + 1) {
        r = lim / (lim / l); int v = lim / l;
        ans = (ans + 1ll * (pfx[r] - pfx[l - 1]) * fastPow(ppfx[v], n, mod)) % mod;
    }
    return ans * fastPow(d, n * k % (mod - 1), mod) % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    initMu();
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        string s; long long int m, d, k;
        cin >> s >> m >> d >> k;
        for (int i = 0; i < 2; i++)
            csts[i] = (solve(s, m, d, k, mods[i]) + mods[i]) % mods[i];
        cout << crt() << '\n';
    }

    return 0;
}

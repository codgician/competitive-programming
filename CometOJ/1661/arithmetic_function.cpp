#include <bits/stdc++.h>
using namespace std;

#define SIZE 5000010
const int mod = 998244353;

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = ret * a % mod;
        a = a * a % mod; n >>= 1;
    }
    return ret;
}

int minFac[SIZE], primes[SIZE], phi[SIZE], mu[SIZE], mert[SIZE], primesPt, inv2;
long long int pfxPhi[SIZE];
void init() {
    memset(minFac, 0, sizeof(minFac)); primesPt = 0; 
    phi[1] = 1; mu[1] = 1;
    for (int i = 2; i < SIZE; i++) {
        if (minFac[i] == 0) {
            phi[i] = i - 1; mu[i] = -1;
            minFac[i] = i, primes[primesPt++] = i;
        }
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (SIZE - 1) / i); j++) {
            minFac[i * primes[j]] = primes[j];
            if (minFac[i] == primes[j]) {
                phi[i * primes[j]] = phi[i] * primes[j];
                mu[i * primes[j]] = 0;
            } else {
                phi[i * primes[j]] = phi[i] * (primes[j] - 1);
                mu[i * primes[j]] = -mu[i];
            }
        }
    }
    pfxPhi[0] = 0; mert[0] = 0;
    for (int i = 1; i < SIZE; i++) {
        pfxPhi[i] = (pfxPhi[i - 1] + phi[i]) % mod;
        mert[i] = (mert[i - 1] + mu[i]) % mod;
    }
}

unordered_map<long long int, int> mp1, mp2;
long long int sievePfxPhi(long long int n) {
    if (n < SIZE)
        return pfxPhi[n];
    if (mp1.find(n) != mp1.end())
        return mp1[n];
    
    long long int ret = n % mod * (n + 1) % mod * inv2 % mod;
    for (long long int l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l); long long int v = n / l;
        ret = (ret - (r - l + 1) * sievePfxPhi(v)) % mod;
    }
    mp1[n] = ret; return ret;
}

long long int sieveMert(long long int n) {
    if (n < SIZE)
        return mert[n];
    if (mp2.find(n) != mp2.end())
        return mp2[n];
    long long int ret = 1;
    for (long long int l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l); long long int v = n / l;
        ret = (ret - (r - l + 1) * sieveMert(v)) % mod;
    }
    mp2[n] = ret; return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    init(); inv2 = fastPow(2, mod - 2, mod);
    long long int n, ans = 0; cin >> n;
    for (long long int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l); long long int v = n / l;
        ans = (ans + (sieveMert(r) - sieveMert(l - 1)) * (2 * sievePfxPhi(v) - 1)) % mod;
    }
    cout << (ans + mod) % mod << '\n';
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define SIZE 90010

unsigned int primes[SIZE], primesk[SIZE], minFac[SIZE], primesPt, lim;
unsigned int g[SIZE], dsc[SIZE];
pair<unsigned int, unsigned int> indx[SIZE];  // indx[x]: index of <x, n / x>

unsigned int fastPow(unsigned int a, unsigned int n) {
    unsigned int ret = 1;
    while (n > 0) {
        if (n & 1)
            ret *= a;
        a *= a; n >>= 1;
    }
    return ret;
}

void initPrimes(unsigned int siz, unsigned int k) {
    fill(minFac + 0, minFac + siz + 1, 0); primesPt = 0;
    for (unsigned int i = 2; i <= siz; i++) {
        if (minFac[i] == 0)
            minFac[i] = i, primes[primesPt++] = i;
        for (unsigned int j = 0; j < primesPt && primes[j] <= min(minFac[i], siz / i); j++)
            minFac[i * primes[j]] = primes[j];
    }
    for (unsigned int i = 0; i < primesPt; i++)
        primesk[i] = fastPow(primes[i], k);
}

unordered_map<unsigned long long int, unsigned int> smp;
unsigned int sieve(unsigned int x, unsigned int pt, unsigned int n, unsigned int k) {
    if (x <= 1 || pt >= primesPt || primes[pt] > x)
        return 0;

    const auto id = [n](unsigned int x) {
        return x <= lim ? indx[x].first : indx[n / x].second;
    };

    const auto p2ll = [x, pt, id]() -> unsigned long long int {
        return 1ull * id(x) * primesPt + pt;
    };

    if (smp.find(p2ll()) != smp.end())
        return smp[p2ll()];
    
    unsigned int ret = 0;
    for (unsigned int i = pt; i < primesPt && 1ll * primes[i] * primes[i] <= x; i++) {
        long long int pk = primes[i], pk1 = 1ll * primes[i] * primes[i];
        for (unsigned int e = 1; pk1 <= x; pk = pk1, pk1 *= primes[i], e++) {
            ret += sieve(x / pk, i + 1, n, k) + primesk[i];
            ret += primesk[i] * (g[id(x / pk)] - i - 1);
        }
    }

    smp[p2ll()] = ret;
    return ret;
}

void initMin25(unsigned int n, unsigned int k) {
    lim = sqrt(n); initPrimes(lim, k); unsigned int dscPt = 0;
    for (unsigned int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l); unsigned int v = n / l; dsc[dscPt] = v;
        g[dscPt] = dsc[dscPt] - 1;
        v <= lim ? indx[v].first = dscPt : indx[n / v].second = dscPt; dscPt++;
    }

    for (unsigned int i = 0; i < primesPt && primes[i] <= lim; i++) {
        for (unsigned int j = 0; j < dscPt && 1ll * primes[i] * primes[i] <= dsc[j]; j++) {
            unsigned int v = dsc[j] / primes[i];
            unsigned int id = v <= lim ? indx[v].first : indx[n / v].second;
            g[j] -= g[id] - i;
        }
    }
}

long long int mp[SIZE];
unsigned int solve(unsigned int x, unsigned int k, unsigned int n) {
    if (x <= 1)
        return 0;
    const auto id = [n](unsigned int x) {
        return x <= lim ? indx[x].first : indx[n / x].second;
    };

    if (mp[id(x)] != -1)
        return mp[id(x)];

    unsigned int ret = sieve(x, 0, n, k) + g[id(x)];
    for (unsigned int l = 2, r; l <= x; l = r + 1) {
        r = x / (x / l);
        ret -= (r - l + 1) * solve(x / l, k, n);
    }
    mp[id(x)] = ret;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    fill(mp + 0, mp + SIZE, -1);
    unsigned int n, k, ret = 0, prev = 0; cin >> n >> k; initMin25(n, k);
    for (unsigned int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l); unsigned int cnt = solve(r, k, n);
        ret += (cnt - prev) * (n / l) * (n / l); prev = cnt;
    }
    cout << ret << '\n';

    return 0;
}
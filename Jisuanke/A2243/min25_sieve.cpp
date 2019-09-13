#include <bits/stdc++.h>
using namespace std;

#define SIZE 150010
#define EXP_SIZE 4

unsigned int primes[SIZE], minFac[SIZE], pfx[SIZE][EXP_SIZE], primesPt, lim;
unsigned int g[SIZE][EXP_SIZE], dsc[SIZE];
pair<unsigned int, unsigned int> indx[SIZE], csts[EXP_SIZE];  // indx[x]: index of <x, n / x>

unsigned int fastPow(unsigned int a, unsigned int n) {
    unsigned int ret = 1;
    while (n > 0) {
        if (n & 1)
            ret *= a;
        a *= a; n >>= 1;
    }
    return ret;
}

void initPrimes(unsigned int siz) {
    fill(minFac + 0, minFac + siz + 1, 0); primesPt = 0;
    for (unsigned int i = 2; i <= siz; i++) {
        if (minFac[i] == 0)
            minFac[i] = i, primes[primesPt++] = i;
        for (unsigned int j = 0; j < primesPt && primes[j] <= min(minFac[i], siz / i); j++)
            minFac[i * primes[j]] = primes[j];
    }

    for (unsigned int e = 0; e < EXP_SIZE; e++)
        pfx[0][e] = fastPow(primes[0], csts[e].second);
    for (unsigned int i = 1; i < primesPt; i++)
        for (unsigned int e = 0; e < EXP_SIZE; e++)
            pfx[i][e] = pfx[i - 1][e] + fastPow(primes[i], csts[e].second);
}

const auto f = [](unsigned int p, int e) {
    unsigned int ret = 0;
    for (int e = 0; e < EXP_SIZE; e++)
        ret += csts[e].first * fastPow(p, csts[e].second);
    return e * ret;
};

const auto sum = [](unsigned int n, unsigned int exp) -> unsigned int {
    if (exp == 0)
        return n;
    unsigned long long int ret = (n & 1) ? 1ull * ((n + 1) >> 1) * n : 1ull * (n >> 1) * (n + 1);
    if (exp == 1)
        return ret;
    if (exp == 2)
        return (ret % 3 == 0) ? (ret / 3) * ((n << 1) + 1) : ((n << 1) + 1) / 3 * ret;
    return ret * ret;
};

pair<unsigned int, unsigned int> sieve(unsigned int x, unsigned int pt, unsigned int n) {
    if (x <= 1 || primes[pt] > x)
        return make_pair(0, 0);
    int k = x <= lim ? indx[x].first : indx[n / x].second;
    pair<unsigned int, unsigned int> ret = make_pair(0, 0);
    ret.second = g[k][3] - pt;
    for (int e = 0; e < EXP_SIZE; e++)
        ret.first += csts[e].first * (g[k][e] - (pt == 0 ? 0 : pfx[pt - 1][e]));

    for (unsigned int i = pt; i < primesPt && primes[i] * primes[i] <= x; i++) {
        long long int pk = primes[i], pk1 = 1ll * primes[i] * primes[i];
        for (int e = 1; pk1 <= x; pk = pk1, pk1 *= primes[i], e++) {
            auto qaq = sieve(x / pk, i + 1, n);
            ret.second += qaq.second + 1; 
            ret.first += qaq.first + qaq.second * f(primes[i], e) + f(primes[i], e + 1);
        }
    }

    return ret;
}

pair<unsigned int, unsigned int> min25(unsigned int n) {
    lim = sqrt(n); initPrimes(lim + 1); int dscPt = 0;
    for (unsigned int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l); unsigned int v = n / l; dsc[dscPt] = v;
        for (int e = 0; e < EXP_SIZE; e++)
            g[dscPt][e] = sum(dsc[dscPt], csts[e].second) - 1;
        v <= lim ? indx[v].first = dscPt : indx[n / v].second = dscPt; dscPt++;
    }

    for (unsigned int i = 0; i < primesPt && primes[i] <= lim; i++) {
        for (int j = 0; j < dscPt && 1ll * primes[i] * primes[i] <= dsc[j]; j++) {
            unsigned int v = dsc[j] / primes[i];
            int k = v <= lim ? indx[v].first : indx[n / v].second;
            for (int e = 0; e < EXP_SIZE; e++)
                g[j][e] -= fastPow(primes[i], csts[e].second) * (g[k][e] - (i == 0 ? 0 : pfx[i - 1][e]));
        }
    }

    return sieve(n, 0, n);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    unsigned int num; cin >> num;
    for (int i = 0; i < EXP_SIZE; i++) {
        cin >> csts[i].first;
        csts[i].second = 3 - i;
    }
    
    cout << min25(num).first << '\n';

    return 0;
}
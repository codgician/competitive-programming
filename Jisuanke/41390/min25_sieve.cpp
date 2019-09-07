#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

const int mod = 998244353;

int primes[SIZE], minFac[SIZE], primesPt, lim;
long long int g[SIZE][EXP_SIZE], dsc[SIZE], pfx[SIZE];
pair<int, int> indx[SIZE];  // indx[x]: index of <x, n / x>

void initPrimes(int siz) {
    fill(minFac + 0, minFac + siz + 1, 0); primesPt = 0;
    for (int i = 2; i <= siz; i++) {
        if (minFac[i] == 0)
            minFac[i] = i, primes[primesPt++] = i;
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], siz / i); j++)
            minFac[i * primes[j]] = primes[j];
    }

    pfx[0] = primes[0];
    for (int i = 1; i < primesPt; i++)
        pfx[i] = (pfx[i - 1] + primes[i]) % mod;
}

class Node {
public:
    long long int s0, s1, sf, sh;
};

const auto f = [](long long int p, int e) {
    return e;
};

const auto h = [](long long int pe, int e) {
    return pe % mod * e % mod;
};

const auto sum = [](long long int n, int exp) {
    n %= mod;
    return exp == 0 ? n : (n & 1) ? ((n + 1) >> 1) * n % mod : (n >> 1) * (n + 1) % mod;
};

Node sieve(long long int x, int pt, long long int n) {
    if (x <= 1 || primes[pt] > x)
        return Node{0, 0, 0, 0};

    const auto id = [n](long long int x) {
        return x <= lim ? indx[x].first : indx[n / x].second;
    };

    Node ret;
    ret.s0 = g[id(x)][0] - pt; ret.sf = ret.s0;
    ret.s1 = g[id(x)][1] - (pt == 0 ? 0 : pfx[pt - 1]); ret.sh = ret.s1;

    for (int i = pt; i < primesPt && 1ll * primes[i] * primes[i] <= x; i++) {
        long long int pk = primes[i], pk1 = 1ll * primes[i] * primes[i];
        for (int e = 1; pk1 <= x; pk = pk1, pk1 *= primes[i], e++) {
            Node q = sieve(x / pk, i + 1, n);
            ret.s0 = (ret.s0 + q.s0 + 1) % mod;
            ret.s1 = (ret.s1 + pk % mod * q.s1 % mod + pk1 % mod) % mod;
            ret.sf = (ret.sf + q.sf + f(primes[i], e) * q.s0 % mod + f(primes[i], e + 1)) % mod;
            ret.sh = (ret.sh + q.sh * pk % mod + h(pk, e) * q.s1 % mod + h(pk1, e + 1)) % mod;
        }
    }

    return ret;
}

void initMin25(long long int n) {
    lim = sqrt(n); initPrimes(lim + 1); int dscPt = 0;
    for (long long int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l); long long int v = n / l; dsc[dscPt] = v;
        g[dscPt][0] = sum(dsc[dscPt], 0) - 1;
        g[dscPt][1] = sum(dsc[dscPt], 1) - 1;
        v <= lim ? indx[v].first = dscPt : indx[n / v].second = dscPt; dscPt++;
    }

    for (int i = 0; i < primesPt && primes[i] <= lim; i++) {
        for (int j = 0; j < dscPt && 1ll * primes[i] * primes[i] <= dsc[j]; j++) {
            long long int v = dsc[j] / primes[i];
            int k = v <= lim ? indx[v].first : indx[n / v].second;
            g[j][0] = (g[j][0] - (g[k][0] - i)) % mod;
            g[j][1] = (g[j][1] - primes[i] * (g[k][1] - (i == 0 ? 0 : pfx[i - 1]))) % mod;    
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    long long int n; cin >> n;
    initMin25(n); Node ret = sieve(n, 0, n);
    cout << ((n + 1) % mod * ret.sf % mod - ret.sh + mod) % mod << '\n';

    return 0;
}
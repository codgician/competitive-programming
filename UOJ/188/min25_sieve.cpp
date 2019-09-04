#include <bits/stdc++.h>
using namespace std;

#define SIZE 1000010

int primes[SIZE], minFac[SIZE], primesPt, lim;
long long int g[SIZE], dsc[SIZE];
pair<int, int> indx[SIZE];  // indx[x]: index of <x, n / x>

void initPrimes(int siz) {
    fill(minFac + 0, minFac + siz + 1, 0); primesPt = 0;
    for (int i = 2; i <= siz; i++) {
        if (minFac[i] == 0)
            minFac[i] = i, primes[primesPt++] = i;
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], siz / i); j++)
            minFac[i * primes[j]] = primes[j];
    }
}

long long int sieve(long long int x, long long int pt, long long int n) {
    if (x <= 1 || primes[pt] > x)
        return 0;

    const auto id = [n](long long int x) {
        return x <= lim ? indx[x].first : indx[n / x].second;
    };

    long long int ret = 0;
    for (int i = pt; i < primesPt && 1ll * primes[i] * primes[i] <= x; i++) {
        long long int pk = primes[i], pk1 = 1ll * primes[i] * primes[i];
        for (int e = 1; pk1 <= x; pk = pk1, pk1 *= primes[i], e++) {
            ret += sieve(x / pk, i + 1, n) + primes[i];
            ret += primes[i] * (g[id(x / pk)] - i - 1);
        }
    }

    return ret;
}

long long int min25(long long int n) {
    lim = sqrt(n); int dscPt = 0;
    for (long long int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l); long long int v = n / l; dsc[dscPt] = v;
        g[dscPt] = dsc[dscPt] - 1;
        v <= lim ? indx[v].first = dscPt : indx[n / v].second = dscPt; dscPt++;
    }

    for (int i = 0; i < primesPt && primes[i] <= lim; i++) {
        for (int j = 0; j < dscPt && 1ll * primes[i] * primes[i] <= dsc[j]; j++) {
            long long int v = dsc[j] / primes[i];
            int k = v <= lim ? indx[v].first : indx[n / v].second;
            g[j] -= g[k] - i;
        }
    }
    return sieve(n, 0, n);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    long long int qLeftPt, qRightPt; cin >> qLeftPt >> qRightPt;
    initPrimes(sqrt(qRightPt)); 
    cout << min25(qRightPt) - min25(qLeftPt - 1) << '\n';

    return 0;
}
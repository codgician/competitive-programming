#include <bits/stdc++.h>
using namespace std;

#define SIZE 700010

int primes[SIZE], minFac[SIZE], primesPt, lim;
long long int g[SIZE], dsc[SIZE];
pair<int, int> indx[SIZE];

void initPrimes() {
    fill(minFac + 0, minFac + SIZE, 0); primesPt = 0;
    for (int i = 2; i < SIZE; i++) {
        if (minFac[i] == 0) {
            minFac[i] = i, primes[primesPt++] = i;
        }
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (SIZE - 1) / i); j++) {
            minFac[i * primes[j]] = primes[j];
        }
    }
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
    return g[0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    long long int num; initPrimes();
    while (cin >> num) 
        cout << min25(num) << '\n';
    return 0;
}
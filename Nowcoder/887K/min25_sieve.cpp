#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 100010
 
int primes[SIZE], minFac[SIZE], primesPt, lim;
long long int pfx[SIZE][2], g[SIZE][2], dsc[SIZE];  // 0: 4k + 1, 1: 4k + 3
pair<int, int> indx[SIZE];  // indx[x]: index of <x, n / x>
 
long long int f(long long int p, int e) {
    return ((p & 3) == 1) ? 3ll * e + 1 : 1ll;
}
 
void initPrimes(int siz) {
    fill(minFac + 0, minFac + siz + 1, 0); primesPt = 0;
    for (int i = 2; i <= siz; i++) {
        if (minFac[i] == 0)
            minFac[i] = i, primes[primesPt++] = i;
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], siz / i); j++)
            minFac[i * primes[j]] = primes[j];
    }
 
    pfx[0][0] = 0; pfx[0][1] = 0;   // Exclude 2
    for (int i = 1; i < primesPt; i++) {
        pfx[i][0] += pfx[i - 1][0]; pfx[i][1] += pfx[i - 1][1];
        pfx[i][(primes[i] & 3) == 3]++;
    }
}
 
long long int sieve(long long int x, long long int pt, long long int n) {
    if (x <= 1 || primes[pt] > x)
        return 0;
    int k = x <= lim ? indx[x].first : indx[n / x].second;
    long long int ret = 4ll * (g[k][0] - (pt == 0 ? 0 : pfx[pt - 1][0])) + (g[k][1] - (pt == 0 ? 0 : pfx[pt - 1][1]));
    if (x > 1 && pt == 0) // Consider 2
        ret++;
 
    for (int i = pt; i < primesPt && 1ll * primes[i] * primes[i] <= x; i++) {
        long long int pk = primes[i], pk1 = 1ll * primes[i] * primes[i];
        for (int e = 1; pk1 <= x; pk = pk1, pk1 *= primes[i], e++)
            ret = (ret + f(primes[i], e) * sieve(x / pk, i + 1, n) + f(primes[i], e + 1));
    }
 
    return ret;
}
 
long long int min25(long long int n) {
    lim = sqrt(n); int dscPt = 0;
    for (long long int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l); long long int v = n / l; dsc[dscPt] = v;
        g[dscPt][0] = (dsc[dscPt] >> 2) + ((dsc[dscPt] & 3) >= 1) - 1;  // Exclude 1
        g[dscPt][1] = (dsc[dscPt] >> 2) + ((dsc[dscPt] & 3) >= 3);
        v <= lim ? indx[v].first = dscPt : indx[n / v].second = dscPt; dscPt++;
    }
 
    for (int i = 1; i < primesPt && primes[i] <= lim; i++) {    // Exclude 2
        int which = ((primes[i] & 3) == 1);
        for (int j = 0; j < dscPt && 1ll * primes[i] * primes[i] <= dsc[j]; j++) {
            long long int v = dsc[j] / primes[i];
            int k = v <= lim ? indx[v].first : indx[n / v].second;
            g[j][0] -= g[k][which ^ 1] - (i == 0 ? 0 : pfx[i - 1][which ^ 1]);
            g[j][1] -= g[k][which] - (i == 0 ? 0 : pfx[i - 1][which]);
        }
    }
 
    return sieve(n, 0, n) + 1;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initPrimes(SIZE);
 
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        long long int num; cin >> num;
        cout << min25(num) << '\n';
    }
 
    return 0;
}

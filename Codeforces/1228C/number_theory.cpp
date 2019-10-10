#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 50010
const int mod = 1e9 + 7;
 
int primes[SIZE], minFac[SIZE], primesPt;
void initPrimes() {
    memset(minFac, 0, sizeof(minFac)); primesPt = 0;
    for (int i = 2; i < SIZE; i++) {
        if (minFac[i] == 0) {
            minFac[i] = i;
            primes[primesPt++] = i;
        }
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (SIZE - 1) / i); j++) {
            minFac[i * primes[j]] = primes[j];
        }
    }
}
 
long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod; n >>= 1;
    }
    return ret;
}
 
vector<int> facs;
 
void factorlize(long long int n) {
    facs.clear();
    for (int i = 0; i < primesPt && 1ll * primes[i] * primes[i] <= n; i++) {
        if (n % primes[i] != 0)
            continue;
        n /= primes[i];
        while (n % primes[i] == 0)
            n /= primes[i];
        facs.push_back(primes[i]);
    }
    if (n > 1)
        facs.push_back(n);
}
 
long long int calc(long long int n, long long int p) {
    if (n < p)
        return 0;
    return n / p + calc(n / p, p);
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initPrimes();
 
    long long int x, n, ans = 1; cin >> x >> n;
    factorlize(x);
 
    for (const auto & p : facs)
        ans = ans * fastPow(p, calc(n, p), mod) % mod;
    cout << ans << '\n';
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define SIZE 2000010

int minFac[SIZE], primes[SIZE], mu[SIZE], primesPt;
long long int mert[SIZE];

void initMu() {
    memset(minFac, 0, sizeof(minFac));
    primesPt = 0; mu[1] = 1;
    for (int i = 2; i < SIZE; i++) {
        if (minFac[i] == 0) {
            minFac[i] = i; mu[i] = -1;
            primes[primesPt++] = i;
        }
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (SIZE - 1) / i); j++) {
            minFac[i * primes[j]] = primes[j];
            if (minFac[i] == primes[j]) {
                mu[i * primes[j]] = 0;
            } else {
                mu[i * primes[j]] = -mu[i];
            }
        }
    }
    mert[0] = 0;
    for (int i = 1; i < SIZE; i++)
        mert[i] = mert[i - 1] + mu[i];
}

int getMu(long long int num) {
    if (num < SIZE)
        return mu[num];
    int ret = 1;
    for (int i = 2; 1ll * i * i <= num; i++) {
        if (num % i != 0)
            continue;
        if (num % (1ll * i * i) == 0)
            return 0;
        ret *= -1, num /= i;
    }
    if (num > 1)
        ret *= -1;
    return ret;
}

unordered_map<long long int, long long int> mp;
long long int getMert(long long int n) {
    if (n < SIZE)
        return mert[n];
    if (mp.find(n) != mp.end())
        return mp[n];
    long long int ret = 1;
    for (long long int l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ret -= getMert(n / l) * (r - l + 1);
    }
    mp[n] = ret;
    return ret;
}

long long int solve(long long int n, long long int m) {
    if (m == 0)
        return 0;
    if (n == 1)
        return getMert(m);
    long long int ret = 0; int cntMu = getMu(n);
    if (cntMu == 0)
        return 0;
    for (int d = 1; d <= m && 1ll * d * d <= n; d++) {
        if (n % d != 0)
            continue;
        ret += getMu(d) * solve(d, m / d);
        if (1ll * d * d != n && n / d <= m)
            ret += getMu(n / d) * solve(n / d, m / (n / d));
    }
    return cntMu * ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initMu(); long long int m, n; cin >> m >> n;
    cout << solve(n, m) << '\n';
    return 0;
}
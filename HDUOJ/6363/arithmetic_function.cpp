#include <bits/stdc++.h>
using namespace std;

#define SIZE 2000010
const int mod = 1e9 + 7;

long long int factorials[SIZE], invFactorials[SIZE];
long long int fibo[SIZE];

int minFac[SIZE], primes[SIZE], mu[SIZE], primesPt;

void initMu() {
    memset(minFac, 0, sizeof(minFac));
    primesPt = 0, mu[1] = 1;
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
            ret = ret * a % mod;
        a = a * a % mod; n >>= 1;
    }
    return ret;
}

void initFactorials() {
    factorials[0] = 1;
    for (int i = 1; i < SIZE; i++)
        factorials[i] = factorials[i - 1] * i % mod;
    invFactorials[SIZE - 1] = fastPow(factorials[SIZE - 1], mod - 2, mod);
    assert(invFactorials[SIZE - 1] != 0);
    for (int i = SIZE - 2; i >= 0; i--)
        invFactorials[i] = invFactorials[i + 1] * (i + 1) % mod;
}

void initFibo() {
    fibo[0] = 0, fibo[1] = 1;
    for (int i = 2; i < SIZE; i++)
        fibo[i] = (fibo[i - 1] + fibo[i - 2]) % (mod - 1);
}

long long int binom(long long int n, long long int m) {
    return m > n ? 0 : factorials[n] * invFactorials[m] % mod * invFactorials[n - m] % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initFactorials(); initFibo(); initMu();
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int n, k; cin >> n >> k;
        vector<int> facs;
        for (int i = 1; i * i <= n; i++) {
            if (n % i != 0)
                continue;
            facs.push_back(i);
            if (i * i != n)
                facs.push_back(n / i);
        }

        sort(facs.begin(), facs.end());
        long long int ret = 0;
        for (const auto & t : facs) {
            long long int cnt = 0;
            for (int i = 0; i < (int)facs.size() && facs[i] <= t; i++)
                if (t % facs[i] == 0)
                    cnt = (cnt + (fastPow(2, fibo[facs[i]], mod) - 1) * mu[t / facs[i]]) % mod;
            ret = (ret + binom(n / t + k - 1, k - 1) * cnt % mod) % mod;
        }

        ret = ret * fastPow(binom(n + k - 1, k - 1), mod - 2, mod) % mod;
        cout << (ret + mod) % mod << '\n';
    }

    return 0;
}
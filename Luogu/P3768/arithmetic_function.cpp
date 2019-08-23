#include <bits/stdc++.h>
using namespace std;

#define SIZE 5000010

int primes[SIZE], minFac[SIZE], primesPt;
int phi[SIZE], mod;
long long int pfx[SIZE], twoInv, sixInv;

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod; n >>= 1;
    }
    return ret;
}

void init() {
    memset(minFac, 0, sizeof(minFac));
    primesPt = 0; phi[1] = 1;
    for (int i = 2; i < SIZE; i++) {
        if (minFac[i] == 0) {
            minFac[i] = i;
            phi[i] = i - 1;
            primes[primesPt++] = i;
        }
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (SIZE - 1) / i); j++) {
            minFac[i * primes[j]] = primes[j];
            if (minFac[i] == primes[j]) 
                phi[i * primes[j]] = phi[i] * primes[j];
            else
                phi[i * primes[j]] = phi[i] * (primes[j] - 1);
        }
    }

    pfx[0] = 0;
    for (int i = 1; i < SIZE; i++)
        pfx[i] = (pfx[i - 1] + 1ll * i * i % mod * phi[i] % mod) % mod;

    twoInv = fastPow(2, mod - 2, mod);
    sixInv = fastPow(6, mod - 2, mod);
}

unordered_map<int, long long int> pfxMp;

auto sum = [](long long int n) -> long long int {
    n %= mod;
    return n * (n + 1) % mod * twoInv % mod;
};

auto squareSum = [](long long int n) -> long long int {
    n %= mod;
    return n * (n + 1) % mod * (2 * n + 1) % mod * sixInv % mod; 
};

auto cubicSum = [](long long int n) -> long long int {
    n %= mod;
    long long int ret = sum(n);
    return ret * ret % mod;
};

long long int solve(long long int n) {
    if (n < SIZE)
        return pfx[n];
    if (pfxMp.find(n) != pfxMp.end())
        return pfxMp[n];

    long long int ret = cubicSum(n);
    for (long long int l = 2, r; l <= n; l = r + 1) {
        if (n / l == 0)
            break;
        r = n / (n / l);
        ret = (ret - (squareSum(r) - squareSum(l - 1)) * solve(n / l) % mod + mod) % mod;
    }

    pfxMp[n] = ret;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    long long int n; cin >> mod >> n;
    init();

    long long int ans = 0;
    for (long long int l = 1, r; l <= n; l = r + 1) {
        if (n / l == 0)
            break;
        r = n / (n / l);
        ans = (ans + (solve(r) - solve(l - 1)) * cubicSum(n / l) % mod + mod) % mod;
    }

    cout << ans << '\n';
    return 0;
}
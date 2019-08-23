#include <bits/stdc++.h>
using namespace std;

#define SIZE 3000010

const int mod = 1e9 + 7;

int primes[SIZE], minFac[SIZE], primesPt;
int phi[SIZE]; long long int pfx[SIZE], inv2, inv6;

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
    inv2 = fastPow(2, mod - 2, mod);
    inv6 = fastPow(6, mod - 2, mod);

    memset(minFac, 0, sizeof(minFac));
    primesPt = 0; phi[1] = 1;
    for (int i = 2; i < SIZE; i++) {
        if (minFac[i] == 0) {
            minFac[i] = i; phi[i] = i - 1;
            primes[primesPt++] = i;
        }
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (SIZE - 1) / i); j++) {
            minFac[i * primes[j]] = primes[j];
            if (minFac[i] == primes[j]) {
                phi[i * primes[j]] = phi[i] * primes[j];
            } else {
                phi[i * primes[j]] = phi[i] * (primes[j] - 1);
            }
        }
    }

    pfx[0] = 0;
    for (int i = 1; i < SIZE; i++)
        pfx[i] = (pfx[i - 1] + 1ll * i * phi[i] % mod) % mod;
}

unordered_map<int, long long int> pfxMp;

// sum i * phi(i)
long long int getPfx(int n) {
    if (n < SIZE)
        return pfx[n];
    if (pfxMp.find(n) != pfxMp.end())
        return pfxMp[n];

    const auto sqrSum = [](long long int len) {
        return len * (len + 1) % mod * ((len << 1) + 1) % mod * inv6 % mod;
    };
    const auto sum = [](long long int len) {
        return len * (len + 1) % mod * inv2 % mod;
    };

    long long int ret = sqrSum(n);
    for (long long int l = 2, r; l <= n; l = r + 1) {
        if (n / l == 0)
            break;
        r = n / (n / l);
        ret = (ret - (sum(r) - sum(l - 1) + mod) % mod * getPfx(n / l) % mod) % mod;
    }

    pfxMp[n] = ret;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    init(); phi[1] = 0; 
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        long long int n, a, b; cin >> n >> a >> b;
        cout << (getPfx(n) - 1 + mod) % mod * inv2 % mod << '\n';
    }
    return 0;
}   

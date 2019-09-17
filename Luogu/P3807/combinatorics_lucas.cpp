#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

long long int factorials[SIZE], invFactorials[SIZE];

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod; n >>= 1;
    }
    return ret;
}

void initFactorials(int p) {
    factorials[0] = 1;
    for (int i = 1; i < p; i++)
        factorials[i] = factorials[i - 1] * i % p;
    invFactorials[p - 1] = fastPow(factorials[p - 1], p - 2, p);
    for (int i = p - 2; i >= 0; i--)
        invFactorials[i] = invFactorials[i + 1] * (i + 1) % p;
}

long long int lucas(long long int n, long long int m, int p) {
    if (n == 0)
        return 1;
    const auto comb = [p](long long int n, long long int m) {
        return m > n ? 0 : factorials[n] * invFactorials[m] % p * invFactorials[n - m] % p;
    };
    return comb(n % p, m % p) * lucas(n / p, m / p, p) % p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        long long int n, m; int p; cin >> n >> m >> p;
        initFactorials(p); cout << lucas(n + m, m, p) << '\n';
    }
    return 0;
}
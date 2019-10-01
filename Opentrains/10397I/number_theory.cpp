#include <bits/stdc++.h>
using namespace std;

#define SIZE 10000000

int primes[SIZE], minFac[SIZE], primesPt;

void initPrimes() {
    primesPt = 0;
    for (int i = 2; i < SIZE; i++) {
        if (minFac[i] == 0)
            minFac[i] = i, primes[primesPt++] = i;
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (SIZE - 1) / i); j++)
            minFac[i * primes[j]] = primes[j];
    }
}

long long int fastPow(long long int a, long long int n, int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod; n >>= 1;
    }
    return ret;
}

vector<int> facs;

void factorize(int n) {
    facs.clear();
    for (int i = 1; i * i <= n; i++) {
        if (n % i != 0)
            continue;
        facs.push_back(i);
        if (i * i != n)
            facs.push_back(n / i);
    }
    sort(facs.begin(), facs.end());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    vector<int> vec; initPrimes();
    int q, n; cin >> q >> n; factorize(n);

    for (int i = 0; i < primesPt; i++) {
        int p = primes[i]; long long int inv = fastPow(q - 1, p - 2, p);
        long long int cnt = ((fastPow(q, n, p) - 1 + p) % p) * inv % p;
        if (cnt == 0)
            vec.push_back(p);
    }

    int siz = vec.size();
    for (const auto & f : facs) {
        if (f == n) continue;
        for (int i = 0; i < siz; i++) {
            int p = vec[i]; long long int inv = fastPow(q - 1, p - 2, p);
            long long int cnt = ((fastPow(q, f, p) - 1 + p) % p) * inv % p;
            if (cnt == 0) {
                swap(vec[i], vec[vec.size() - 1]); vec.pop_back(); i--; siz--;
                continue;
            }
        }
    }

    sort(vec.begin(), vec.end());
    cout << siz << '\n';
    for (int i = 0; i < siz; i++)
        cout << vec[i] << (i == siz - 1 ? '\n' : ' ');
    return 0;
}
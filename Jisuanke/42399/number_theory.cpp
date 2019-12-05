#include <bits/stdc++.h>
using namespace std;

#define SIZE 4000010

int primes[SIZE], minFac[SIZE], primesPt;
long long int arr[SIZE], ans[SIZE], mod;

void initPrimes() {
    memset(minFac, 0, sizeof(minFac)); primesPt = 0;
    for (int i = 2; i < SIZE; i++) {
        if (minFac[i] == 0)
            minFac[i] = i, primes[primesPt++] = i;
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (SIZE - 1) / i); j++)
            minFac[i * primes[j]] = primes[j];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initPrimes(); int caseNum; cin >> caseNum;
    while (caseNum--) {
        long long int l, r, k, ret = 0;
        cin >> l >> r >> k >> mod;
        for (long long int i = l; i <= r; i++)
            arr[i - l] = i, ans[i - l] = 1;
        for (int i = 0; i < primesPt && 1ll * primes[i] * primes[i] <= r; i++) {
            long long int startPt = l + (primes[i] - l % primes[i]) % primes[i];
            for (long long int j = startPt; j <= r; j += primes[i]) {
                long long int pk = primes[i]; arr[j - l] /= primes[i];
                while (arr[j - l] % primes[i] == 0)
                    arr[j - l] /= primes[i], pk *= primes[i];
                if ((primes[i] & 3) == 3) {
                    ans[j - l] *= (pk + 2 * (pk / primes[i]) + 2 * ((pk / primes[i] - 1) / (primes[i] - 1)));
                } else if ((primes[i] & 3) == 1) {
                    ans[j - l] *= pk;
                }
            }
        }
        for (long long int i = l; i <= r; i++)
            if (arr[i - l] > 2)
                ans[i - l] *= (arr[i - l] + 2 * ((arr[i - l] & 3) == 3));
        for (long long int i = l; i <= r; i++)
            ret = (ret + ((6 * ans[i - l]) ^ k)) % mod;
        cout << ret << '\n';
    }
    return 0;
}

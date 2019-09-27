#include <bits/stdc++.h>
using namespace std;

#define SIZE 1000010

const int mod = 998244353;

int primes[SIZE], minFac[SIZE], primesPt;
long long int arr[SIZE], ans[SIZE];

void initPrimes() {
    fill(minFac + 0, minFac + SIZE, 0); primesPt = 0;
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
    initPrimes();
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        long long int qLeftPt, qRightPt; int k;
        cin >> qLeftPt >> qRightPt >> k;
        for (long long int i = qLeftPt; i <= qRightPt; i++)
            arr[i - qLeftPt] = i, ans[i - qLeftPt] = 1;
        for (int i = 0; i < primesPt && primes[i] <= qRightPt; i++) {
            long long int fst = qLeftPt;
            if (fst % primes[i] != 0)
                fst = qLeftPt + primes[i] - qLeftPt % primes[i];
            for (long long int j = fst; j <= qRightPt; j += primes[i]) {
                arr[j - qLeftPt] /= primes[i]; int exp = 1;
                while (arr[j - qLeftPt] % primes[i] == 0)
                    exp++, arr[j - qLeftPt] /= primes[i];
                ans[j - qLeftPt] = ans[j - qLeftPt] * (k * exp + 1) % mod;
            }
        }

        for (long long int i = qLeftPt; i <= qRightPt; i++)
            if (arr[i - qLeftPt] > 1)
                ans[i - qLeftPt] = ans[i - qLeftPt] * (k + 1) % mod;

        long long int ret = 0;
        for (long long int i = qLeftPt; i <= qRightPt; i++)
            ret = (ret + ans[i - qLeftPt]) % mod;
        cout << ret << '\n';
    }

    return 0;
}
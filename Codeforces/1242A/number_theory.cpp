#include <bits/stdc++.h>
using namespace std;

#define SIZE 1000010

int primes[SIZE], minFac[SIZE], primesPt;
void initPrimes() {
    memset(minFac, 0, sizeof(minFac));
    primesPt = 0;
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

vector<long long int> facs;

void factorize(long long int num) {
    facs.clear();
    for (int i = 0; i < primesPt && 1ll * primes[i] * primes[i] <= num; i++) {
        if (num % primes[i] != 0)
            continue;
        facs.push_back(primes[i]); num /= primes[i];
        while (num % primes[i] == 0)
            num /= primes[i];
    }
    if (num > 1)
        facs.push_back(num);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initPrimes();
    long long int num; cin >> num; 
    if (num == 1) {
        cout << 1 << '\n';
        return 0;
    }
    factorize(num);
    cout << ((int)facs.size() == 1 ? facs.front() : 1) << '\n';
    return 0;
}
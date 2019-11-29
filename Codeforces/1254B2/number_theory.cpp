#include <bits/stdc++.h>
using namespace std;

#define SIZE 1000010

int arr[SIZE];
int primes[SIZE], minFac[SIZE], primesPt;

void initPrimes() {
    memset(minFac, 0, sizeof(minFac)); primesPt = 0;
    for (int i = 2; i < SIZE; i++) {
        if (minFac[i] == 0) {
            minFac[i] = i, primes[primesPt++] = i;
        }
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (SIZE - 1) / i); j++)
            minFac[i * primes[j]] = primes[j];
    }
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    initPrimes(); long long int sum = 0; 
    int len; cin >> len;
    for (int i = 0; i < len; i++)
        cin >> arr[i], sum += arr[i];
    
    if (sum == 0) {
        cout << 0 << '\n';
        return 0;
    }

    if (sum == 1) {
        cout << -1 << '\n';
        return 0;
    }

    vector<long long int> facs;
    const auto factorize = [&facs](long long int n) {
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
    };
    
    factorize(sum); long long int ans = LLONG_MAX;
    for (const auto & p : facs) {
        const auto solve = [p, len]() {
            long long int cnt = 0, ret = 0;
            for (int i = 0; i < len; i++) {
                cnt = (cnt + arr[i]) % p;
                ret += min(cnt, p - cnt);
            }
            return ret;
        };
        ans = min(ans, solve());
    }

    cout << ans << '\n';
    return 0;
}

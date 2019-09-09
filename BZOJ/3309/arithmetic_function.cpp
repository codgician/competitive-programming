#include <bits/stdc++.h>
using namespace std;

#define SIZE 10000010

int primes[SIZE], minFac[SIZE], g[SIZE], primesPt;
pair<int, int> minFacExp[SIZE];

void init() {
    memset(minFac, 0, sizeof(minFac)); primesPt = 0; g[1] = 0;
    for (int i = 2; i < SIZE; i++) {
        if (minFac[i] == 0) {
            minFac[i] = i; minFacExp[i] = make_pair(i, 1); g[i] = 1;
            primes[primesPt++] = i;
        }

        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (SIZE - 1) / i); j++) {
            int val = i * primes[j]; minFac[val] = primes[j];
            if (minFac[i] == primes[j]) {
                minFacExp[val] = make_pair(minFacExp[i].first * primes[j], minFacExp[i].second + 1);
                int rem = i / minFacExp[i].first;
                if (rem == 1)   // i == p ^ e
                    g[val] = 1;
                else
                    g[val] = minFacExp[val].second == minFacExp[rem].second ? -g[rem] : 0;
            } else {
                minFacExp[val] = make_pair(primes[j], 1);
                g[val] = minFacExp[val].second == minFacExp[i].second ? - g[i] : 0;
            }
        }
    }
    for (int i = 2; i < SIZE; i++)
        g[i] += g[i - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    init(); 

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int n, m; long long int ans = 0; cin >> n >> m;
        if (n > m)
            swap(n, m);
        for (int l = 1, r; l <= n; l = r + 1) {
            r = min(n / (n / l), m / (m / l));
            ans += 1ll * (g[r] - g[l - 1]) * (n / l) * (m / l);
        }
        cout << ans << '\n';
    }

    return 0;
}
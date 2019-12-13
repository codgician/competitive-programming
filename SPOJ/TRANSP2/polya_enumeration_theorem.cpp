#include <bits/stdc++.h>
using namespace std;

#define SIZE 2000010
const int mod = 1000003;

int a, b, n, col;
long long int ans;

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = ret * a % mod;
        a = a * a % mod; n >>= 1;
    }
    return ret;
}

int minFac[SIZE], primes[SIZE], phi[SIZE], primesPt;
void initPhi() {
    memset(minFac, 0, sizeof(minFac));
    primesPt = 0; phi[1] = 1;
    for (int i = 2; i < SIZE; i++) {
        if (minFac[i] == 0) {
            phi[i] = i - 1;
            minFac[i] = i, primes[primesPt++] = i;
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
}

vector<pair<int, int> > facs;
void factorize(int num) {
    facs.clear();
    while (num > 1) {
        int p = minFac[num];
        facs.push_back(make_pair(p, 1)); num /= p;
        while (minFac[num] == p)
            num /= p, facs.back().second++;
    }
}

void dfs(const vector<pair<int, int> >::iterator & it, int t) {
    if (it == facs.end()) {
        ans = (ans + phi[n / t] * fastPow(col, t, mod)) % mod;
        return;
    }
    int cnt = 1;
    for (int i = 0; i <= it -> second; i++)
        dfs(next(it), t * cnt), cnt *= it -> first;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    initPhi(); int caseNum; cin >> caseNum;
    while (caseNum--) {
        ans = 0; cin >> a >> b;
        if (a == 0 && b == 0) {
            cout << 0 << '\n';
            continue;
        }
        int gcd = __gcd(a + b, b);
        n = (a + b) / gcd, col = fastPow(2, gcd, mod);
        factorize(n); dfs(facs.begin(), 1);
        ans = ans * fastPow(n, mod - 2, mod) % mod;
        ans = (fastPow(2, a + b, mod) - ans + mod) % mod; 
        cout << ans << '\n'; 
    }

    return 0;
}

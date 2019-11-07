#include <bits/stdc++.h>
using namespace std;

#define SIZE 200
#define P_SIZE 32000

int minFac[P_SIZE], primes[P_SIZE], mu[P_SIZE], primesPt;
void initMu() {
    primesPt = 0; mu[1] = 1;
    for (int i = 2; i < P_SIZE; i++) {
        if (minFac[i] == 0) {
            mu[i] = -1;
            minFac[i] = i, primes[primesPt++] = i;
        }
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (P_SIZE - 1) / i); j++) {
            minFac[i * primes[j]] = primes[j];
            if (minFac[i] == primes[j]) {
                mu[i * primes[j]] = 0;
            } else {
                mu[i * primes[j]] = -mu[i];
            }
        }
    }
}

int getMu(long long int num) {
    if (num < P_SIZE)
        return mu[num];
    int facNum = 0;
    for (int i = 0; i < primesPt && 1ll * primes[i] * primes[i] <= num; i++) {
        if (num % primes[i] != 0)
            continue;
        num /= primes[i];
        if (num % primes[i] == 0)
            return 0;
        facNum ^= 1;
    }

    if (num > 1)
        facNum ^= 1;
    return (facNum & 1) ? 1 : -1;
}

int arr[SIZE], csts[6], mods[6] = {4, 9, 25, 49, 121, 169};
const int prod = 901800900;
vector<int> zeros, rems[6];
const int lim = 1e9 + 1;

long long int extEuclid(long long int a, long long int b, long long int & x, long long int & y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    long long int gcd = extEuclid(b, a % b, x, y), tmp = x;
    x = y; y = tmp - y * (a / b);
    return gcd;
}

long long int crt() {
    long long int modProd = mods[0], ans = csts[0];
    for (int i = 1; i < 6; i++) {
        long long int x, y, a = modProd, b = mods[i];
        long long int c = (csts[i] - ans % b + b) % b;
        long long int gcd = extEuclid(a, b, x, y), bg = b / gcd;
        if (c % gcd != 0)
            return -1;
        long long int cntAns = c / gcd % bg * x % bg;
        ans += modProd * cntAns; modProd *= bg;
    }

    ans = (ans % modProd + modProd) % modProd;
    return ans == 0 ? modProd : ans;
}

long long int ans;

void dfs(int pt) {
    if (pt == 6) {
        long long int ret = crt();
        if (ret == -1 || ret + 200 > lim)
            return;

        const auto check = [](int ret) {
            for (int i = ret; i < ret + 200; i++)
                if (abs(getMu(i)) != arr[i - ret])
                    return false;
            return true;
        };
        if (check(ret)) {
            ans = min(ans, ret);
            return;
        }
        ret += prod;
        if (ret + 200 > lim)
            return;
        if (check(ret))
            ans = min(ans, ret);
        return;
    }

    for (const auto & r : rems[pt]) {
        csts[pt] = r; dfs(pt + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initMu();
    for (int i = 0; i < 200; i++) {
        char ch; cin >> ch;
        arr[i] = (ch == '1');
        if (arr[i] == 0)
            zeros.push_back(i);
    }

    int siz = zeros.size();
    if (siz > 120) {
        cout << -1 << '\n';
        return 0;
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < siz && zeros[j] < mods[i]; j++) {
            const auto check = [](int p, int r) {
                for (int l = p - r; l < 200; l += p)
                    if (arr[l] != 0)
                        return false;
                return true;
            };
            if (check(mods[i], mods[i] - zeros[j]))
                rems[i].push_back(mods[i] - zeros[j]);
        }

        if (rems[i].empty()) {
            cout << -1 << '\n';
            return 0;
        }
    }

    ans = INT_MAX; dfs(0);
    cout << (ans == INT_MAX ? -1 : ans) << '\n';

    return 0;
}
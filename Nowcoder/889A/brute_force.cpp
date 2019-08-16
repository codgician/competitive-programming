#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 7812501

const int mod = 1e9;
const int cyc[2] = {768, 7812500};

int fibo[SIZE], n, m;
int mods[2] = {512, 1953125}, csts[2];

long long int extEuclid(long long int a, long long int b, long long int & x, long long int & y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    long long int gcd = extEuclid(b, a % b, x, y), tmp = x;
    x = y; y = tmp - y * (a / b);
    return gcd;
}
 
long long int crt(int equNum) {
    long long int modProd = mods[0], ans = csts[0];
    for (int i = 1; i < equNum; i++) {
        long long int x, y, a = modProd, b = mods[i];
        long long int c = (csts[i] - ans % b + b) % b;
        long long int gcd = extEuclid(a, b, x, y), bg = b / gcd;
 
        if (c % gcd != 0)
            return -1;
 
        long long int cntAns = (c / gcd % bg * x % bg + bg) % bg;
        ans += modProd * cntAns;
        modProd *= bg;
    }
 
    return (ans % modProd + modProd) % modProd;
}
 
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
    fibo[0] = 0; fibo[1] = 1;
    for (int i = 2; i < SIZE; i++)
        fibo[i] = (fibo[i - 1] + fibo[i - 2]) % mod;
    for (int i = 2; i < SIZE; i++)
        fibo[i] = (fibo[i - 1] + fastPow(fibo[i], m, mod)) % mod;
}

long long int solve(int id) {
    return (1ll * fibo[cyc[id] - 1] * (n / cyc[id]) % mods[id] + fibo[n % cyc[id]]) % mods[id];
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m; init();
    csts[0] = solve(0); csts[1] = solve(1);
    cout << crt(2) << '\n';
    return 0;
}
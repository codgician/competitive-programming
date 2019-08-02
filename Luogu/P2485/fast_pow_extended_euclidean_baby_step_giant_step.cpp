#include <bits/stdc++.h>
using namespace std;

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod; n >>= 1;
    }
    return ret;
}

long long int extEuclid(long long int a, long long int b, long long int & x, long long int & y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    long long int gcd = extEuclid(b, a % b, x, y), tmp = x;
    x = y; y = tmp - y * (a / b);
    return gcd;
}

long long int linCon(long long int a, long long int b, long long int p) { // ax = b (mod p)
    long long int x, y, gcd = extEuclid(a, p, x, y);
    a /= gcd; p /= gcd;
    if (b % gcd != 0)
        return -1;
    long long int ret = b / gcd * x;
    return (ret % p + p) % p;
}

long long int hiCon(long long int a, long long int b, long long int p) {  // a ^ x = b (mod p)
    unordered_map<long long int, int> mp;
    b %= p; long long int t = sqrt(p) + 1;
    for (long long int j = 0; j < t; j++) {
        long long int cnt = b * fastPow(a, j, p) % p;
        mp[cnt] = j;
    }

    a = fastPow(a, t, p);
    if (a == 0)
        return b == 0? 1 : -1;
    for (long long int i = 0; i <= t; i++) {
        long long int cnt = fastPow(a, i, p);
        long long int j = mp.find(cnt) == mp.end() ? -1 : mp[cnt];
        if (j >= 0 && i * t - j >= 0)
            return i * t - j;
    }
    return -1;
}

typedef long long int (* fptr)(long long int, long long int, long long int);
const fptr func[3] = {&fastPow, &linCon, &hiCon};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int qNum, type;
    cin >> qNum >> type; type--;
    while (qNum--) {
        long long int a, b, mod; cin >> a >> b >> mod;
        long long int ret = func[type](a, b, mod);
        if (ret == -1)
            cout << "Orz, I cannot find x!\n";
        else
            cout << ret << '\n';
    }

    return 0;
}
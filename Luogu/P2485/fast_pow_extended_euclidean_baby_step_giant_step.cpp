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

long long int phi(long long int num) {
    long long int ret = num;
    for (int i = 2; i * i <= num; i++) {
        if (num % i != 0)
            continue;
        ret -= ret / i;
        while (num % i == 0)
            num /= i;
    }
    if (num > 1)
        ret -= ret / num;
    return ret;
}

long long int bsgs(long long int a, long long int b, long long int p) {  // k * a ^ x = b (mod p)
    a %= p; b %= p;
    if (a == 0)
        return b == 0 ? 1 : -1;
    unordered_map<long long int, int> mp;
    int t = sqrt(p) + 1; long long int tmp = 1;
    for (int j = 0; j < t; j++) {
        if (mp.find(tmp) != mp.end())
            break;
        mp[tmp] = j; tmp = tmp * a % p;
    }

    long long int phip = phi(p), inv = fastPow(a, phip - t % phip, p); tmp = b;
    for (int i = 0; i <= t; i++) {
        int j = mp.find(tmp) == mp.end() ? -1 : mp[tmp];
        if (j != -1) 
            return 1ll * i * t + j;
        tmp = tmp * inv % p;
    }
    return -1;
}

typedef long long int (* fptr)(long long int, long long int, long long int);
const fptr func[3] = {&fastPow, &linCon, &bsgs};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int qNum, type;
    cin >> qNum >> type; type--;
    while (qNum--) {
        long long int a, b, p; cin >> a >> b >> p;
        long long int ret = func[type](a, b, p);
        if (ret == -1)
            cout << "Orz, I cannot find x!\n";
        else
            cout << ret << '\n';
    }

    return 0;
}
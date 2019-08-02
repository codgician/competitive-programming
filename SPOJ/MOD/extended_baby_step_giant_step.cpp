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

long long int bsgs(long long int k, long long int a, long long int b, long long int p) {
    unordered_map<long long int, long long int> mp;
    b %= p; long long int t = sqrt(p) + 1;
    for (long long int j = 0; j < t; j++) {
        long long int cnt = b * fastPow(a, j, p) % p;
        mp[cnt] = j;
    }

    a = fastPow(a, t, p);
    if (a == 0)
        return b == 0? 1 : -1;
    for (long long int i = 0; i <= t; i++) {
        long long int cnt = k * fastPow(a, i, p) % p;
        long long int j = mp.find(cnt) == mp.end() ? -1 : mp[cnt];
        if (j != -1 && i * t - j >= 0)
            return i * t - j;
    }
    return -1;
}

long long int hiCon(long long int a, long long int b, long long int p) {
    if (b == 1)
        return 0;
    long long int offset = 0, fac = 1;
    while (true) {
        if (fac == b) 
            return offset;
        long long int gcd = __gcd(a, p);
        if (b % gcd != 0)
            return -1;
        if (gcd == 1)
            break;
        offset++; p /= gcd; b /= gcd; 
        fac = a / gcd * fac % p;
    }

    long long int ret = bsgs(fac, a, b, p);
    return ret == -1 ? ret : ret + offset;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    long long int a, b, p;
    while (cin >> a >> p >> b) {
        if (a == 0 && p == 0 && b == 0)
            break;
        long long int ret = hiCon(a, b, p);
        if (ret == -1)
            cout << "No Solution\n";
        else
            cout << ret << '\n';
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

const long long int p = 1000000007;
long long int b, c;

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod; n >>= 1;
    }
    return ret;
}

const long long int inv2 = fastPow(2, p - 2, p);

bool check(long long int x, long long int y) {
    if ((x + y) % p == b && x * y % p == c)
        return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        cin >> b >> c;
        if (c == 0) {
            cout << 0 << ' ' << b << '\n';
            continue;
        }

        long long int t = b * b - 4 * c;
        t = (t % p + p) % p;
        if (t != 0 && fastPow(t, (p - 1) >> 1, p) != 1) {
            cout << "-1 -1\n";
            continue;
        }

        long long int qaq1 = fastPow(t, (p + 1) >> 2, p);
        long long int qaq2 = (p - qaq1) % p;

        long long int x1 = (qaq1 + b) * inv2 % p;
        long long int x2 = (qaq2 + b) * inv2 % p;
        long long int y1 = c * fastPow(x1, p - 2, p) % p;
        long long int y2 = c * fastPow(x2, p - 2, p) % p;

        if (x1 > y1) swap(x1, y1);
        if (x2 > y2) swap(x2, y2);

        if (check(x1, y1)) {
            cout << x1 << ' ' << y1 << '\n';
        } else if (check(x2, y2)) {
            cout << x2 << ' ' << y2 << '\n';
        } else {
            assert(false);
            cout << "-1 -1\n";
        }
    }

    return 0;
}
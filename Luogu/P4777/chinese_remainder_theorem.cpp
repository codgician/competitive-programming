#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

long long int cstArr[SIZE], modArr[SIZE];
int equNum;

long long int fastMul(long long int a, long long int n, long long int mod) {
    long long int ret = 0;
    a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret + a) % mod;
        a = (a << 1) % mod;
        n >>= 1;
    }
    return ret;
}

long long int extEuclid(long long int a, long long int b, long long int & x, long long int & y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    long long int gcd = extEuclid(b, a % b, x, y), tmp = x;
    x = y;
    y = tmp - y * (a / b);
    return gcd;
}

long long int crt() {
    long long int modProd = modArr[0], ans = cstArr[0];
    for (int i = 1; i < equNum; i++) {
        long long int x, y, a = modProd, b = modArr[i];
        long long int c = (cstArr[i] - ans % b + b) % b;
        long long int gcd = extEuclid(a, b, x, y), bg = b / gcd;

        if (c % gcd != 0)
            return -1;

        long long int cntAns = fastMul(x, c / gcd, bg);
        ans += modProd * cntAns;
        modProd *= bg;
        ans = (ans % modProd + modProd) % modProd;
    }

    return (ans % modProd + modProd) % modProd;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> equNum;
    for (int i = 0; i < equNum; i++)
        cin >> modArr[i] >> cstArr[i];
    cout << crt() << '\n';
    return 0;
}
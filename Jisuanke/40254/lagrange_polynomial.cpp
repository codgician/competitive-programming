#include <bits/stdc++.h>
using namespace std;

#define SIZE 1010

const int mod = 9999991;

long long int pre[SIZE], suf[SIZE];
long long int yFst[SIZE], ySnd[SIZE];
long long int factorial[SIZE], invFactorial[SIZE];

long long int fastPow(long long int a, long long int n) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod; n >>= 1;
    }
    return ret;
}

void initFactorial() {
    factorial[0] = 1;
    for (int i = 1; i < SIZE; i++)
        factorial[i] = (factorial[i - 1] * i) % mod;
}

void initInvFactorial() {
    invFactorial[SIZE - 1] = fastPow(factorial[SIZE - 1], mod - 2);
    for (int i = SIZE - 2; i >= 0; i--) {
        invFactorial[i] = invFactorial[i + 1] * (i + 1) % mod;
    }
}

long long int lagrangeCons(long long int x, int len, long long int * y) {
    x %= mod; pre[0] = x; suf[len] = x - len;
    for (int i = 1; i <= len; i++) 
        pre[i] = pre[i - 1] * (x - i) % mod;
    for (int i = len - 1; i >= 0; i--)
        suf[i] = suf[i + 1] * (x - i) % mod;

    long long int ret = 0;
    for (int i = 0; i <= len; i++) {
        long long int cnt = y[i] * (i == 0 ? 1ll : pre[i - 1]) % mod * (i == len ? 1ll : suf[i + 1]) % mod;
        cnt = cnt * invFactorial[i] % mod * invFactorial[len - i] % mod;
        cnt = ((len + i) & 1) ? -cnt : cnt;
        ret = (ret + cnt + mod) % mod;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initFactorial(); initInvFactorial();
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int len, qNum; cin >> len >> qNum;
        for (int i = 0; i <= len; i++)
            cin >> yFst[i];
        yFst[len + 1] = lagrangeCons(len + 1, len, yFst);
        ySnd[0] = yFst[0];
        for (int i = 1; i <= len + 1; i++)
            ySnd[i] = (ySnd[i - 1] + yFst[i]) % mod;
        while (qNum--) {
            int qLeftPt, qRightPt; cin >> qLeftPt >> qRightPt;
            long long int ans = (lagrangeCons(qRightPt, len + 1, ySnd) - lagrangeCons(qLeftPt - 1, len + 1, ySnd) + mod) % mod;
            cout << ans << '\n';
        }
    }

    return 0;
}
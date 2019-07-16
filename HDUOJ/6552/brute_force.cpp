#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

long long int mod = 1e9 + 7;

long long int factorialArr[SIZE], invFactorialArr[SIZE];

long long int fastPow(long long int a, long long int n) {
    long long int ret = 1;
    a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ret;
}

void initFactorial() {
    factorialArr[0] = 1;
    for (int i = 1; i < SIZE; i++)
        factorialArr[i] = factorialArr[i - 1] * i % mod;
}

void initInvFactorial() {
    invFactorialArr[SIZE - 1] = fastPow(factorialArr[SIZE - 1], mod - 2);
    for (int i = SIZE - 2; i >= 0; i--) {
        invFactorialArr[i] = invFactorialArr[i + 1] * (i + 1) % mod;
    }
}

long long int getComb(int n, int m) {
    if (m > n)
        return 0;
    return factorialArr[n] * invFactorialArr[m] % mod * invFactorialArr[n - m] % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initFactorial(); initInvFactorial();

    int n, k;
    while (cin >> n >> k) {
        long long int ans = 0; int a1, a2, a3, a4, a5, a6, a7;
        cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6 >> a7;

        const int rst1 = k; 
        for (int b123 = 0; 3 * b123 <= rst1; b123++) {
            const int rst2 = rst1 - 3 * b123;
            for (int b12 = 0; 2 * b12 <= rst2; b12++) {
                const int rst3 = rst2 - 2 * b12;
                for (int b13 = 0; 2 * b13 <= rst3; b13++) {
                    const int rst4 = rst3 - 2 * b13;
                    for (int b23 = 0; 2 * b23 <= rst4; b23++) {
                        const int rst5 = rst4 - 2 * b23, s2 = b12 + b13 + b23;
                        for (int b1 = max(0, a1 - b12 - b13 - b123); b1 <= rst5; b1++) {
                            const int rst6 = rst5 - b1;
                            for (int b2 = max(0, max(a2 - b12 - b23 - b123, a4 - b1 - s2 - b123)); b2 <= rst6; b2++) {
                                int b3 = rst6 - b2; int num = b1 + b2 + b3 + s2 + b123;
                                if (b3 + b13 + b23 + b123 < a3 || num - b2 < a6 || num - b1 < a5 || num < a7)
                                    continue;
                                long long int cnt = getComb(n, b1) * getComb(n - b1, b2) % mod;
                                cnt = cnt * getComb(n - b1 - b2, b3) % mod;
                                cnt = cnt * getComb(n - b1 - b2 - b3, b12) % mod;
                                cnt = cnt * getComb(n - b1 - b2 - b3 - b12, b13) % mod;
                                cnt = cnt * getComb(n - b1 - b2 - b3 - b12 - b13, b23) % mod;
                                cnt = cnt * getComb(n - b1 - b2 - b3 - b12 - b13 - b23, b123) % mod;
                                ans = (ans + cnt) % mod;
                            }
                        }
                    }
                }
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
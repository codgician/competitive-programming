#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

const int mod = 998244353;

long long int factorialArr[SIZE], invFactorialArr[SIZE];

long long int fastPow(long long int a, long long int n) {
    long long int ans = 1;
    a %= mod;
    while (n > 0) {
        if (n & 1)
            ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

void initFactorial() {
    factorialArr[0] = 1;
    for (int i = 1; i < SIZE; i++) {
        factorialArr[i] = factorialArr[i - 1] * i % mod;
    }
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
    initFactorial();
    initInvFactorial();

    int num, x, y;
    cin >> num >> x >> y;

    long long int ans = 0;
    for (int i = 0; i <= num; i++) {
        // For each vertex set of size i, iff all edges are erased should it be a independent set
        long long int edgeNum = 1ll * i * (i - 1) / 2;
        ans += getComb(num, i) * fastPow(x, edgeNum) % mod * fastPow(fastPow(y, edgeNum), mod - 2) % mod;
        ans %= mod;
    }
    cout << ans << endl;

    return 0;
}

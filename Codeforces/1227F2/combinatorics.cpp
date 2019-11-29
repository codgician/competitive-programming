#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010
const int mod = 998244353;

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod; n >>= 1;
    }
    return ret;
}

long long int factorials[SIZE], invFactorials[SIZE];
int arr[SIZE];

void initFactorials() {
    factorials[0] = 1;
    for (int i = 1; i < SIZE; i++)
        factorials[i] = factorials[i - 1] * i % mod;
    invFactorials[SIZE - 1] = fastPow(factorials[SIZE - 1], mod - 2, mod);
    for (int i = SIZE - 2; i >= 0; i--)
        invFactorials[i] = invFactorials[i + 1] * (i + 1) % mod;
}

long long int binom(int n, int m) {
    return m > n ? 0 : factorials[n] * invFactorials[m] % mod * invFactorials[n - m] % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initFactorials();

    int len, col, diff = 0; cin >> len >> col;
    for (int i = 0; i < len; i++)
        cin >> arr[i];
    if (col == 1) {
        cout << 0 << '\n';
        return 0;
    }
    for (int i = 0; i < len; i++)
        diff += (arr[i] != arr[(i + 1) % len]);
    
    long long int ans = 0;
    for (int i = 0; i <= (diff >> 1); i++)
        (ans += binom(diff, i) * binom(diff - i, i) % mod * fastPow(col - 2, diff - i * 2, mod) % mod * fastPow(col, len - diff, mod) % mod) %= mod;
    
    ans = (fastPow(col, len, mod) - ans) * fastPow(2, mod - 2, mod) % mod;
    cout << (ans + mod) % mod << '\n';
    return 0;
}
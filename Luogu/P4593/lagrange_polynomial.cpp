#include <bits/stdc++.h>
using namespace std;

#define SIZE 101

const long long int mod = 1e9 + 7;

long long int val[SIZE], pre[SIZE], suf[SIZE], rem[SIZE];
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

void bruteForce(int len, int k) {
    val[0] = 0; val[1] = 1;
    for (int i = 2; i <= len; i++)
        val[i] = (val[i - 1] + fastPow(i, k)) % mod;
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
        long long int maxv; int num;
        cin >> maxv >> num;
        bruteForce(num + 2, num + 1);

        long long int ans = 0; rem[0] = 0; 
        for (int i = 1; i <= num; i++)
            cin >> rem[i];
        for (int i = 0; i <= num; i++) {
            ans = (ans + lagrangeCons(maxv - rem[i], num + 2, val)) % mod;
            for (int j = 0; j <= num; j++)
                if (rem[j] > rem[i])
                    ans = (ans - fastPow(rem[j] - rem[i], num + 1) + mod) % mod;
        }
        cout << ans << '\n';
    }

    return 0;
}
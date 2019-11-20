#include <bits/stdc++.h>
using namespace std;

#define SIZE 600010

const int mod = 998244353, pr = 3;
long long int fst[SIZE], snd[SIZE], omg[SIZE], inv[SIZE];
long long int pos[SIZE], fstLen, sndLen, len, lenInv;

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod; n >>= 1;
    }
    return ret;
}

void init() {
    int lim = 0; len = 1;
    while (len < fstLen + sndLen - 1)
        len <<= 1, lim++;
    omg[0] = 1; inv[0] = 1; 
    long long int w =  fastPow(pr, (mod - 1) / len, mod);
    for (int i = 1; i < len; i++) {
        omg[i] = omg[i - 1] * w % mod;
        inv[len - i] = omg[i];
        pos[i] = (pos[i >> 1] >> 1) | ((i & 1) << (lim - 1));
    }
}

void ntt(long long int * arr, long long int * omg) {
    for (int i = 0; i < len; i++) 
        if (i < pos[i])
            swap(arr[i], arr[pos[i]]);
    for (int l = 2; l <= len; l <<= 1) {
        int midPt = l >> 1, step = len / l;
        for (long long int * p = arr; p != arr + len; p += l) {
            for (int i = 0, cnt = 0; i < midPt; i++, cnt += step) {
                long long int t = omg[cnt] * p[i + midPt] % mod;
                p[i + midPt] = (p[i] - t + mod) % mod; 
                p[i] = (p[i] + t) % mod;
            }
        }
    }
}

void multiply() {
    ntt(fst, omg); ntt(snd, omg);
    for (int i = 0; i < len; i++)
        fst[i] = fst[i] * snd[i] % mod;
    ntt(fst, inv);
    for (int i = 0; i < len; i++)
        fst[i] = fst[i] * lenInv % mod;
}

long long int factorial[SIZE], invFactorial[SIZE];

void initFactorial() {
    factorial[0] = 1;
    for (int i = 1; i < SIZE; i++)
        factorial[i] = factorial[i - 1] * i % mod;
    invFactorial[SIZE - 1] = fastPow(factorial[SIZE - 1], mod - 2, mod);
    for (int i = SIZE - 2; i >= 0; i--)
        invFactorial[i] = invFactorial[i + 1] * (i + 1) % mod;
}

long long int binom(long long int n, long long int m) {
    return m > n ? 0 : factorial[n] * invFactorial[m] % mod * invFactorial[n - m] % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initFactorial();
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int qNum; cin >> fstLen >> qNum; sndLen = fstLen;
        for (int i = 0; i < fstLen; i++)
            cin >> fst[i];
        int ops[3] = {0, 0, 0};
        for (int i = 0; i < qNum; i++) {
            int id; cin >> id;
            ops[id - 1]++;
        }

        init(); lenInv = fastPow(len, mod - 2, mod);
        for (int t = 1; t <= 3; t++) {
            if (ops[t - 1] == 0)
                continue;
            for (int i = 0; i * t < sndLen; i++)
                snd[i * t] = binom(ops[t - 1] + i - 1, i);
            multiply();
            fill(fst + fstLen, fst + len, 0); fill(snd + 0, snd + len, 0);
        }

        long long int ans = 0;
        for (int i = 0; i < fstLen; i++)
            ans ^= 1ll * (i + 1) * fst[i];
        cout << ans << '\n';
    }

    return 0;
}

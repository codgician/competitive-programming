#include <bits/stdc++.h>
using namespace std;

#define SIZE 3000010
const int mod = 998244353;
const int pr = 3;

long long int fst[SIZE], snd[SIZE], omg[SIZE], inv[SIZE];
long long int pos[SIZE], fstLen, sndLen, len, lim;

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
    len = 1, lim = 0;
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
    init();
    ntt(fst, omg); ntt(snd, omg);
    for (int i = 0; i < len; i++)
        fst[i] = fst[i] * snd[i] % mod;
    ntt(fst, inv);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> fstLen >> sndLen; fstLen++; sndLen++;
    for (int i = 0; i < fstLen; i++)
        cin >> fst[i];
    for (int i = 0; i < sndLen; i++)
        cin >> snd[i];
    multiply();

    long long int lenInv = fastPow(len, mod - 2, mod);
    cout << fst[0] * lenInv % mod;
    for (int i = 1; i < fstLen + sndLen - 1; i++)
        cout << ' ' << fst[i] * lenInv % mod;
    cout << '\n';

    return 0;   
}
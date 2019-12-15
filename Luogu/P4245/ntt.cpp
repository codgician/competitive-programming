#include <bits/stdc++.h>
using namespace std;

#define SIZE 400010
const int mods[3] = {998244353, 1004535809, 469762049}, pr = 3;

long long int fst[3][SIZE], snd[3][SIZE], omg[SIZE], inv[SIZE];
int pos[SIZE], fstLen, sndLen, len, lim;

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod; n >>= 1;
    }
    return ret;
}

long long int inv1, inv2;
long long int crt(int pt, int mod) {
    long long int a = fst[0][pt], b = fst[1][pt], c = fst[2][pt], m1 = mods[0], m2 = mods[1], m3 = mods[2];
    long long int x = ((b - a) % m2 * inv1 % m2 + m2) % m2 * m1 + a;
    long long int ret = (((c - x % m3) % m3 * inv2 % m3 + m3) % m3 * (m1 * m2 % mod) % mod + x) % mod;
    return (ret + mod) % mod;
}

void init(int mod) {
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

void ntt(long long int * arr, long long int * omg, int mod) {
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

void multiply(long long int * fst, long long int * snd, int mod) {
    init(mod); int lenInv = fastPow(len, mod - 2, mod);
    ntt(fst, omg, mod); ntt(snd, omg, mod);
    for (int i = 0; i < len; i++)
        fst[i] = fst[i] * snd[i] % mod;
    ntt(fst, inv, mod);
    for (int i = 0; i < fstLen + sndLen - 1; i++)
        fst[i] = fst[i] * lenInv % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    inv1 = fastPow(mods[0], mods[1] - 2, mods[1]), inv2 = fastPow(1ll * mods[0] * mods[1], mods[2] - 2, mods[2]);
    int mod; cin >> fstLen >> sndLen >> mod; fstLen++; sndLen++;
    for (int i = 0; i < fstLen; i++)
        cin >> fst[0][i], fst[1][i] = fst[0][i], fst[2][i] = fst[0][i];
    for (int i = 0; i < sndLen; i++)
        cin >> snd[0][i], snd[1][i] = snd[0][i], snd[2][i] = snd[0][i];

    for (int t = 0; t < 3; t++)
        multiply(fst[t], snd[t], mods[t]);
    cout << crt(0, mod);
    for (int i = 1; i < fstLen + sndLen - 1; i++)
        cout << ' ' << crt(i, mod);
    cout << '\n';
    return 0;   
}
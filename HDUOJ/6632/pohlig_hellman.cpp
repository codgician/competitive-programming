#include <bits/stdc++.h>
using namespace std;

long long int fastMul(long long int a, long long int n, long long int mod) {
    long long int ret = 0; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret + a) % mod;
        a = (a << 1) % mod; n >>= 1;
    }
    return ret;
}

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (__int128)ret * a % mod;
        a = (__int128)a * a % mod; n >>= 1;
    }
    return ret;
}

/* Chinese Remainder Theorem */

long long int modArr[2], cstArr[2];   // x % modArr[i] = cstArr[i]

long long int extEuclid(long long int a, long long int b, long long int & x, long long int & y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    long long int gcd = extEuclid(b, a % b, x, y), tmp = x;
    x = y; y = tmp - y * (a / b);
    return gcd;
}

long long int crt(int equNum) {
    long long int modProd = modArr[0]; long long int ans = cstArr[0];
    for (int i = 1; i < equNum; i++) {
        long long int x, y, a = modProd, b = modArr[i];
        long long int c = (cstArr[i] - ans % b + b) % b;
        long long int gcd = extEuclid(a, b, x, y), bg = b / gcd;

        if (c % gcd != 0)
            return -1;

        long long int cntAns = fastMul(x, c / gcd, bg);
        ans += modProd * cntAns;
        modProd *= bg;
    }

    return (ans % modProd + modProd) % modProd;
}

/* Baby step Giant step */

long long int bsgs(long long int a, long long int b, long long int p, long long int ord) {  // k * a ^ x = b (mod p)
    a %= p; b %= p;
    if (a == 0)
        return b == 0 ? 1 : -1;
    unordered_map<long long int, int> mp;
    long long int t = sqrt(ord) + 1; long long int tmp = 1;
    for (long long int j = 0; j < t; j++) {
        if (mp.find(tmp) != mp.end())
            break;
        mp[tmp] = j; tmp = (__int128)tmp * a % p;
    }

    long long int inv = fastPow(a, ord - t % ord, p); tmp = b;
    for (long long int i = 0; i <= t; i++) {
        long long int j = mp.find(tmp) == mp.end() ? -1 : mp[tmp];
        if (j != -1) 
            return i * t + j;
        tmp = (__int128)tmp * inv % p;
    }
    return -1;
}

/* Pohlig-Hellman Algorithm */

long long int getOrd(long long int a, long long int p) {
    long long int phip = p - 1, ret = phip;
    int twoExp = 0, threeExp = 0;
    while ((phip & 1) == 0)
        twoExp++, phip >>= 1;
    while (phip % 3 == 0)
        threeExp++, phip /= 3;

    long long int base = 1;
    for (int i = 0; i <= threeExp && base <= ret; i++) {
        long long int cnt = base;
        for (int j = 0; j <= twoExp && cnt <= ret; j++) {
            if (fastPow(a, cnt, p) == 1)
                ret = min(ret, cnt);
            cnt <<= 1;
        }
        base *= 3;
    }
    return ret;
}

long long int pohligHellman(long long int a, long long int b, long long int mod, 
                            long long int ord, long long int p, int e) {    // ord = p ^ e
    long long int ret = 0;
    long long int y = fastPow(a, ord / p, mod), p1 = ord / p, p2 = 1;
    for (int k = 0; k < e; k++) {
        long long int inv = fastPow(fastPow(a, ord - 1, mod), ret, mod);
        long long int bk = fastPow((__int128)inv * b % mod, p1, mod); p1 /= p;
        long long int dk = bsgs(y, bk, mod, p);
        if (dk == -1)
            return -1;
        ret = (ret + p2 * dk % ord) % ord; p2 *= p;
    }
    return ret;
}

int primes[2] = {2, 3}, primesPt = 2;

long long int hiCon(long long int a, long long int b, long long int p) {
    long long int ord = getOrd(a, p), tmp = ord; int equNum = 0;
    for (int i = 0; i < primesPt; i++) {
        long long int prime = primes[i];
        if (tmp % prime != 0)
            continue;
        int exp = 1; long long int cnt = prime; tmp /= prime;
        while (tmp % prime == 0)
            exp++, cnt *= prime, tmp /= prime;

        long long int ai = fastPow(a, ord / cnt, p), bi = fastPow(b, ord / cnt, p);
        cstArr[equNum] = pohligHellman(ai, bi, p, cnt, prime, exp);
        if (cstArr[equNum] == -1)
            return -1;
        modArr[equNum++] = cnt;
    }

    return crt(equNum);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        long long int p, a, b; cin >> p >> a >> b;
        cout << hiCon(a, b, p) << '\n';
    }

    return 0;
}

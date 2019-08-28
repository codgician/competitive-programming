#include <bits/stdc++.h>
using namespace std;

#define SIZE 1010
#define EQU_SIZE 30

int primes[SIZE], minFac[SIZE], primesPt;
int mods[EQU_SIZE], csts[EQU_SIZE];

void initPrimes() {
    memset(minFac, 0, sizeof(minFac));
    primesPt = 0;
    for (int i = 2; i < SIZE; i++) {
        if (minFac[i] == 0) {
            minFac[i] = i;
            primes[primesPt++] = i;
        }
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (SIZE - 1) / i); j++) {
            minFac[i * primes[j]] = primes[j];
        }
    }
}

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod; n >>= 1;
    }
    return ret;
}

long long int extEuclid(long long int a, long long int b, long long int & x, long long int & y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    long long int gcd = extEuclid(b, a % b, x, y), tmp = x;
    x = y; y = tmp - y * (a / b);
    return gcd;
}

long long int inv(long long int a, long long int mod) {
    long long int x, y;
    extEuclid(a, mod, x, y);
    return (x + mod) % mod;
}

long long int crt(int equNum) {
    long long int modProd = mods[0], ans = csts[0];
    for (int i = 1; i < equNum; i++) {
        long long int x, y, a = modProd, b = mods[i];
        long long int c = (csts[i] - ans % b + b) % b;
        long long int gcd = extEuclid(a, b, x, y), bg = b / gcd;

        if (c % gcd != 0)
            return -1;

        long long int cntAns = (c / gcd % bg * x % bg + bg) % bg;
        ans += modProd * cntAns;
        modProd *= bg;
    }

    return (ans % modProd + modProd) % modProd;
}

class Fac {
public:
    long long int p, pk;
    vector<long long int> factorials, invFactorials;
};

vector<Fac> facs;

void factorize(long long int num) {
    facs.clear(); facs.reserve(20);
    for (int i = 0; i < primesPt && primes[i] * primes[i] <= num; i++) {
        if (num % primes[i] != 0)
            continue;
        Fac f = Fac{primes[i], primes[i], vector<long long int>(), vector<long long int>()};
        num /= primes[i];
        while (num % primes[i] == 0)
            f.pk *= primes[i], num /= primes[i];
        facs.push_back(f);
    }
    if (num > 1)
        facs.push_back(Fac{num, num, vector<long long int>(), vector<long long int>()});
}

void initFactorials() {
    for (auto & f : facs) {
        auto & v = f.factorials; v.reserve(f.pk); v.push_back(1);
        for (int i = 1; i < f.pk; i++)
            v.push_back(v.back() * (i % f.p == 0 ? 1 : i) % f.pk);
        auto & vi = f.invFactorials; vi.reserve(f.pk); vi.push_back(inv(v.back(), f.pk));
        for (int i = f.pk; i >= 1; i--)
            vi.push_back(vi.back() * (i % f.p == 0 ? 1 : i) % f.pk);
        reverse(vi.begin(), vi.end());
    }
}

long long int calc(long long int n, const Fac & f) {
    if (n == 0)
        return 1;
    long long int ret = fastPow(f.factorials[f.pk - 1], n / f.pk, f.pk);
    return ret * f.factorials[n % f.pk] % f.pk * calc(n / f.p, f) % f.pk;
}

long long int calcInv(long long int n, const Fac & f) {
    if (n == 0)
        return 1;
    long long int ret = fastPow(f.invFactorials[f.pk - 1], n / f.pk, f.pk);
    return ret * f.invFactorials[n % f.pk] % f.pk * calcInv(n / f.p, f) % f.pk;
}

long long int comb1(long long int n, long long int m, const Fac & f) {
    if (n == 0)
        return 1;
    const auto comb = [f](long long int n, long long int m) {
        return m > n ? 0 : f.factorials[n] * f.invFactorials[m] % f.p * f.invFactorials[n - m] % f.p;
    };
    return comb(n % f.p, m % f.p) * comb1(n / f.p, m / f.p, f) % f.p;
}

long long int comb2(long long int n, long long int m, const Fac & f) {
    long long int occ = 0;
    for (long long int i = n; i > 0; i /= f.p)
        occ += i / f.p;
    for (long long int i = m; i > 0; i /= f.p)
        occ -= i / f.p;
    for (long long int i = n - m; i > 0; i /= f.p)
        occ -= i / f.p;
    return fastPow(f.p, occ, f.pk) * calc(n, f) % f.pk * calcInv(m, f) % f.pk * calcInv(n - m, f) % f.pk;
}

long long int extLucas(long long int n, long long int m) {
    int equNum = 0;
    for (const auto & f : facs) {
        mods[equNum] = f.pk; 
        csts[equNum] = f.p == f.pk ? comb1(n, m, f) : comb2(n, m, f);
        equNum++;
    }
    return crt(equNum);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    long long int n, m, p; cin >> n >> m >> p;
    initPrimes(); factorize(p); initFactorials();
    cout << extLucas(n, m) << '\n';

    return 0;
}
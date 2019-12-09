#include <bits/stdc++.h>
using namespace std;

#define MR_SIZE 9
const int mr[MR_SIZE] = {2, 3, 5, 7, 11, 13, 17, 19, 23};

long long int fastPow(__int128 a, long long int n, long long int mod) {
    __int128 ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = ret * a % mod;
        a = a * a % mod; n >>= 1;
    }
    return ret;
}

bool millerRobin(long long int n, int p) {
    for (long long int k = n - 1; k > 0; k >>= 1) {
        long long int cnt = fastPow(p, k, n);
        if (cnt != 1 && cnt != n - 1)
            return false;
        if ((k & 1) == 1 || cnt == n - 1)
            return true;
    }
    return true;
}

bool isPrime(long long int n) {
    if (n < 2)
        return false;
    for (int i = 0; i < MR_SIZE; i++)
        if (n % mr[i] == 0)
            return n == mr[i];
    bool ret = true;
    for (int i = 0; i < MR_SIZE && ret; i++)
        ret &= millerRobin(n, mr[i]);
    return ret;
}

long long int func(long long int x, long long int c, long long int md) {
    return ((__int128)x * x + c) % md;
}

long long int findFac(long long int n) {
    for (int i = 0; i < MR_SIZE; i++)
        if (n % mr[i] == 0)
            return mr[i];
    long long int c = rand() % (n - 1) + 1;
    long long int s = 0, t = 0, val = 1;
    for (long long int lim = 2; lim <<= 1; s = t, val = 1) {
        for (long long int i = 1; i <= lim; i++) {
            t = func(t, c, n);
            val = (__int128)val * abs(t - s) % n;
            if (i % 127 == 0) {
                long long int gcd = __gcd(val, n);
                if (gcd > 1)
                    return gcd;
            }
        }
        long long int gcd = __gcd(n, val);
        if (gcd > 1)
            return gcd;
    }
    assert(false);
    return n;
}

unordered_map<long long int, int> mp;
void pollardRho(long long int n) {
    if (n < 2)
        return;
    if (isPrime(n)) {
        mp[n]++;
        return;
    }
    long long int p = findFac(n);
    while (p >= n)
        p = findFac(p);
    pollardRho(p); pollardRho(n / p);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    srand(time(0));

    long long int n;
    while (cin >> n) {
        mp.clear(); pollardRho(n);
        int d = 1;
        for (const auto & p : mp)
            d *= (p.second + 1);
        if (d != 4) {
            cout << "is not a D_num\n";
            continue;
        }

        if ((int)mp.size() == 1) {
            long long int fst = mp.begin() -> first;
            cout << fst << ' ' << fst * fst << ' ' << n << '\n';
        } else {
            long long int fst = mp.begin() -> first, snd = next(mp.begin()) -> first;
            tie(fst, snd) = make_tuple(min(fst, snd), max(fst, snd));
            cout << fst << ' ' << snd << ' ' << n << '\n';
        }
    }

    return 0;
}

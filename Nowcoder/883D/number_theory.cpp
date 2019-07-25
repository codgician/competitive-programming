#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

int primeArr[SIZE], minFacArr[SIZE], primePt;

void initPrime() {
    memset(minFacArr, 0, sizeof(minFacArr));
    primePt = 0;
    for (int i = 2; i < SIZE; i++) {
        if (minFacArr[i] == 0) {
            minFacArr[i] = i;
            primeArr[primePt++] = i;
        }
        for (int j = 0; j < primePt && primeArr[j] <= min(minFacArr[i], (SIZE - 1) / i); j++) {
            minFacArr[i * primeArr[j]] = primeArr[j];
        }
    }
}

vector<pair<int, int> > fac;

long long int fastPow(long long int a, long long int n) {
    long long int ret = 1;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a);
        a *= a; n >>= 1;
    }
    return ret;
}

long long int fastPowMod(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod; n >>= 1;
    }
    return ret;
}

long long int calc(long long int num, long long int mod) {
    return (fastPowMod(10, num, mod) - 1 + mod) % mod * fastPowMod(9, mod - 2, mod) % mod;
}

int ceilDiv(int fst, int snd) {
    return fst / snd + (fst % snd != 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initPrime();
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        long long int mod, n, m, cyc, cnt = INT_MAX;
        cin >> mod >> n >> m; cyc = mod - 1;

        if (mod == 3) {
            cnt = 3;
        } else {
            for (int i = 1; i * i <= cyc; i++) {
                if (cyc % i != 0)
                    continue;
                if (i < cnt && calc(i, mod) == 0)
                    cnt = i;
                if (i * i != cyc && cyc / i < cnt && calc(cyc / i, mod) == 0)
                    cnt = cyc / i;
            }
        }

        if (cnt == INT_MAX) {
            cout << 0 << '\n';
            continue;
        }

        fac.clear(); cyc = cnt;
        for (int i = 0; i < primePt && primeArr[i] * primeArr[i] <= cnt; i++) {
            if (cnt % primeArr[i] != 0)
                continue;
            int cntExp = 1; cnt /= primeArr[i];
            while (cnt % primeArr[i] == 0) {
                cnt /= primeArr[i]; cntExp++;
            }
            fac.push_back(make_pair(primeArr[i], cntExp));
        }
        if (cnt > 1)
            fac.push_back(make_pair(cnt, 1));

        long long int ans = 0;
        for (int j = 1; j <= min(m, 30ll); j++) {
            long long int qaq = 1;
            for (auto & p : fac)
                qaq *= fastPow(p.first, ceilDiv(p.second, j));
            ans += (n / qaq) * (j == 30 ? (m - 30 + 1) : 1); 
        }

        cout << ans << '\n';
    }

    return 0;
}
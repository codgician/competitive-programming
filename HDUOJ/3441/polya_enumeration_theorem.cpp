#include <bits/stdc++.h>
using namespace std;

#define SIZE 1000100
const int mod = 1e9 + 7;

int minFacArr[SIZE], primeArr[SIZE], primePt;

void initPrime() {
    memset(minFacArr, 0, sizeof(minFacArr));
    primePt = 0;
    for (int i = 2; i < SIZE; i++) {
        if (minFacArr[i] == 0) {
            minFacArr[i] = i;
            primeArr[primePt++] = i;
        }
        for (int j = 0; j < primePt && primeArr[j] <= min(minFacArr[i], (SIZE - 1) / i); j++)
            minFacArr[i * primeArr[j]] = primeArr[j];
    }
}

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

unordered_map<long long int, int> mp, cntMp;
vector<long long int> fac;
int len, color;
long long int ans;

void getPrimeFac(long long int n) {
    for (int i = 0; i < primePt && 1ll * primeArr[i] * primeArr[i] <= n; i++) {
        if (n % primeArr[i] != 0)
            continue;
        int cntExp = 0;
        while (n % primeArr[i] == 0) {
            n /= primeArr[i];
            cntExp++;
        }
        mp[primeArr[i]] += cntExp;
    }
    if (n > 1)
        mp[n]++;
}

long long int solveSquare(int len) {
    long long int ans = 0;
    if (len & 1) {
        // odd
        ans = (ans + fastPow(color, 1ll * len * len)) % mod;
        ans = (ans + 2 * fastPow(color, ((1ll * len * len - 1) >> 2) + 1) % mod) % mod;
        ans = (ans + fastPow(color, (1ll * len * len + 1) >> 1)) % mod;
    } else {
        // even
        ans = (ans + fastPow(color, 1ll * len * len)) % mod;
        ans = (ans + 2 * fastPow(color, (1ll * len * len) >> 2) % mod) % mod;
        ans = (ans + fastPow(color, (1ll * len * len) >> 1)) % mod;
    }
    ans = ans * fastPow(4, mod - 2) % mod;
    return ans;
}

void dfs2(unordered_map<long long int, int>::iterator cntIt, long long int cntProd) {
    while (cntIt != cntMp.end() && cntIt -> second == 0)
        cntIt = next(cntIt);

    if (cntIt == cntMp.end()) {
        fac.push_back(cntProd);
        return;
    }
    
    long long int tmp = 1;
    for (int i = 0; i <= cntIt -> second; i++) {
        dfs2(next(cntIt), cntProd * tmp);
        tmp *= cntIt -> first;
    }
}

long long int _phi(long long int num) {
    long long int ret = num;
    for (auto p : cntMp) {
        if (p.second > 0 && num % p.first == 0) {
            ret -= ret / p.first;
            while (num % p.first == 0)
                num /= p.first;
        }
    }
    return ret % mod;
}

void dfs(unordered_map<long long int, int>::iterator cntIt, long long int cntProd) {
    if (cntIt == mp.end()) {
        long long int n = (1ll * len * len - 1) / (cntProd * cntProd), m = solveSquare(cntProd);
        fac.clear();
        dfs2(cntMp.begin(), 1);

        // Solve ring
        long long int cntAns = 0;
        for (auto i : fac) {
            cntAns = (cntAns + _phi(n / i) * fastPow(m, i) % mod) % mod;
        }
        cntAns = cntAns * fastPow(n, mod - 2) % mod;
        
        ans = (ans + cntAns) % mod;
        return;
    }

    long long int tmp = 1;
    for (int i = 0; i <= cntIt -> second; i += 2) {
        cntMp[cntIt -> first] -= i;
        dfs(next(cntIt), cntProd * tmp);
        cntMp[cntIt -> first] += i;
        tmp *= cntIt -> first;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initPrime();
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++) {
        cin >> len >> color;
        cout << "Case " << t << ": ";
        if (len == 1) {
            cout << color << '\n';
            continue;
        }

        mp.clear(); cntMp.clear();
        getPrimeFac(len + 1);
        getPrimeFac(len - 1);
        cntMp = mp;

        ans = 0;
        dfs(mp.begin(), 1);

        ans = ans * color % mod;
        cout << ans << '\n';
    }

    return 0;
}
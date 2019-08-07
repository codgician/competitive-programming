#include <bits/stdc++.h>
using namespace std;

#define SIZE 5000010

int primes[SIZE], minFac[SIZE], primesPt;
int phi[SIZE], mu[SIZE], mert[SIZE];
long long int pfxPhi[SIZE];

void initMuPhi() {
    memset(minFac, 0, sizeof(minFac));
    primesPt = 0; mu[1] = 1; phi[1] = 1;
    for (int i = 2; i < SIZE; i++) {
        if (minFac[i] == 0) {
            minFac[i] = i;
            mu[i] = -1, phi[i] = i - 1;
            primes[primesPt++] = i;
        }
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (SIZE - 1) / i); j++) {
            minFac[i * primes[j]] = primes[j];
            if (minFac[i] == primes[j]) {
                mu[i * primes[j]] = 0;
                phi[i * primes[j]] = phi[i] * primes[j];
            } else {
                mu[i * primes[j]] = -mu[i];
                phi[i * primes[j]] = phi[i] * (primes[j] - 1);
            }
        }
    }

    pfxPhi[0] = 0; mert[0] = 0;
    for (int i = 1; i < SIZE; i++) {
        pfxPhi[i] = pfxPhi[i - 1] + phi[i];
        mert[i] = mert[i - 1] + mu[i];
    }
}

unordered_map<int, long long int> pfxPhiMp;

long long int getPfxPhi(int n) {
    if (n < SIZE)
        return pfxPhi[n];
    if (pfxPhiMp.find(n) != pfxPhiMp.end())
        return pfxPhiMp[n];
    long long int ret = 1ll * n * (n + 1) / 2;
    for (int l = 2, r; l <= n; l = r + 1) {
        if (n / l == 0)
            break;
        r = n / (n / l);
        ret -= (r - l + 1) * getPfxPhi(n / l);
    }

    pfxPhiMp[n] = ret;
    return ret;
}

unordered_map<int, int> mertMp;

int getMert(int n) {
    if (n < SIZE)
        return mert[n];
    if (mertMp.find(n) != mertMp.end())
        return mertMp[n];
    long long int ret = 1;
    for (int l = 2, r; l <= n; l = r + 1) {
        if (n / l == 0)
            break;
        r = n / (n / l);
        ret -= (r - l + 1) * getMert(n / l);
    }

    mertMp[n] = ret;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initMuPhi();
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int num; cin >> num;
        cout << getPfxPhi(num) << " " << getMert(num) << '\n';
    }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

class Frac {
public:
    long long int a, b;

    Frac operator + (const Frac & snd) {
        long long int gcd = __gcd(b, snd.b);
        return {snd.b / gcd * a + b / gcd * snd.a, b / gcd * snd.b};
    }

    Frac operator / (const long long int & snd) {
        long long int gcd = __gcd(a, snd);
        return {a / gcd, snd / gcd * b}; 
    }

    bool operator < (const Frac & snd) const {
        return a * snd.b < b * snd.a;
    }

    void print() {
        cout << a << '/' << b << '\n';
    }
};

#define SIZE 1000010

int minFac[SIZE], primeArr[SIZE], mu[SIZE], mert[SIZE], primePt;
int lim; long long int k; 

void initMu() {
    fill(minFac + 0, minFac + SIZE, 0);
    primePt = 0; mu[1] = 1;
    for (int i = 2; i < SIZE; i++) {
        if (minFac[i] == 0) {
            minFac[i] = i; mu[i] = -1;
            primeArr[primePt++] = i;
        }
        for (int j = 0; j < primePt && primeArr[j] <= min(minFac[i], (SIZE - 1) / i); j++) {
            minFac[i * primeArr[j]] = primeArr[j];
            if (minFac[i] == primeArr[j])
                mu[i * primeArr[j]] = 0;
            else
                mu[i * primeArr[j]] = -mu[i];
        }
    }

    mert[0] = 0;
    for (int i = 1; i < SIZE; i++)
        mert[i] = mert[i - 1] + mu[i];
}

long long int quasiEuclidean(long long int a, long long int b, long long int c, long long int n) {
    if (a == 0)
        return (n + 1) * (b / c);

    if (a >= c || b >= c) {
        long long int tmp = (n & 1) ? ((n + 1) >> 1) * n : (n >> 1) * (n + 1);
        return (a / c) * tmp + (b / c) * (n + 1) + quasiEuclidean(a % c, b % c, c, n);
    }
    long long int m = (a * n + b) / c;
    return n * m - quasiEuclidean(c, c - b - 1, a, m - 1);
}

long long int solve(const Frac & cnt) {
    long long int ret = 0;
    for (int l = 1, r; l <= lim; l = r + 1) {
        if (lim / l == 0)
            break;
        r = lim / (lim / l);
        ret += (mert[r] - mert[l - 1]) * quasiEuclidean(cnt.a, 0, cnt.b, lim / l);   
    }
    return ret;
}

Frac sternBrocot(const Frac & frac) {
    Frac leftPt = {0, 1}, midPt = {1, 1}, rightPt = {1, 0}, ret = {-1, -1};
    long long int x = frac.a, y = frac.b;
    while (x != y && max(midPt.a, midPt.b) <= lim) {
        if (frac < midPt)
            ret = midPt;
        if (x < y) {
            rightPt = midPt; 
            midPt = {leftPt.a + midPt.a, leftPt.b + midPt.b};
            y -= x;
        } else {
            leftPt = midPt; 
            midPt = {midPt.a + rightPt.a, midPt.b + rightPt.b};
            x -= y;
        }
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initMu();
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        cin >> lim >> k;
        Frac leftPt = {0, 1}, rightPt = {1, 1}, ans = {-1, -1};

        while (true) {
            Frac midPt = (leftPt + rightPt) / 2;
            long long int midNum = solve(midPt);

            if (midNum == k - 1) {
                ans = midPt;
                break;
            }

            if (midNum < k)
                leftPt = midPt;
            else
                rightPt = midPt;
        }

        sternBrocot(ans).print();
    }

    return 0;
}
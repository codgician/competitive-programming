#include <bits/stdc++.h>
using namespace std;

long long int a, b, p, q;

long long int quasiEuclidean(long long int a, long long int b, long long int c, long long int n) {
    if (n < 0)
        return 0;
    if (a == 0) 
        return (n + 1) * (b / c);
    
    if (a >= c || b >= c) {
        long long int tmp = ((n & 1) ? ((n + 1) >> 1) * n : (n >> 1) * (n + 1));
        return ((a / c) * tmp + (b / c) * (n + 1) + quasiEuclidean(a % c, b % c, c, n));
    }
    long long int m = (a * n + b) / c;
    return n * m - quasiEuclidean(c, c - b - 1, a, m - 1);
}

bool check(long long int delta) {
    long long int leftPt = q - delta, rightPt = q + delta;
    long long int fst = quasiEuclidean(p << 1, (q << 1) - leftPt, q << 1, b) - quasiEuclidean(p << 1, (q << 1) - leftPt, q << 1, a - 1);
    long long int snd = quasiEuclidean(p << 1, (q << 1) - rightPt - 1, q << 1, b) - quasiEuclidean(p << 1, (q << 1) - rightPt - 1, q << 1, a - 1);
    return fst - snd > 0;
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

long long int reRange(long long int x, long long int mod, long long int lim) {
    x += (lim - x) / mod * mod;
    while (x < lim)
        x += mod;
    while (x >= lim + mod)
        x -= mod;
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        cin >> a >> b >> p >> q;
        long long int leftPt = 0, rightPt = q, delta = 0;
        while (leftPt <= rightPt) {
            long long int midPt = (leftPt + rightPt) >> 1; 
            if (check(midPt)) {
                delta = midPt; rightPt = midPt - 1;
            } else {
                leftPt = midPt + 1;
            }
        }

        long long int x, y; long long int fac = p << 1, mod = q << 1;
        long long int gcd = extEuclid(p << 1, q << 1, x, y), ans = INT_MAX; 
        fac /= gcd; mod /= gcd;
        if ((q + delta) % gcd == 0) {
            long long int cnt = (q + delta) / gcd * x; 
            ans = min(ans, reRange(cnt, mod, a));
        }
        if ((q - delta) % gcd == 0) {
            long long int cnt = (q - delta) / gcd * x; 
            ans = min(ans, reRange(cnt, mod, a));
        }
        cout << ans << '\n';
    }

    return 0;
}

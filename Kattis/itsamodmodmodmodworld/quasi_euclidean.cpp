#include <bits/stdc++.h>
using namespace std;

long long int quasiEuclidean(long long int a, long long int b, long long int c, long long int n) {
    if (n < 0)
        return 0;
    if (a == 0)
        return (n + 1) * (b / c);
    if (a >= c || b >= c) {
        long long int tmp = (n & 1) ? ((n + 1) >> 1) * n : (n >> 1) * (n + 1);
        return (a / c) * tmp + (b / c) * (n + 1) + quasiEuclidean(a % c, b % c, c, n);
    }
    long long int m = (a * n + b) / c;
    return n * m - quasiEuclidean(c, c - b - 1, a, m - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        long long int p, q, n; cin >> p >> q >> n;
        long long int ans = p * ((n + 1) * n / 2);
        ans -= q * quasiEuclidean(p, 0, q, n);
        cout << ans << '\n';
    }

    return 0;
}
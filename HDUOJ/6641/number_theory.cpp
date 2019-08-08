#include <bits/stdc++.h>
using namespace std;

long long int k; int m; 

bool check(long long int n, int t) {
    if (n == 1)
        return t == m + 1;
    if (m == 1 && t == 1)
        return true;
    if (__gcd(n, 1ll * t) != 1)
        return false;
    int cnt = 1;
    for (long long int i = 2; i < t; i++) {
        if (__gcd(n, i) != 1)
            continue;
        cnt++;
        if (cnt >= m)
            return false;
    }
    return cnt == m - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        long long int ans = LLONG_MAX;
        cin >> k >> m;
        for (int t = 1; t <= 400; t++) {
            long long int n = k ^ t;
            if (check(n, t)) {
                ans = min(ans, n);
            }
        }
        cout << (ans == LLONG_MAX ? -1 : ans) << '\n';
    }

    return 0;
}
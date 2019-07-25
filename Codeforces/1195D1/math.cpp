#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

long long int work(int num, int which) {
    long long int ret = 0, fac = which == 0 ? 1 : 10;
    while (num > 0) {
        int cnt = num % 10;
        ret = (ret + cnt * fac) % mod;
        fac = fac * 100 % mod;
        num /= 10;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int len; cin >> len;
    long long int ans = 0;
    for (int i = 0; i < len; i++) {
        int cnt; cin >> cnt;
        ans = (ans + work(cnt, 0) * len % mod) % mod;
        ans = (ans + work(cnt, 1) * len % mod) % mod;
    }
    cout << ans << '\n';
    return 0;
}
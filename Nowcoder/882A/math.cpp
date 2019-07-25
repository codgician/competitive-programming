#include <bits/stdc++.h>
using namespace std;
 
const int mod = 1e9 + 7;
long long int ans;
 
long long int fastPow(long long int a, long long int n) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod; n >>= 1;
    }
    return ret;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int caseNum; cin >> caseNum; ans = 1;
    while (caseNum--) {
        long long int len, endPt; cin >> len >> endPt;
        if (endPt == 0) {
            ans = ans * (len == 1 ? 1 : 0);
            cout << ans << '\n';
            continue;
        }
        len--; ans = ans * fastPow(len, mod - 2) % mod;
        cout << ans << '\n';
    }
 
    return 0;
}
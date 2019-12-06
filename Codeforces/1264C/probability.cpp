#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 200010
const int mod = 998244353;
 
long long int prob[SIZE], sfx[SIZE], invSfx[SIZE], invSfxSum[SIZE];
 
long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = ret * a % mod;
        a = a * a % mod; n >>= 1;
    }
    return ret;
}
 
long long int rangeExpt(int qLeftPt, int qRightPt) {
    return (invSfxSum[qLeftPt] - invSfxSum[qRightPt + 1]) * sfx[qRightPt + 1] % mod;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int len, qNum, inv = fastPow(100, mod - 2, mod); 
    cin >> len >> qNum;
    for (int i = 0; i < len; i++)
        cin >> prob[i], prob[i] = prob[i] * inv % mod;
    sfx[len] = 1;
    for (int i = len - 1; i >= 0; i--)
        sfx[i] = sfx[i + 1] * prob[i] % mod;
    invSfx[len] = 1, invSfxSum[len] = 1;
    invSfx[0] = fastPow(sfx[0], mod - 2, mod);
    for (int i = 1; i <= len; i++)
        invSfx[i] = invSfx[i - 1] * prob[i - 1] % mod;
    for (int i = len - 1; i >= 0; i--)
        invSfxSum[i] = (invSfxSum[i + 1] + invSfx[i]) % mod;
 
    set<int> st; st.insert({0, len});    
    long long int ans = rangeExpt(0, len - 1);
    for (int i = 0; i < qNum; i++) {
        int cntPt; cin >> cntPt; cntPt--;
        auto it = st.find(cntPt);
        if (it != st.end()) {
            // Add checkpoint
            ans -= rangeExpt(*prev(it), *it - 1) + rangeExpt(*it, *next(it) - 1);
            ans += rangeExpt(*prev(it), *next(it) - 1);
            st.erase(it);
        } else {
            // Remove checkpoint
            it = st.insert(cntPt).first;
            ans -= rangeExpt(*prev(it), *next(it) - 1);
            ans += rangeExpt(*prev(it), *it - 1) + rangeExpt(*it, *next(it) - 1);
        }
 
        ans = (ans % mod + mod) % mod;
        cout << ans << '\n';
    }
 
    return 0;
}
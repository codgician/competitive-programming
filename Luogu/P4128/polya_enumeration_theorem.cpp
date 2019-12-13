#include <bits/stdc++.h>
using namespace std;

#define SIZE 60

long long int factls[SIZE], invFactls[SIZE];
int num, col, mod;

long long int fastPow(long long int a, long long int n, int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = ret * a % mod;
        a = a * a % mod; n >>= 1;
    }
    return ret;
}

void initFactls() {
    factls[0] = 1; int lim = min(num + 1, mod);
    for (int i = 1; i < lim; i++)
        factls[i] = factls[i - 1] * i % mod;
    invFactls[lim - 1] = fastPow(factls[lim - 1], mod - 2, mod);
    for (int i = lim - 2; i >= 0; i--)
        invFactls[i] = invFactls[i + 1] * (i + 1) % mod;
}

long long int ans;
vector<pair<int, int> > vec;
void dfs(int rem, int lb) {
    if (rem == 0) {
        long long int cycNum = 0, permuNum = factls[num]; int siz = vec.size();
        // For every cycle
        for (const auto & p : vec)
            cycNum = (cycNum + p.second * (p.first / 2)) % (mod - 1);
        // Between different cycles
        for (int i = 0; i < siz; i++) {
            const auto & p1 = vec[i];
            cycNum = (cycNum + (1ll * (p1.second - 1) * p1.second / 2) % (mod - 1) *  p1.first) % (mod - 1);
            for (int j = i + 1; j < siz; j++) {
                const auto & p2 = vec[j];
                cycNum = (cycNum + __gcd(p1.first, p2.first) * p1.second % (mod - 1) * p2.second) % (mod - 1);
            }
        }
        for (const auto & p : vec)
            permuNum = permuNum * invFactls[p.second] % mod * fastPow(fastPow(p.first, p.second, mod), mod - 2, mod) % mod;
        ans = (ans + permuNum * fastPow(col, cycNum, mod)) % mod; 
        return;
    }

    for (int i = lb; i <= rem; i++) {
        for (int j = 1; i * j <= rem; j++) {
            if (i * j != rem && rem - i * j <= i)
                continue;
            vec.push_back(make_pair(i, j));
            dfs(rem - i * j, i + 1);
            vec.pop_back();
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> num >> col >> mod;
    initFactls(); ans = 0; vec.clear();
    dfs(num, 1);
    ans = ans * invFactls[num] % mod;
    cout << ans << '\n';

    return 0;
}
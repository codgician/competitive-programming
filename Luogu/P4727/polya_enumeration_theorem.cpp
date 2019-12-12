#include <bits/stdc++.h>
using namespace std;

#define SIZE 997
const int mod = 997;

int factls[SIZE], num;
long long int invs[SIZE];

void initFactls() {
    factls[0] = 1;
    for (int i = 1; i < SIZE; i++)
        factls[i] = factls[i - 1] * i % mod;
}

void initInv() {
    invs[1] = 1;
    for (int i = 2; i < SIZE; i++)
        invs[i] = (mod - mod / i) * invs[mod % i] % mod;
}

int fastPow(int a, int n, int mod) {
    int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = ret * a % mod;
        a = a * a % mod; n >>= 1;
    }
    return ret;
}

int ans = 0;
vector<pair<int, int> > vec;
void dfs(int rem, int lb) {
    if (rem == 0) {
        int cycNum = 0, permuNum = factls[num], siz = vec.size();
        // For every cycle
        for (const auto & p : vec)
            cycNum = (cycNum + p.second * (p.first / 2)) % (mod - 1);
        // Between different cycles
        for (int i = 0; i < siz; i++) {
            const auto & p1 = vec[i];
            cycNum = (cycNum + p1.first * (p1.second - 1) * p1.second / 2) % (mod - 1);
            for (int j = i + 1; j < siz; j++) {
                const auto & p2 = vec[j];
                cycNum = (cycNum + __gcd(p1.first, p2.first) * p1.second * p2.second) % (mod - 1);
            }
        }
        for (const auto & p : vec)
            permuNum = permuNum * invs[factls[p.second]] * invs[fastPow(p.first, p.second, mod)] % mod;
        ans = (ans + permuNum * fastPow(2, cycNum, mod)) % mod; 
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

    initFactls(); initInv(); cin >> num;
    ans = 0; vec.clear();
    dfs(num, 1);
    ans = ans * invs[factls[num]] % mod;
    cout << ans << '\n';

    return 0;
}
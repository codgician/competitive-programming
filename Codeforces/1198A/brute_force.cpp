#include <bits/stdc++.h>
using namespace std;

map<int, int> mp;
vector<int> vec;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; long long int lim; cin >> len >> lim; lim <<= 3;
    for (int i = 0; i < len; i++) {
        int cnt; cin >> cnt;
        mp[cnt]++;
    }

    vec.push_back(0);
    for (const auto & p : mp)
        vec.push_back(p.second);
    int siz = vec.size();
    for (int i = 1; i < siz; i++)
        vec[i] += vec[i - 1];

    if (1ll * len * ceil(log2(mp.size())) <= lim) {
        cout << 0 << '\n';
        return 0;
    }

    int tgt = 1 << (lim / len), ans = 0;
    for (int i = 0; i + tgt < siz; i++)
        ans = max(ans, vec[i + tgt] - vec[i]);
    cout << len - ans << '\n';

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define SIZE 2010

int arr[2][SIZE];
vector<pair<int, int> > v[2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int len, mod; cin >> len >> mod;
    for (int t = 0; t < 2; t++) {
        for (int i = 0; i < len; i++)
            cin >> arr[t][i];
        sort(arr[t] + 0, arr[t] + len);
        v[t].push_back(make_pair(arr[t][0], 1));
        for (int i = 1; i < len; i++) {
            if (arr[t][i] == v[t].back().first) {
                v[t].back().second++;
            } else {
                v[t].push_back(make_pair(arr[t][i], 1));
            }
        }
    }

    const auto solve = [mod]() {
        int siz = v[0].size(); int ret = INT_MAX;
        for (int i = 0; i < siz; i++) {
            if (v[0][0].second != v[1][i].second)
                continue;
            int delta = (v[1][i].first - v[0][0].first + mod) % mod; bool flag = true;
            for (int j = 1; j < siz && flag; j++) {
                const auto & p1 = v[0][j], & p2 = v[1][(i + j) % siz];
                if (p1.second != p2.second || (p2.first - p1.first + mod) % mod != delta)
                    flag = false;
            }
            if (flag)
                ret = min(ret, delta);
        }
        return ret;
    };

    cout << solve() << '\n';
    return 0;
}

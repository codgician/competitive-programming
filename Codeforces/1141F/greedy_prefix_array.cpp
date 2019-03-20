#include <bits/stdc++.h>
using namespace std;

#define SIZE 1510

int pfx[SIZE];
map<int, vector<pair<int, int> > > mp;
vector<pair<int, int> > ans, cnt;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len;
    cin >> len;
    pfx[0] = 0;
    for (int i = 1; i <= len; i++) {
        cin >> pfx[i];
        pfx[i] += pfx[i - 1];
    }

    for (int i = 1; i <= len; i++) {
        for (int j = i; j <= len; j++) {
            int val = pfx[j] - pfx[i - 1];
            mp[val].push_back(make_pair(i, j));
        }
    }

    for (auto p : mp) {
        sort(p.second.begin(), p.second.end(), [](auto fst, auto snd) {
            return fst.second < snd.second;
        });
        cnt.clear();

        for (auto i : p.second)
            if (cnt.empty() || i.first > cnt.back().second)
                cnt.push_back(i);
        if (cnt.size() > ans.size())
            ans = cnt;
    }

    cout << ans.size() << endl;
    for (auto i : ans)
        cout << i.first << " " << i.second << endl;

    return 0;
}
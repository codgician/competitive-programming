#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; cin >> len;
    vector<pair<int, int> > v;
    for (int i = 0; i < len; i++) {
        int b; cin >> b;
        v.push_back(make_pair(b - i, b));
    }

    sort(v.begin(), v.end());
        
    int cntPt = 0; long long int cnt = v[0].second, ans = 0;
    for (int i = 1; i < (int)v.size(); i++) {
        if (v[cntPt].first == v[i].first) {
            cnt += v[i].second;
        } else {
            ans = max(ans, cnt);
            cntPt = i, cnt = v[i].second;
        }
    }

    ans = max(ans, cnt);
    cout << ans << '\n';

    return 0;
}
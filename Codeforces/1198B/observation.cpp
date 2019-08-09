#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

vector<pair<int, int> > que;
int ans[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; cin >> len;
    for (int i = 0; i < len; i++) {
        int val; cin >> val; ans[i] = -1;
        que.push_back(make_pair(i, val));
    }

    int qNum; cin >> qNum;
    for (int i = 0; i < qNum; i++) {
        int op; cin >> op;
        if (op == 1) {
            int pt, val; cin >> pt >> val;
            que.push_back(make_pair(pt - 1, val));
        } else {
            int val; cin >> val;
            que.push_back(make_pair(-1, val));
        }
    }

    int global = 0;
    for (auto it = que.rbegin(); it != que.rend(); ++it) {
        const auto & p = *it;
        if (p.first == -1)
            global = max(global, p.second);
        else if (ans[p.first] == -1)
            ans[p.first] = max(global, p.second);
    }

    for (int i = 0; i < len; i++)
        cout << ans[i] << ' ';
    cout << '\n';
    return 0;
}
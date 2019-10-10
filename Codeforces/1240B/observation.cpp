#include <bits/stdc++.h>
using namespace std;

#define SIZE 300010

int arr[SIZE];
pair<int, int> pos[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int qNum; cin >> qNum;
    while (qNum--) {
        int len, ans = 0; cin >> len;
        fill(pos + 1, pos + len + 1, make_pair(INT_MAX, -1));
        for (int i = 0; i < len; i++) {
            cin >> arr[i]; ans += (pos[arr[i]].second == -1);
            pos[arr[i]].first = min(pos[arr[i]].first, i);
            pos[arr[i]].second = max(pos[arr[i]].second, i);
        }

        int ret = 0, cnt = 0, prev = -1;
        for (int i = 1; i <= len; i++) {
            if (pos[i].second == -1)
                continue;
            if (pos[i].first > prev) {
                cnt++;
            } else {
                ret = max(ret, cnt); cnt = 1;
            }
            prev = pos[i].second;
        }
        
        ret = max(ret, cnt);
        cout << ans - ret << '\n';
    }

    return 0;
}
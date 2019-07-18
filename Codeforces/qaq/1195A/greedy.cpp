#include <bits/stdc++.h>
using namespace std;

map<int, int> mp;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len, num; cin >> len >> num;
    int selectNum = (len + 1) >> 1;
    for (int i = 0; i < len; i++) {
        int cnt; cin >> cnt;
        mp[cnt]++;
    }

    int ans = 0;
    for (auto & p : mp) {
        if (p.second >= 2) {
            int canTake = min(selectNum, p.second >> 1);
            selectNum -= canTake;
            p.second -= canTake * 2;
            ans += canTake * 2;
            if (selectNum == 0)
                break;
        }
    }

    if (selectNum > 0) {
        for (auto & p : mp) {
            if (p.second == 1) {
                ans++; selectNum--;
                p.second = 0;
                if (selectNum == 0)
                    break;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
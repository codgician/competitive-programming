#include <bits/stdc++.h>
using namespace std;

int arr[10];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int len; cin >> len;
        map<int, int> mp;
        for (int i = 0; i < len; i++)
            cin >> arr[i], mp[arr[i]]++;
        int ret = 0;
        for (const auto & p : mp)
            ret += p.second - 1;
        cout << ret << '\n';
        for (int i = 0; i < len; i++) {
            if (mp[arr[i]] > 1) {
                mp[arr[i]]--;
                for (int t = 1; t <= 1000; t *= 10) {
                    bool flag = false; int cntBit = (arr[i] / t) % 10;
                    int cnt = arr[i] - cntBit * t;
                    for (int j = 0; j <= 9; j++) {
                        if (j == cntBit)
                            continue;
                        int nxt = cnt + j * t;
                        if (mp.find(nxt) == mp.end()) {
                            mp[nxt] = 1; arr[i] = nxt;
                            flag = true; break;
                        }
                    }
                    if (flag)
                        break;
                }
            }
            cout << setw(4) << setfill('0') << arr[i] << '\n';
        }
    }

    return 0;
}
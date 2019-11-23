#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

vector<int> pos[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int len; cin >> len;
        for (int i = 1; i <= len; i++)
            pos[i].clear();
        for (int i = 0; i < len; i++) {
            int cnt; cin >> cnt;
            pos[cnt].push_back(i);
        }

        int ans = INT_MAX;
        for (int i = 1; i <= len; i++) {
            int siz = pos[i].size();
            if (siz <= 1)
                continue;
            for (int j = 0; j < siz - 1; j++)
                ans = min(ans, pos[i][j + 1] - pos[i][j] + 1);
        }
        cout << (ans == INT_MAX ? -1 : ans) << '\n';
    }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

int pos[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int len; cin >> len;
        for (int i = 0; i < len; i++) {
            int cnt; cin >> cnt;
            pos[cnt] = i;
        }

        cout << 1;
        int minv = pos[1], maxv = pos[1];
        for (int i = 2; i <= len; i++) {
            minv = min(minv, pos[i]);
            maxv = max(maxv, pos[i]);
            cout << (maxv - minv + 1 == i);
        }
        cout << '\n';
    }

    return 0;
}
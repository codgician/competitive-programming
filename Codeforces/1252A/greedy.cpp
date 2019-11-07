#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; cin >> len;
    for (int i = 0; i < len; i++) {
        int cnt; cin >> cnt;
        cout << len + 1 - cnt << ' ';
    }

    return 0;
}
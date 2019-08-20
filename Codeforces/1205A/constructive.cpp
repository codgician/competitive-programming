#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; cin >> len;
    if (!(len & 1)) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    int cnt = 1, flag = 1;
    for (int i = 0; i < len; i++) {
        cout << cnt << ' ';
        cnt += (flag << 1) + 1;
        flag ^= 1;
    }
    cnt = 2, flag = 0;
    for (int i = 0; i < len; i++) {
        cout << cnt << ' ';
        cnt += (flag << 1) + 1;
        flag ^= 1;
    }
    cout << '\n';

    return 0;
}
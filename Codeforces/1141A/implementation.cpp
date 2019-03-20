#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    if (m < n || m % n > 0) {
        cout << -1 << endl;
        return 0;
    }
    if (m == n) {
        cout << 0 << endl;
        return 0;
    }

    m /= n;
    int ans = 0;
    while (m > 1 && m % 2 == 0) {
        ans++;
        m /= 2;
    }
    while (m > 1 && m % 3 == 0) {
        ans++;
        m /= 3;
    }

    if (m > 1) {
        cout << -1 << endl;
        return 0;
    }
    cout << ans << endl;

    return 0;
}
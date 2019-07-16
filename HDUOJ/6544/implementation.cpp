#include <bits/stdc++.h>
using namespace std;

double para(int num) {
    if (num < 100)
        return 1.0;
    if (num < 150)
        return 0.8;
    if (num < 400)
        return 0.5;
    return 1.0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int num;
    while (cin >> num) {
        double ans = 0;
        while (num--) {
            int cnt; cin >> cnt;
            ans += para(ans) * cnt;
        }
        cout << fixed << setprecision(2) << ans << '\n';
    }

    return 0;
}
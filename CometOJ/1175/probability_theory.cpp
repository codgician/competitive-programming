#include <bits/stdc++.h>
using namespace std;

long double l, r, L, R;

long double calc(long double p) {
    long double Eq = (L + R) / 2;
    return (p - l) * (Eq - p) / (r - l);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> l >> r >> L >> R;

    long double Eq = (L + R) / 2, ans = 0;

    if ((Eq + l) / 2 <= r && (Eq + l) / 2 >= l)
        ans = max(ans, calc((Eq + l) / 2));
    ans = max(ans, calc(r));
    ans = max((long double)0, ans);
    cout << fixed << setprecision(4) << ans << endl;

    return 0;
}
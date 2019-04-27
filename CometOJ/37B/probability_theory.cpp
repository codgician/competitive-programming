#include <bits/stdc++.h>
using namespace std;

long double l, r, L, R, Eq, ans;

long double calc(long double p) {
    return (p - l) * (Eq - p) / (r - l);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ans = 0;
    cin >> l >> r >> L >> R;

    Eq = (L + R) / 2;
    if ((Eq + l) / 2 >= l && (Eq + l) / 2 <= r)
        ans = max(ans, calc((Eq + l) / 2));
    ans = max(ans, calc(r));
    cout << fixed << setprecision(4) << ans << endl;

    return 0;
}



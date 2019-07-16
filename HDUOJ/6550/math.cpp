#include <bits/stdc++.h>
using namespace std;

const long double pi = acos(-1.0);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    while (cin >> n) {
        long double alpha = 2 * pi / n;
        long double ans = (sin(alpha) * (n - 1) + sqrt(2 - 2 * cos(alpha))) / 2;
        cout << fixed << setprecision(6) << ans << '\n';
    }

    return 0;
}
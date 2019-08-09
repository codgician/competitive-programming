#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    double h, l; cin >> h >> l;
    cout << fixed << setprecision(12) << (pow(l, 2) - pow(h, 2)) / (2 * h) << '\n';

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;
double a, b, c, d;

double f(double x) {
    return (c * x + d) / (a * x + b);
}

double simpson(double l, double r) {
    double mid = (l + r) / 2;
    return (r - l) / 6 * (f(l) + 4 * f(mid) + f(r));
}

double adaptiveSimpson(double l, double r, double sp) {
    double mid = (l + r) / 2;
    double lsp = simpson(l, mid), rsp = simpson(mid, r);
    if (abs(sp - lsp - rsp) < eps)
        return lsp + rsp;
    return adaptiveSimpson(l, mid, lsp) + adaptiveSimpson(mid, r, rsp);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    double l, r; cin >> a >> b >> c >> d >> l >> r;
    cout << fixed << setprecision(6) << adaptiveSimpson(l, r, simpson(l, r)) << '\n';
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-7;
double a, b;

double f(double x) {
    return sqrt(a * a - x * x) * b / a;
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

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        double l, r; cin >> a >> b >> l >> r;
        cout << fixed << setprecision(3) << 2 * adaptiveSimpson(l, r, simpson(l, r)) << '\n';
    }

    return 0;
}
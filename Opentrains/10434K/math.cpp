#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);

int main() {
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        double alpha, phi; int h, m, s;
        scanf("%lf %lf", &alpha, &phi);
        scanf("%d:%d:%d", &h, &m, &s);

        if (phi >= alpha) {
            h = (h + 6) % 24;
            printf("%02d:%02d:%02d\n", h, m, s);
            continue;
        }

        alpha = alpha * pi / 180; phi = phi * pi / 180;
        double qaq = asin(tan(phi) / tan(alpha)) / (2 * pi);
        int ans = 24 * 3600 * qaq;

        h += ans / 3600; ans %= 3600;
        m += ans / 60; ans %= 60;
        s += ans;
        m += s / 60; s %= 60;
        h += m / 60; m %= 60;
        h %= 24;

        printf("%02d:%02d:%02d\n", h, m, s);
    }

    return 0;
}
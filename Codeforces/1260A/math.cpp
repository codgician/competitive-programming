#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int lim, sum; cin >> lim >> sum;
        int avg = sum / lim, md = sum % lim;
        cout << 1ll * md * (avg + 1) * (avg + 1) + 1ll * (lim - md) * avg * avg << '\n';
    }

    return 0;
}
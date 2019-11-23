#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int x, y; cin >> x >> y;
        const auto check = [x, y]() {
            if (x >= y)
                return true;
            if (x <= 3 && y > 3)
                return false;
            if (x <= 1 && y > 1)
                return false;
            return true;
        };
        cout << (check() ? "Yes" : "No") << '\n';
    }

    return 0;
}
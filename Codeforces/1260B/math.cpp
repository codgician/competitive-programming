#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        long long int a, b; cin >> a >> b;
        const auto check = [](long long int a, long long int b) {
            if ((a + b) % 3 != 0 || a + b < 0)
                return false;
            long long int sum = (a + b) / 3;
            long long int d1 = b - a;
            long long int x1 = sum + d1;
            if (x1 < 0 || x1 & 1)
                return false;
            x1 >>= 1;
            if (sum - x1 < 0)
                return false;
            return true;
        };
        cout << (check(a, b) || check(b, a) ? "YES\n" : "NO\n");
    }

    return 0;
}
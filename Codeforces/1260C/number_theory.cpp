#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        long long int r, b, k; cin >> r >> b >> k;
        if (r > b) swap(r, b);
        const auto check = [r, b, k]() {
            long long int gcd = __gcd(r, b);
            long long int mn = r - ((r / gcd - 1) * gcd + 1);
            const auto ceil = [](long long int x, long long int y) {
                return x / y + (x % y > 0);
            };
            return ceil(b - 1 - mn, r) >= k; 
        };
        cout << (check() ? "REBEL\n" : "OBEY\n");        
    }
    return 0;
}

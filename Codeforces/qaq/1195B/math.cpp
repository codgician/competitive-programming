#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    long long int n, k; cin >> n >> k;
    long long int delta2 = 9 + 8 * (n + k);
    long long int deltaSqrt = max(0ll, (long long int)sqrt(delta2) - 1);
    while (deltaSqrt * deltaSqrt < delta2)
        deltaSqrt++;

    long long int y = (deltaSqrt - 3) / 2;
    long long int x = n - y; cout << x << '\n';

    return 0;
}
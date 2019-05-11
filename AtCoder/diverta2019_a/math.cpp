#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    long long int n, k;
    cin >> n >> k;
    cout << max(0ll, n - k + 1) << '\n';
    return 0;
}

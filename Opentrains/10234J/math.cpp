#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    long long int num; cin >> num;
    long long int ans = num * (num + 1) / 2;
    for (long long int i = 1; i <= num; i <<= 1) {
        long long int j = min(num + 1, i << 1);
        ans -= i * (j - i);
    }

    cout << ans << '\n';
    return 0;
}
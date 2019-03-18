#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    long long int n, k ,t;
    while (cin >> n >> k >> t) {
        long long int ans = n - k * t;
        if (ans < 0)
            ans = 0;
        cout << ans << endl;
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; cin >> len;
    cout << ((len & 1) ? 0 : (1ll << (len >> 1))) << '\n';
    return 0;
}
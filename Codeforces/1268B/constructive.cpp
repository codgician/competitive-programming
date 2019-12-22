#include <bits/stdc++.h>
using namespace std;

#define SIZE 300010

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; cin >> len;
    long long int ans[2] = {0, 0};
    for (int i = 0; i < len; i++) {
        int cnt; cin >> cnt;
        ans[i & 1] += cnt >> 1;
        ans[(i & 1) ^ 1] += (cnt + 1) >> 1;
    }
    cout << min(ans[0], ans[1]) << '\n';
    return 0;
}

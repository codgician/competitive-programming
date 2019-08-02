#include <bits/stdc++.h>
using namespace std;

#define SIZE (1 << 26)

int arr[26];
char dp[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int vertexNum, edgeNum; cin >> vertexNum >> edgeNum;
    fill(arr + 0, arr + vertexNum, 0);
    fill(dp + 0, dp + (1 << vertexNum), 0);

    for (int i = 0; i < edgeNum; i++) {
        int from, to; cin >> from >> to;
        arr[from] |= 1 << to;
        arr[to] |= 1 << from;
    }

    for (int i = 0; i < vertexNum; i++) {
        arr[i] |= (1 << i); arr[i] = ~arr[i];
    }

    int pt = 0, ans = 0;
    for (int st = 1; st < (1 << vertexNum); st++) {
        while (!(st & (1 << pt)))
            pt++;
        dp[st] = max(dp[st ^ (1 << pt)], (short)(dp[st & arr[pt]] + 1));
        ans += dp[st];
    }

    cout << ans << '\n';
    return 0;
}

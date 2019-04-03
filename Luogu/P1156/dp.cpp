#include <bits/stdc++.h>
using namespace std;

#define SIZE 1010

typedef struct _Node {
    int time, height, life;
} Node;
Node arr[SIZE];
int dp[SIZE][SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len, num;
    cin >> len >> num;
    for (int i = 1; i <= num; i++)
        cin >> arr[i].time >> arr[i].life >> arr[i].height;
    sort(arr + 1, arr + num + 1, [](const Node & fst, const Node & snd) {
        return fst.time < snd.time;
    });
    arr[0].time = 0;

    int ans = 0;
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 10;
    for (int i = 0; i < num; i++) {
        int span = arr[i + 1].time - arr[i].time;
        for (int j = 0; j <= len; j++) {
            if (dp[i][j] < span)
                continue;
            if (j + arr[i + 1].height >= len) {
                cout << arr[i + 1].time << endl;
                return 0;
            }
            dp[i + 1][j + arr[i + 1].height] = max(dp[i + 1][j + arr[i + 1].height], dp[i][j] - span);
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + arr[i + 1].life - span);
        }
        if (dp[i][0] != -1) {
            ans = max(ans, dp[i][0] + arr[i].time);
        }
    }
    if (dp[num][0] != -1)
        ans = max(ans, dp[num][0] + arr[num].time);

    cout << ans << endl;

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define SIZE 210

pair<int, int> arr[SIZE];
int dp[SIZE][SIZE * SIZE], pfxSum[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int num;
    cin >> num;
    for (int i = 1; i <= num; i++)
        cin >> arr[i].first >> arr[i].second;
    sort(arr + 1, arr + num + 1, [](pair<int, int> & fst, pair<int, int> & snd) {
        return fst.second > snd.second;
    });

    pfxSum[0] = 0;
    for (int i = 1; i <= num; i++)
        pfxSum[i] = pfxSum[i - 1] + arr[i].first;

    for (int i = 0; i <= num; i++)
        for (int j = 0; j <= pfxSum[num]; j++)
            dp[i][j] = INT_MAX;
    dp[0][0] = 0;

    for (int i = 0; i < num; i++) {
        for (int j = 0; j <= pfxSum[num]; j++) {
            if (dp[i][j] == INT_MAX)
                continue;
            int queueTime = arr[i + 1].first, dineTime = arr[i + 1].second;
            dp[i + 1][j + queueTime] = min(dp[i + 1][j + queueTime], max(dp[i][j], j + queueTime + dineTime));
            dp[i + 1][j] = min(dp[i + 1][j], max(dp[i][j], pfxSum[i] - j + queueTime + dineTime));
        }
    }

    int ans = INT_MAX;
    for (int j = 0; j <= pfxSum[num]; j++)
        ans = min(ans, dp[num][j]);
    cout << ans << endl;

    return 0;
}
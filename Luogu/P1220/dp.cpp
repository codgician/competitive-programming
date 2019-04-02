#include <bits/stdc++.h>
using namespace std;

#define SIZE 55

pair<int, int> arr[SIZE];
int pfxSum[SIZE], num;
long long int dp[SIZE][SIZE][2];

int dist(int qLeftPt, int qRightPt) {
    return arr[qRightPt].first - arr[qLeftPt].first;
}

int except(int qLeftPt, int qRightPt) {
    return pfxSum[num] - (pfxSum[qRightPt] - pfxSum[qLeftPt - 1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int pt;
    cin >> num >> pt;
    pfxSum[0] = 0;
    for (int i = 1; i <= num; i++) {
        cin >> arr[i].first >> arr[i].second;
        pfxSum[i] = pfxSum[i - 1] + arr[i].second;
    }

    for (int i = 0; i <= num; i++)
        for (int j = 0; j <= num; j++)
            dp[i][j][0] = INT_MAX, dp[i][j][1] = INT_MAX;
    dp[pt][pt][0] = 0, dp[pt][pt][1] = 0;

    for (int l = 2; l <= num; l++) {
        for (int i = 1; i <= num; i++) {
            int j = i + l - 1;
            dp[i][j][0] = min(dp[i][j][0], dp[i + 1][j][0] + dist(i, i + 1) * except(i + 1, j));
            dp[i][j][0] = min(dp[i][j][0], dp[i + 1][j][1] + dist(i, j) * except(i + 1, j));

            dp[i][j][1] = min(dp[i][j][1], dp[i][j - 1][1] + dist(j - 1, j) * except(i, j - 1));
            dp[i][j][1] = min(dp[i][j][1], dp[i][j - 1][0] + dist(i, j) * except(i, j - 1));

        }
    }

    cout << min(dp[1][num][0], dp[1][num][1]) << endl;
    return 0;
}
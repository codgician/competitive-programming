#include <bits/stdc++.h>
using namespace std;

#define SIZE 1010

int cost[SIZE], pfx[SIZE][SIZE];
int dp[SIZE], add[SIZE];
deque<pair<int, int> > mdq[SIZE];
int len, tim, lim;

int subMod(int a, int b) {
    return ((a - b) % len + len) % len;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> len >> tim >> lim;

    for(int j = 0; j < len; j++)
        for(int i = 1; i <= tim; i++)
            cin >> pfx[i][j];
    for(int i = 2; i <= tim; i++)
        for(int j = 0; j < len; j++)
            pfx[i][j] += pfx[i - 1][subMod(j, 1)];
    for (int j = 0; j < len; j++) {
        cin >> cost[j];
        mdq[j].push_back(make_pair(-cost[j], 0));
    }

    for (int i = 1; i <= tim; i++)
        dp[i] = INT_MIN;
    dp[0] = 0;
    for (int i = 1; i <= tim; i++) {
        for (int j = 0; j < len; j++) {
            int qId = subMod(j, i);
            if (mdq[qId].empty())
                continue;
            dp[i] = max(dp[i], mdq[qId].front().first + pfx[i][subMod(j, 1)]);
        }
        for (int j = 0; j < len; j++) {
            int qId = subMod(j, i);
            while (!mdq[qId].empty() && mdq[qId].front().second + lim <= i)
                mdq[qId].pop_front();
            int f = dp[i] - pfx[i][subMod(j, 1)] - cost[j];
            while (!mdq[qId].empty() && mdq[qId].back().first <= f)
                mdq[qId].pop_back();
            mdq[qId].push_back(make_pair(f, i));
        }
    }
    cout << dp[tim] << endl;
    return 0;
}
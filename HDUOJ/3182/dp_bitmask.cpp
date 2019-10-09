#include <bits/stdc++.h>
using namespace std;

#define SIZE 16
#define BAG_SIZE 101
#define STATE_SIZE (1 << 16)

int dp[STATE_SIZE];
int val[SIZE], cost[SIZE], lim[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        int num, bagSiz;
        cin >> num >> bagSiz;
        for (int i = 0; i < num; i++)
            cin >> val[i];
        for (int i = 0; i < num; i++)
            cin >> cost[i];
        for (int i = 0; i < num; i++) {
            int limNum;
            cin >> limNum;
            lim[i] = 0;
            for (int j = 0; j < limNum; j++) {
                int cnt;
                cin >> cnt;
                cnt--;
                lim[i] |= (1 << cnt);
            }
        }

        int ans = 0;
        memset(dp, -1, sizeof(dp));
        dp[0] = 0;
        for (int st = 0; st < (1 << num); st++) {
            int baseCost = 0, baseValue = 0;
            for (int i = 0; i < num; i++) {
                if (!(st & (1 << i)))
                    continue;
                if ((st & lim[i]) != lim[i]) {
                    baseCost = INT_MAX;
                    break;
                }
                baseCost += cost[i];
                baseValue += val[i];
            }

            if (baseCost > bagSiz)
                continue;

            for (int i = 0; i < num; i++) {
                if (!(st & (1 << i)) && dp[st] != -1) {
                    if ((lim[i] & st) == lim[i] && baseCost + cost[i] <= bagSiz) {
                        dp[st | (1 << i)] = max(dp[st | (1 << i)], dp[st] + val[i]);
                    }
                }
            }

            ans = max(ans, dp[st]);
        }

        cout << ans << endl;
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define SIZE 17
#define STATE_SIZE (1 << 17)

long long int dp[STATE_SIZE][SIZE];
int val[SIZE], lim[SIZE];
vector<int> vec;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++) {
        int num;
        cin >> num;
        vec.clear();
        memset(lim, -1, sizeof(lim));
        for (int i = 0; i < num; i++) {
            int pos;
            cin >> val[i] >> pos;
            if (pos == -1)
                vec.push_back(i);
            else
                lim[pos] = i;
        }

        for (int st = 0; st < (1 << num); st++)
            for (int i = 0; i < num; i++)
                dp[st][i] = LLONG_MIN;

        if (lim[0] == -1) {
            for (auto i : vec)
                dp[1 << i][i] = 0;
        } else {
            dp[1 << lim[0]][lim[0]] = 0;
        }

        for (int st = 1; st < (1 << num) - 1; st++) {
            int nextPt = 0, tmp = st;
            while (tmp > 0) {
                if (tmp & 1)
                    nextPt++;
                tmp >>= 1;
            }

            if (lim[nextPt] == -1) {
                for (int i = 0; i < num; i++) {
                    if (dp[st][i] == LLONG_MIN)
                        continue;
                    for (auto j : vec) {
                        if (st & (1 << j))
                            continue;
                        dp[st | (1 << j)][j] = max(dp[st | (1 << j)][j], dp[st][i] + 1ll * val[i] * val[j]);
                    }
                }
            } else {
                if (st & (1 << lim[nextPt]))
                    continue;
                for (int i = 0; i < num; i++) {
                    if (dp[st][i] == LLONG_MIN)
                        continue;
                    dp[st | (1 << lim[nextPt])][lim[nextPt]] = max(dp[st | (1 << lim[nextPt])][lim[nextPt]], dp[st][i] + 1ll * val[i] * val[lim[nextPt]]);
                }
            }
        }

        long long int ans = LLONG_MIN;
        for (int i = 0; i < num; i++)
            ans = max(ans, dp[(1 << num) - 1][i]);

        cout << "Case #" << t << ":\n" << ans << "\n";
    }
    return 0;
}
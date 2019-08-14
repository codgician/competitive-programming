#include <bits/stdc++.h>
using namespace std;

#define SIZE 62

const int mod = 1e9 + 7;

bitset<SIZE> bst[4];
long long int arr[4], dp[SIZE][16][5][5];

long long int dfs(int pos, int st, int cond1, int cond2) {
    if (pos < 0)
        return cond1 > 0 && cond2 >= 0;
    if (dp[pos][st][cond1 + 2][cond2 + 2] != -1)
        return dp[pos][st][cond1 + 2][cond2 + 2];

    int lim[4], cnt[4]; long long int ret = 0;
    for (int i = 0; i < 4; i++)
        lim[i] = (st >> i & 1) ? bst[i][pos] : 1;
    for (cnt[0] = 0; cnt[0] <= lim[0]; cnt[0]++) {
        for (cnt[1] = 0; cnt[1] <= lim[1]; cnt[1]++) {
            for (cnt[2] = 0; cnt[2] <= lim[2]; cnt[2]++) {
                for (cnt[3] = 0; cnt[3] <= lim[3]; cnt[3]++) {
                    int nextst = 0;
                    for (int i = 3; i >= 0; i--)
                        nextst = (nextst << 1) + ((st >> i & 1) && cnt[i] == lim[i]);
                    int nextCond1 = min(2, (cond1 << 1) + cnt[0] + cnt[2] - cnt[1] - cnt[3]);
                    int nextCond2 = min(2, (cond2 << 1) + cnt[0] + cnt[3] - cnt[1] - cnt[2]);
                    if (nextCond1 <= -2 || nextCond2 <= -2)
                        continue;
                    ret = (ret + dfs(pos - 1, nextst, nextCond1, nextCond2)) % mod;
                }
            }
        }
    }

    dp[pos][st][cond1 + 2][cond2 + 2] = ret;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        memset(dp, -1, sizeof(dp));
        for (int i = 0; i < 4; i++)
            cin >> arr[i], bst[i] = arr[i];
        cout << dfs(60, 15, 0, 0) << '\n';
    }

    return 0;
}
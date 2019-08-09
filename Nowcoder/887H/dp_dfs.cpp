#include <bits/stdc++.h>
using namespace std;

#define SIZE 32

long long int dp[SIZE][2][2][2][2]; 
int fst, snd, thd;
bitset<32> fstBst, sndBst, thdBst;

// cond1: x & y <= C
// cond2: x ^ y >= C
// 0: Might satisfy, 1: Confirmed to satisfy
long long int dfs(int pos, bool cond1, bool cond2, bool hasLim1, bool hasLim2) {
    if (pos < 0)
        return 1;
    if (dp[pos][cond1][cond2][hasLim1][hasLim2] != -1)
        return dp[pos][cond1][cond2][hasLim1][hasLim2];

    int fstLim = hasLim1 ? fstBst[pos] : 1;
    int sndLim = hasLim2 ? sndBst[pos] : 1;

    long long int ret = 0;
    for (int i = 0; i <= fstLim; i++) {
        for (int j = 0; j <= sndLim; j++) {
            int bit1 = i & j, bit2 = i ^ j;
            if (!cond1 && bit1 > thdBst[pos])
                continue;
            if (!cond2 && bit2 < thdBst[pos])
                continue;
            int nextCond1 = cond1 || bit1 < thdBst[pos];
            int nextCond2 = cond2 || bit2 > thdBst[pos];
            ret += dfs(pos - 1, nextCond1, nextCond2, hasLim1 && i == fstLim, hasLim2 && j == sndLim);
        }
    }

    dp[pos][cond1][cond2][hasLim1][hasLim2] = ret;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        memset(dp, -1, sizeof(dp));
        cin >> fst >> snd >> thd;
        fstBst = fst; sndBst = snd; thdBst = thd;
        long long int ret = 1ll * fst * snd;
        ret -= dfs(30, false, false, true, true) - max(0, snd - thd + 1) - max(0, fst - thd + 1);
        cout << ret << '\n';
    }

    return 0;
}
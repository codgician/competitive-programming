#include <bits/stdc++.h>
using namespace std;

#define SIZE 2010

const long long int mod = 1e9 + 7;

long long int dp[SIZE][SIZE];
int cntArr[SIZE], gLen, m, d;

long long int dfs(int pos, int rem, bool isZero, bool hasLim) {
    if (pos < 0) 
        return !isZero && rem == 0;
    if (!hasLim && dp[pos][rem] != -1)
        return dp[pos][rem];

    long long int ans = 0;
    int lim = hasLim ? cntArr[pos] : 9;

    for (int i = 0; i <= lim; i++) {
        if (((gLen - pos) & 1) == 1 && i == d)    // Odd position
            continue;
        if (((gLen - pos) & 1) == 0 && i != d)    // Even position
            continue;
        int nextRem = (rem * 10 + i) % m;
        ans = (ans + dfs(pos - 1, nextRem, isZero && i == 0, hasLim && i == lim)) % mod;
    }

    if (!hasLim)
        dp[pos][rem] = ans;
    return ans;
}

long long int work(string & str) {
    int len = str.size();
    for (int i = 0; i < len; i++) 
        cntArr[i] = str[len - i - 1] - '0';
    for (int i = len; i <= gLen; i++)
        cntArr[i] = 0;
    return dfs(gLen - 1, 0, true, true) % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    memset(dp, -1, sizeof(dp));

    string qLeftPt, qRightPt;
    cin >> m >> d >> qLeftPt >> qRightPt;
    gLen = qRightPt.size();
    qLeftPt[qLeftPt.size() - 1]--;
    for (int i = qLeftPt.size() - 1; i > 0; i--) {
        if (qLeftPt[i] < '0') {
            qLeftPt[i] += 10;
            qLeftPt[i - 1]--;
        }
    }

    cout << (work(qRightPt) - work(qLeftPt) + mod) % mod << endl;

    return 0;
}
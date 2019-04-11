#include <bits/stdc++.h>
using namespace std;

#define SIZE 20
#define STATE_SIZE 120

long long int dp[SIZE][STATE_SIZE];
int arr[16] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6, 6, 5, 4, 5, 5, 4};
int cntArr[SIZE];

const long long int mod = 1ll << 32;

int hexToDec(char ch) {
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    return ch - 'A' + 10;
}

long long int dfs(int pos, int sum, bool hasLim) {
    if (pos < 0)
        return sum;
    if (!hasLim && dp[pos][sum] != -1)
        return dp[pos][sum];

    long long int ans = 0;
    int lim = hasLim ? cntArr[pos] : 15;

    for (int i = 0; i <= lim; i++) {
        int nextSum = sum + arr[i];
        ans += dfs(pos - 1, nextSum, hasLim && i == lim);
    }

    if (!hasLim)
        dp[pos][sum] = ans;
    return ans;
}

long long int solve(long long int num) {
    if (num == -1)
        return 0;
    for (int i = 0; i < 8; i++) {
        cntArr[i] = num % 16;
        num /= 16;
    }
    return dfs(7, 0, true);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        memset(dp, -1, sizeof(dp));
        long long int leftPt = 0, rightPt;
        string str;
        cin >> rightPt >> str;
        for (auto ch : str) {
            leftPt = (leftPt << 4) + hexToDec(ch);
        }
        rightPt += leftPt - 1;

        long long int ans = 0;
        if (rightPt >= mod) {
            ans = solve(mod - 1) - solve(leftPt - 1);
            ans += solve(rightPt);
        } else {
            ans = solve(rightPt) - solve(leftPt - 1);
        }
        cout << ans << '\n';
    }

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define SIZE 25
#define TOT_SIZE 75

long long int dp[SIZE][SIZE][SIZE];
int trans[TOT_SIZE];
bool vis[TOT_SIZE];
vector<int> vec;
int redNum, blueNum, greenNum, totNum, permuNum, mod;

long long int fastPow(long long int a, long long int n) {
    long long int ans = 1;
    a %= mod;
    while (n > 0) {
        if (n & 1)
            ans = ans * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return ans;
}

long long int solve() {
    memset(dp, 0, sizeof(dp));
    memset(vis, false, sizeof(vis));
    vec.clear();
    for (int i = 0; i < totNum; i++) {
        if (vis[i])
            continue;
        vis[i] = true;
        int cntPt = trans[i], siz = 1;
        while (cntPt != i) {
            siz++; vis[cntPt] = true;
            cntPt = trans[cntPt];
        }
        vec.push_back(siz);
    }

    int cycleNum = vec.size();
    dp[0][0][0] = 1;
    for (int t = 0; t < cycleNum; t++) {
        for (int i = redNum; i >= 0; i--) {
            for (int j = blueNum; j >= 0; j--) {
                for (int k = greenNum; k >= 0; k--) {
                    if (i >= vec[t])
                        dp[i][j][k] = (dp[i][j][k] + dp[i - vec[t]][j][k]) % mod;
                    if (j >= vec[t])
                        dp[i][j][k] = (dp[i][j][k] + dp[i][j - vec[t]][k]) % mod;
                    if (k >= vec[t])
                        dp[i][j][k] = (dp[i][j][k] + dp[i][j][k - vec[t]]) % mod;
                }
            }
        }
    }

    return dp[redNum][blueNum][greenNum];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> redNum >> blueNum >> greenNum >> permuNum >> mod;
    totNum = redNum + blueNum + greenNum;
    long long int ans = 0;
    for (int i = 0; i < permuNum; i++) {
        for (int j = 0; j < totNum; j++) {
            cin >> trans[j];
            trans[j]--;
        }
        ans = (ans + solve()) % mod;
    }
    for (int j = 0; j < totNum; j++)
        trans[j] = j;
    ans = (ans + solve()) % mod;
    cout << ans * fastPow(permuNum + 1, mod - 2) % mod  << '\n';

    return 0;
}
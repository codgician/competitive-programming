#include <bits/stdc++.h>
using namespace std;

#define SIZE (1 << 20)

int dp[SIZE], trans[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int len, num; string str; cin >> len >> num >> str;
    int lim = (1 << num) - 1; 
    for (int i = 1; i < len; i++) 
        trans[(1 << (str[i] - 'a') | (1 << (str[i - 1] - 'a')))]++;
    for (int i = 0; i < num; i++)
        for (int st = 0; st <= lim; st++)
            if (!(st & (1 << i)))
                trans[st | (1 << i)] += trans[st];

    fill(dp + 0, dp + SIZE, INT_MAX); dp[0] = 0;
    for (int st = 0; st <= lim; st++) {
        if (dp[st] == INT_MAX)
            continue;
        for (int i = 0; i < num; i++) {
            if (st & (1 << i))
                continue;
            int nextst = st | (1 << i), val = len - 1 - trans[nextst] - trans[lim ^ nextst];
            dp[nextst] = min(dp[nextst], dp[st] + val);
        }
    }

    cout << dp[(1 << num) - 1] << '\n';
    return 0;
}
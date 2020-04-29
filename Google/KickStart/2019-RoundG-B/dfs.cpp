#include <bits/stdc++.h>
using namespace std;

#define SIZE 1010

bitset<50> bsts[SIZE];
int zeros[50], len; long long int ans, lim;

void dfs(int pos, long long int cnt, long long int sum) {
    if (cnt + (1ll << (pos + 1)) - 1 <= ans || sum > lim) 
        return;
    if (pos == -1) {
        ans = cnt;  return;
    }

    dfs(pos - 1, cnt + (1ll << pos), sum + zeros[pos] * (1ll << pos));
    dfs(pos - 1, cnt, sum + (len - zeros[pos]) * (1ll << pos));
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    for (int t = 1; t <= caseNum; t++) {
        cin >> len >> lim;
        fill(zeros + 0, zeros + 50, 0);
        for (int i = 0; i < len; i++) {
            long long int cnt; cin >> cnt;
            bsts[i] = cnt;
            for (int j = 0; j <= 49; j++)
                zeros[j] += bsts[i][j] ^ 1;
        }
        ans = -1; dfs(49, 0, 0);
        cout << "Case #" << t << ": " << ans << '\n';
    }

    return 0;
}
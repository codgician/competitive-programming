#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 400010
 
int events[SIZE], arr[SIZE], pos[SIZE];
pair<int, int> ans[SIZE];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++)
        pos[i] = i, arr[i] = i, ans[i] = make_pair(i, i);
    for (int i = 0; i < m; i++) {
        int cnt; cin >> cnt; cnt--;
        if (pos[cnt] == 0)
            continue;
        int prev = arr[pos[cnt] - 1];
        pos[cnt]--; pos[prev]++;
        swap(arr[pos[cnt]], arr[pos[prev]]);
 
        ans[cnt].first = min(ans[cnt].first, pos[cnt]);
        ans[cnt].second = max(ans[cnt].second, pos[cnt]);
        ans[prev].first = min(ans[prev].first, pos[prev]);
        ans[prev].second = max(ans[prev].second, pos[prev]);
    }
 
    for (int i = 0; i < n; i++)
        cout << ans[i].first + 1 << " " << ans[i].second + 1 << '\n';
    return 0;
}
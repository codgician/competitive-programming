#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 100010
 
vector<int> fst[SIZE], snd[SIZE];
vector<pair<int, int> > rows, cols;
 unordered_map<long long int, int> mp;
 
long long int p2ll(int x, int y) {
    return 1ll * x * SIZE + y;
}

int solve(int x, int y, int delta, int ret) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            long long int cnt = p2ll(x + i * delta, y + j * delta);
            if (mp.find(cnt) != mp.end())
                ret -= mp[cnt];
        }
    }
    return ret;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int num, delta; cin >> num >> delta;
    int row = 0, column = 0;
    for (int i = 0; i < num; i++) {
         int x, y; cin >> x >> y;
         fst[x].push_back(y); snd[y].push_back(x);
         mp[p2ll(x, y)]++;
         row = max(row, x); column = max(column, y);
    }
 
    for (int i = 0; i <= row; i++) {
        int cnt = 0;
        for (int j = 0; j < 3; j++)
            if (i + delta * j <= row)
                cnt += fst[i + delta * j].size();
        rows.push_back(make_pair(cnt, i));
    }
 
    for (int i = 0; i <= column; i++) {
        int cnt = 0;
        for (int j = 0; j < 3; j++)
            if (i + delta * j <= column)
                cnt += snd[i + delta * j].size();
        cols.push_back(make_pair(cnt, i));
    }
 
    sort(rows.begin(), rows.end(), greater<pair<int, int> >());
    sort(cols.begin(), cols.end(), greater<pair<int, int> >());
 
    int rowLim = min(500, (int)rows.size()), colLim = min(500, (int)cols.size()), ans = 0;
    for (int i = 0; i < rowLim; i++)
        for (int j = 0; j < colLim; j++)
            ans = max(ans, solve(rows[i].second, cols[j].second, delta, rows[i].first + cols[j].first));
    cout << ans << '\n';
 
    return 0;
}
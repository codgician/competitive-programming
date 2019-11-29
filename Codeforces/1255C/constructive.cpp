#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 100010
 
vector<int> pos[SIZE], tup[SIZE];
bool vis[SIZE], pvis[SIZE];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int len; cin >> len;
    fill(vis + 0, vis + len, false);
    fill(pvis + 0, pvis + len, false);
    for (int i = 0; i < len - 2; i++) {
        for (int j = 0; j < 3; j++) {
            int cnt; cin >> cnt;
            pos[cnt].push_back(i);
            tup[i].push_back(cnt);
        }
    }
    for (int i = 1; i <= len; i++)
        sort(pos[i].begin(), pos[i].end()), sort(tup[i].begin(), tup[i].end()); 
 
    vector<int> ans; int pid = -1;
    for (int i = 1; i <= len; i++) 
        if (pos[i].size() == 1) {
            ans.push_back(i), vis[i] = true;
            pid = pos[i].front();
            break;
        }
    
    pvis[pid] = true;
    for (const auto & v : tup[pid])
        if (!vis[v])
            ans.push_back(v), vis[v] = true;
    
    while ((int)ans.size() < len) {
        int fst = ans[ans.size() - 1], snd = ans[ans.size() - 2], ret = -1;
        for (const auto & v : pos[fst]) {
            if (!pvis[v] && binary_search(pos[snd].begin(), pos[snd].end(), v)) {
                ret = v; break;
            }
        }
 
        if (ret == -1) {
            swap(ans[ans.size() - 2], ans[ans.size() - 3]);
            fst = ans[ans.size() - 1], snd = ans[ans.size() - 2];
            for (const auto & v : pos[fst]) {
                if (!pvis[v] && binary_search(pos[snd].begin(), pos[snd].end(), v)) {
                    ret = v; break;
                }
            }
        }
 
        pvis[ret] = true;
        for (const auto & v : tup[ret])
            if (!vis[v])
                ans.push_back(v), vis[v] = true;
    }
 
    for (const auto & i : ans)
        cout << i << ' ';
    cout << '\n';
 
    return 0;
}

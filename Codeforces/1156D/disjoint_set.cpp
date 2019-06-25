#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

int parent[2][SIZE];
unordered_map<int, vector<int> > mp[2];

int getParent(int id, int cntPt) {
    if (parent[id][cntPt] == cntPt)
        return cntPt;
    parent[id][cntPt] = getParent(id, parent[id][cntPt]);
    return parent[id][cntPt];
}

void merge(int id, int fstPt, int sndPt) {
    fstPt = getParent(id, fstPt);
    sndPt = getParent(id, sndPt);
    if (fstPt != sndPt)
        parent[id][sndPt] = fstPt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int vertexNum;
    cin >> vertexNum;
    for (int t = 0; t < 2; t++)
        for (int i = 0; i < vertexNum; i++) {
            parent[t][i] = i;
        }

    for (int i = 1; i < vertexNum; i++) {
        int from, to, len;
        cin >> from >> to >> len;
        from--; to--;
        merge(len, from, to);
    }

    long long int ans = 0;
    for (int t = 0; t < 2; t++) {
        for (int i = 0; i < vertexNum; i++)
            mp[t][getParent(t, i)].push_back(i);
        for (auto p : mp[t])
            ans += 1ll * p.second.size() * (p.second.size() - 1);
    }

    for (auto p : mp[0])
        for (auto i : p.second)
            if (mp[1][getParent(1, i)].size())
                ans += 1ll * (p.second.size() - 1) * (mp[1][getParent(1, i)].size() - 1);
    cout << ans << '\n';
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

typedef struct _Edge {
    int to, next;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE], edgePt;

int fav[SIZE];
long long int ans[SIZE], tot;

void addEdge(int from, int to) {
    edge[edgePt] = {to, head[from]};
    head[from] = edgePt++;
}

long long int combN2(long long int num) {
    return num * (num - 1) / 2;
}

void dfs(int cntPt, int fatherPt) {
    map<int, int> mp; mp[fav[cntPt]]++;
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (nextPt == fatherPt)
            continue;
        mp[fav[nextPt]]++;
        dfs(nextPt, cntPt);
    }

    for (auto & p : mp)
        if (p.second > 1)
            tot += combN2(p.second);

    if (fatherPt != -1)
        mp[fav[fatherPt]]++;
    if (mp[fav[cntPt]] > 1)
        ans[cntPt] -= combN2(mp[fav[cntPt]]);
    mp[fav[cntPt]]--; long long int cnt = 0;
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (nextPt == fatherPt)
            continue;
        cnt = max(cnt, combN2(mp[fav[nextPt]]));
    }
    ans[cntPt] += cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int vertexNum, favNum;
    cin >> vertexNum >> favNum;
    fill(head + 0, head + vertexNum, -1); 
    fill(ans + 0, ans + vertexNum, 0);
    edgePt = 0; tot = 0;

    for (int i = 0; i < vertexNum; i++)
        cin >> fav[i];
    for (int i = 1; i < vertexNum; i++) {
        int from, to; cin >> from >> to;
        from--; to--;
        addEdge(from, to); addEdge(to, from);
    }

    dfs(0, -1);

    for (int i = 0; i < vertexNum; i++)
        cout << tot + ans[i] << (i == vertexNum - 1 ? '\n' : ' ');
    
    return 0;
}
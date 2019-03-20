#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

typedef struct _Edge {
    int to, next, ans;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE], edgePt;
int vertexNum, lim, ans;

void addEdge(int from, int to) {
    edge[edgePt] = {to, head[from], 0};
    head[from] = edgePt++;
}

pair<int, int> deg[SIZE];

void dfs(int cntPt, int parentPt, int prevAns) {
    int cntAns = 0;    
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (nextPt == parentPt)
            continue;
        cntAns++;
        if (cntAns == prevAns)
            cntAns++;
        cntAns = min(cntAns, ans);
        edge[i].ans = cntAns;
        edge[i ^ 1].ans = cntAns;
        dfs(nextPt, cntPt, cntAns);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(head, -1, sizeof(head));
    edgePt = 0;

    cin >> vertexNum >> lim;
    for (int i = 1; i < vertexNum; i++) {
        int from, to;
        cin >> from >> to;
        from--, to--;
        addEdge(from, to);
        addEdge(to, from);
        deg[from].first++, deg[to].first++;
        deg[from].second = from, deg[to].second = to;
    }

    sort(deg + 0, deg + vertexNum, greater<pair<int, int>>());
    ans = deg[min(lim, vertexNum - 1)].first;

    cout << ans << endl;
    dfs(0, -1, 0);
    for (int i = 0; i < edgePt; i += 2)
        cout << edge[i].ans << " ";
    cout << endl;

    return 0;
}
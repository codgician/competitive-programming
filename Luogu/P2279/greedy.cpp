#include <bits/stdc++.h>
using namespace std;

#define SIZE 1010

typedef struct _Edge {
    int to, next;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE], vertexNum, edgePt;
bool mark[SIZE], vis[SIZE];
int father[SIZE];
stack<int> stk;

void addEdge(int from, int to) {
    edge[edgePt] = {to, head[from]};
    head[from] = edgePt++;
} 

void bfs(int rootPt) {
    memset(mark, false, sizeof(mark));
    memset(vis, false, sizeof(vis));
    queue<int> q;
    q.push(rootPt);
    stk.push(rootPt);
    father[rootPt] = rootPt;
    vis[rootPt] = true;
    while (!q.empty()) {
        int cntPt = q.front();
        q.pop();
        for (int i = head[cntPt]; i != -1; i = edge[i].next) {
            int nextPt = edge[i].to;
            if (vis[nextPt])
                continue;
            vis[nextPt] = true;
            father[nextPt] = cntPt;
            stk.push(nextPt);
            q.push(nextPt);
        }
    }
}

void dfs(int cntPt, int fatherPt, int depth) {
    mark[cntPt] = true;
    if (depth == 2)
        return;
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (nextPt == fatherPt)
            continue;
        dfs(nextPt, cntPt, depth + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(head, -1, sizeof(head));
    edgePt = 0;
    cin >> vertexNum;
    for (int i = 1; i < vertexNum; i++) {
        int cnt;
        cin >> cnt;
        cnt--;
        addEdge(i, cnt);
        addEdge(cnt, i);
    }
    bfs(0);
    int ans = 0;
    while (!stk.empty()) {
        int cntPt = stk.top();
        stk.pop();
        if (!mark[cntPt]) {
            dfs(father[father[cntPt]], -1, 0);
            ans++;
        }
        
    }
    cout << ans << endl;
    return 0;
}
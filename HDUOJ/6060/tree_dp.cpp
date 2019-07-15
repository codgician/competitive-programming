#include <bits/stdc++.h>
using namespace std;

#define SIZE 1000010

typedef struct _Edge {
    int to, next, len;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE], edgePt;
int siz[SIZE], cost[SIZE];

void addEdge(int from, int to, int len) {
    edge[edgePt] = {to, head[from], len};
    head[from] = edgePt++;
}

void dfs(int cntPt, int fatherPt) {
    siz[cntPt] = 1;
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (nextPt == fatherPt)
            continue;
        cost[nextPt] = edge[i].len;
        dfs(nextPt, cntPt);
        siz[cntPt] += siz[nextPt];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int vertexNum, k;
    while (cin >> vertexNum >> k) {
        fill(head + 0, head + vertexNum, -1);
        edgePt = 0;
        for (int i = 1; i < vertexNum; i++) {
            int from, to, len; cin >> from >> to >> len;
            from--; to--;
            addEdge(from, to, len); addEdge(to, from, len);
        }
        dfs(0, -1);
        long long int ans = 0;
        for (int i = 1; i < vertexNum; i++)
            ans += 1ll * min(siz[i], k) * cost[i];
        cout << ans << '\n';
    }

    return 0;
}
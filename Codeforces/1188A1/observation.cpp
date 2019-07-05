#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

typedef struct _Edge {
    int to, next;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE], edgePt, vertexNum;

int deg[SIZE], father[SIZE], depth[SIZE], siz[SIZE];

void addEdge(int from, int to) {
    edge[edgePt] = {to, head[from]};
    head[from] = edgePt++;
}

bool check() {
    for (int i = 0; i < vertexNum; i++)
        if (deg[i] == 2)
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(head, -1, sizeof(head));
    memset(deg, 0, sizeof(deg));
    edgePt = 0;
    cin >> vertexNum;
    for (int i = 1; i < vertexNum; i++) {
        int from, to; cin >> from >> to;
        from--; to--;
        addEdge(from, to); addEdge(to, from);
        deg[from]++; deg[to]++;
    }

    cout << (check() ? "YES\n" : "NO\n");

    return 0;
}
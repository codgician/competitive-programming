#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

typedef struct _Edge {
    int to, next;
} Edge;

Edge edge[SIZE << 2];
int head[SIZE], edgePt, vertexNum;
int ans[SIZE], inDeg[SIZE], ansPt;
bool vis[SIZE];

void addEdge(int from, int to) {
    edge[edgePt] = {to, head[from]};
    head[from] = edgePt++;
}

bool dfs(int cntPt, int cntDepth) {
    if (cntDepth == vertexNum)
        return true;

    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (vis[nextPt])
            continue;
        bool prune = false;
        for (int j = head[cntPt]; j != -1; j = edge[j].next) {
            int nextPt1 = edge[j].to;
            if (nextPt1 == nextPt)
                continue;
            inDeg[nextPt1]--;
            if (!vis[nextPt1] && inDeg[nextPt1] <= 0)
                prune = true;
        }

        if (!prune) {
            vis[nextPt] = true;
            ans[ansPt++] = nextPt;
            if (dfs(nextPt, cntDepth + 1))
                return true;
            ansPt--;
            vis[nextPt] = false;
        }

        for (int j = head[cntPt]; j != -1; j = edge[j].next) {
            int nextPt1 = edge[j].to;
            if (nextPt1 == nextPt)
                continue;
            inDeg[nextPt1]++;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        cin >> vertexNum;
        for (int i = 1; i <= vertexNum; i++)
            head[i] = -1, vis[i] = false, inDeg[i] = 0;
        edgePt = 0;

        for (int i = 1; i <= vertexNum; i++)
            for (auto j : {i * 2 + 1, i * 2, i - 1, i / 2})
                if (j >= 2 && j <= vertexNum && i != j)
                    addEdge(i, j), inDeg[j]++;

        ans[0] = 1; ansPt = 1; vis[1] = true;
        if (dfs(1, 1)) {
            cout << ans[0];
            for (int i = 1; i < ansPt; i++)
                cout << " " << ans[i];
            cout << '\n';
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}

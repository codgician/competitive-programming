#include <bits/stdc++.h>
using namespace std;

#define EDGE_SIZE 400010
#define VERTEX_SIZE 100010

typedef struct _Edge {
    int to, next;
} Edge;

Edge edge[2][EDGE_SIZE];
int head[2][VERTEX_SIZE], edgePt[2];

int dfn[VERTEX_SIZE], low[VERTEX_SIZE], cntTime;
int edccId[VERTEX_SIZE], edccNum, bridgeNum, vertexNum;
bool isBridge[EDGE_SIZE];

/* Disjoint Set */

int parent[VERTEX_SIZE];

int getParent(int cntPt) {
    if (parent[cntPt] == cntPt) {
        return cntPt;
    } else {
        parent[cntPt] = getParent(parent[cntPt]);
        return parent[cntPt];
    }
}

void merge(int fstPt, int sndPt) {
    fstPt = getParent(fstPt), sndPt = getParent(sndPt);
    if (fstPt != sndPt)
        parent[sndPt] = fstPt;
}

/* Tarjan + eDCC */

void addEdge(int id, int from, int to) {
    edge[id][edgePt[id]] = {to, head[id][from]};
    head[id][from] = edgePt[id]++;
}

void tarjan(int cntPt, int edgeId) {
    dfn[cntPt] = cntTime;
    low[cntPt] = cntTime;
    cntTime++;
    for (int i = head[0][cntPt]; i != -1; i = edge[0][i].next) {
        int nextPt = edge[0][i].to;
        if (dfn[nextPt] == -1) {
            tarjan(nextPt, i);
            low[cntPt] = min(low[cntPt], low[nextPt]);
            if (low[nextPt] > dfn[cntPt]) {
                bridgeNum++;
                isBridge[i] = true;
                isBridge[i ^ 1] = true;
            }
        } else if (i != (edgeId ^ 1)) {
            low[cntPt] = min(low[cntPt], dfn[nextPt]);
        }
    }
}

void dfs(int cntPt) {
    edccId[cntPt] = edccNum;
    for (int i = head[0][cntPt]; i != -1; i = edge[0][i].next) {
        int nextPt = edge[0][i].to;
        if (edccId[nextPt] > -1 || isBridge[i])
            continue;
        dfs(nextPt);
    }
}

/* LCA */

int depth[VERTEX_SIZE], anc[VERTEX_SIZE][20];
bool vis[VERTEX_SIZE];
int maxDepth;

void bfs(int startPt) {
    memset(depth, -1, sizeof(depth));
    memset(anc, -1, sizeof(anc));
    queue<int> q;
    q.push(startPt);
    depth[startPt] = 0;

    while (!q.empty()) {
        int cntPt = q.front();
        q.pop();

        for (int i = head[1][cntPt]; i != -1; i = edge[1][i].next) {
            int nextPt = edge[1][i].to;
            if (depth[nextPt] != -1)
                continue;
            depth[nextPt] = depth[cntPt] + 1;
            anc[nextPt][0] = cntPt;
            for (int j = 1; j <= maxDepth; j++) {
                if (anc[nextPt][j - 1] != -1) {
                    anc[nextPt][j] = anc[anc[nextPt][j - 1]][j - 1];
                }
            }
            q.push(nextPt);
        }
    }
}

int getLca(int fstPt, int sndPt) {
    if (depth[fstPt] < depth[sndPt])
        swap(fstPt, sndPt);
    for (int i = maxDepth; i >= 0; i--)
        if (anc[fstPt][i] != -1 && depth[anc[fstPt][i]] >= depth[sndPt])
            fstPt = anc[fstPt][i];
    if (fstPt == sndPt)
        return fstPt;
    for (int i = maxDepth; i >= 0; i--)
        if (anc[fstPt][i] != -1 && anc[sndPt][i] != -1 && anc[fstPt][i] != anc[sndPt][i])
            fstPt = anc[fstPt][i], sndPt = anc[sndPt][i];
    return anc[fstPt][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        memset(head, -1, sizeof(head));
        memset(dfn, -1, sizeof(dfn));
        memset(edccId, -1, sizeof(edccId));
        memset(isBridge, false, sizeof(isBridge));
        memset(edgePt, 0, sizeof(edgePt));
        cntTime = 0, edccNum = 0, bridgeNum = 0;

        int edgeNum, qNum;
        cin >> vertexNum >> edgeNum >> qNum;
        for (int i = 0; i < edgeNum; i++) {
            int from, to;
            cin >> from >> to;
            from--, to--;
            addEdge(0, from, to);
            addEdge(0, to, from);
        }

        for (int i = 0; i < vertexNum; i++)
            if (dfn[i] == -1)
                tarjan(i, 0);

        for (int i = 0; i < vertexNum; i++) {
            if (edccId[i] == -1) {
                dfs(i);
                edccNum++;
            }
        }

        for (int i = 0; i < edccNum + 1; i++)
            parent[i] = i;

        for (int i = 0; i < edgePt[0]; i += 2) {
            int from = edge[0][i ^ 1].to, to = edge[0][i].to;
            if (edccId[from] == edccId[to])
                continue;
            addEdge(1, edccId[from], edccId[to]);
            addEdge(1, edccId[to], edccId[from]);
            merge(edccId[from], edccId[to]);
        }

        for (int i = 0; i < edccNum; i++) {
            if (getParent(i) != getParent(edccNum)) {
                addEdge(1, i, edccNum);
                addEdge(1, edccNum, i);
                merge(edccNum, i);
            }
        }

        int rootPt = edccNum++;

        // LCA

        maxDepth = log2(edccNum) + 1;
        bfs(rootPt);

        while (qNum--) {
            int rec, from, to;
            cin >> rec >> from >> to;
            rec--, from--, to--;
            rec = edccId[rec], from = edccId[from], to = edccId[to];

            if (getLca(from, rec) == rootPt || getLca(to, rec) == rootPt) {
                // Not even connected
                cout << "No\n";
                continue;
            }

            if (from == to) {
                cout << (from == rec ? "Yes\n" : "No\n");
            } else {
                int lca = getLca(from, to);

                if (from == rec || to == rec) {
                    cout << "Yes\n";
                } else {
                    if (lca == rec)
                        cout << "Yes\n";
                    else if ((getLca(from, rec) == rec) ^ (getLca(to, rec) == rec))
                        cout << "Yes\n";
                    else
                        cout << "No\n";
                }
            }
        }
    }

    return 0;
}
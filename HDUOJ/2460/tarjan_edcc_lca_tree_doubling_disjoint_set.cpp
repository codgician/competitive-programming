#include <bits/stdc++.h>
using namespace std;

#define VERTEX_SIZE 100010
#define EDGE_SIZE 400020

typedef struct _Edge {
    int to, next;
} Edge;

Edge edge[2][EDGE_SIZE];
int head[2][VERTEX_SIZE], edgePt[2];
int vertexNum, edgeNum;

void addEdge(int id, int from, int to) {
    edge[id][edgePt[id]] = {to, head[id][from]};
    head[id][from] = edgePt[id]++;
}

/* Tarjan (e-DCC) */

int dfn[VERTEX_SIZE], low[VERTEX_SIZE], cntTime;
int edccId[VERTEX_SIZE], edccNum;
bool isBridge[EDGE_SIZE];
int bridgeNum;

void tarjan(int cntPt, int edgeId) {
    dfn[cntPt] = cntTime, low[cntPt] = cntTime;
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

int depth[VERTEX_SIZE], dist[VERTEX_SIZE], anc[VERTEX_SIZE][20];
int maxDepth;

void bfs(int startPt) {
    memset(depth, -1, sizeof(depth));
    memset(dist, 0, sizeof(dist));
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
            dist[nextPt] = dist[cntPt] + 1;
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
    if (depth[fstPt] > depth[sndPt])
        swap(fstPt, sndPt);
    if (fstPt != sndPt)
        parent[sndPt] = fstPt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int casePt = 0;
    while (cin >> vertexNum >> edgeNum) {
        if (vertexNum == 0 && edgeNum == 0)
            break;

        memset(head, -1, sizeof(head));
        memset(dfn, -1, sizeof(dfn));
        memset(edccId, -1, sizeof(edccId));
        memset(isBridge, false, sizeof(isBridge));
        memset(edgePt, 0, sizeof(edgePt));
        cntTime = 0, edccNum = 0, bridgeNum = 0;

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

        for (int i = 0; i < edgePt[0]; i += 2) {
            int from = edge[0][i ^ 1].to, to = edge[0][i].to;
            from = edccId[from], to = edccId[to];
            if (from == to)
                continue;
            addEdge(1, from, to); 
            addEdge(1, to, from);
        }

        maxDepth = log2(edccNum);
        bfs(0);

        for (int i = 0; i < edccNum; i++)
            parent[i] = i;

        cout << "Case " << ++casePt << ":\n";

        int qNum;
        cin >> qNum;
        while (qNum--) {
            int from, to;
            cin >> from >> to;
            from = edccId[from - 1], to = edccId[to - 1];
            int lca = getLca(from, to);

            from = getParent(from);
            while (depth[from] > depth[lca]) {
                merge(from, anc[from][0]);
                bridgeNum--;
                from = getParent(from);
            }

            to = getParent(to);
            while (depth[to] > depth[lca]) {
                merge(to, anc[to][0]);
                bridgeNum--;
                to = getParent(to);
            }

            cout << bridgeNum << '\n'; 
        }
        cout << '\n';
    }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define VERTEX_SIZE 10010
#define EDGE_SIZE 200020

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

/* Tarjan (v-DCC) */

int dfn[VERTEX_SIZE], low[VERTEX_SIZE], cntTime;
stack<int> stk;
vector<int> vdcc[VERTEX_SIZE];
bool isCut[VERTEX_SIZE];
int vdccId[VERTEX_SIZE], newId[VERTEX_SIZE], edgeVdccId[EDGE_SIZE];
int cntRoot, vdccNum;

void tarjan(int cntPt) {
    dfn[cntPt] = cntTime;
    low[cntPt] = cntTime;
    cntTime++;
    stk.push(cntPt);

    if (cntPt == cntRoot && head[0][cntPt] == -1) {
        vdcc[vdccNum++].push_back(cntPt);
        return;
    }

    bool isFirst = true;
    for (int i = head[0][cntPt]; i != -1; i = edge[0][i].next) {
        int nextPt = edge[0][i].to;
        if (dfn[nextPt] == -1) {
            tarjan(nextPt);
            low[cntPt] = min(low[cntPt], low[nextPt]);
            if (low[nextPt] >= dfn[cntPt]) {
                if (cntPt != cntRoot || !isFirst) 
                    isCut[cntPt] = true;
                isFirst = false;
                while (!stk.empty()) {
                    int cntTop = stk.top();
                    stk.pop();
                    vdcc[vdccNum].push_back(cntTop);
                    if (cntTop == nextPt)
                        break;
                }
                vdcc[vdccNum++].push_back(cntPt);
            }
        } else {
            low[cntPt] = min(low[cntPt], dfn[nextPt]);
        }
    }
}

/* LCA */
int depth[VERTEX_SIZE], dist[VERTEX_SIZE], anc[VERTEX_SIZE][20];
int maxDepth;

void bfs(int startPt) {
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
            dist[nextPt] = dist[cntPt] + (nextPt >= vdccNum);
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
    //ios::sync_with_stdio(false);
    //cin.tie(0); cout.tie(0);

    while (cin >> vertexNum >> edgeNum) {
        if (vertexNum == 0 && edgeNum == 0)
            break;

        memset(head, -1, sizeof(head));
        memset(dfn, -1, sizeof(dfn));
        memset(vdccId, -1, sizeof(vdccId));
        memset(isCut, false, sizeof(isCut));
        memset(edgePt, 0, sizeof(edgePt));
        for (int i = 0; i < vertexNum; i++)
            vdcc[i].clear();
        cntTime = 0, vdccNum = 0;

        for (int i = 0; i < edgeNum; i++) {
            int from, to;
            cin >> from >> to;
            from--, to--;
            addEdge(0, from, to);
            addEdge(0, to, from);
        }

        for (int i = 0; i < vertexNum; i++) {
            if (dfn[i] == -1) {
                cntRoot = i;
                tarjan(i);
            }
        }

        int newVertexNum = vdccNum;
        for (int i = 0; i < vertexNum; i++)
            if (isCut[i])
                newId[i] = newVertexNum++;

        for (int i = 0; i < vdccNum; i++) {
            for (auto j : vdcc[i]) {
                if (isCut[j]) {
                    addEdge(1, i, newId[j]);
                    addEdge(1, newId[j], i);
                }
                vdccId[j] = i;
            }

            for (auto j : vdcc[i]) {
                for (int k = head[0][j]; k != -1; k = edge[0][k].next) {
                    int nextPt = edge[0][k].to;
                    if (vdccId[nextPt] == i) {
                        edgeVdccId[k >> 1] = i;
                    }
                }
            }
        }

        maxDepth = log2(newVertexNum);
        memset(depth, -1, sizeof(depth));
        memset(dist, 0, sizeof(dist));
        memset(anc, -1, sizeof(anc));
        for (int i = 0; i < newVertexNum; i++)
            if (depth[i] == -1)
                bfs(i);

        int qNum;
        cin >> qNum;
        while (qNum--) {
            int from, to;
            cin >> from >> to;
            from = edgeVdccId[from - 1], to = edgeVdccId[to - 1];
            int lca = getLca(from, to);
            cout << dist[from] + dist[to] - (dist[lca] << 1) << '\n';
        }
    }

    return 0;
}
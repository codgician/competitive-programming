#include <bits/stdc++.h>
using namespace std;

#define VERTEX_SIZE 10010
#define EDGE_SIZE 200020

typedef struct _Edge {
    int to, next;
} Edge;

Edge edge[EDGE_SIZE];
int head[VERTEX_SIZE], edgePt;
int vertexNum, edgeNum;

int dfn[VERTEX_SIZE], low[VERTEX_SIZE], cntTime;
int bridgeNum;

stack<int> stk;
vector<int> vdcc[VERTEX_SIZE];
bool isCut[VERTEX_SIZE];
int vdccId[VERTEX_SIZE], cntRoot, vdccNum;

void addEdge(int from, int to) {
    edge[edgePt] = {to, head[from]};
    head[from] = edgePt++;
}

void tarjanBridge(int cntPt, int edgeId) {
    dfn[cntPt] = cntTime;
    low[cntPt] = cntTime;
    cntTime++;
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (dfn[nextPt] == -1) {
            tarjanBridge(nextPt, i);
            low[cntPt] = min(low[cntPt], low[nextPt]);
            if (low[nextPt] > dfn[cntPt]) {
                bridgeNum++;
            }
        } else if (i != (edgeId ^ 1)) {
            low[cntPt] = min(low[cntPt], dfn[nextPt]);
        }
    }
}

void tarjanVdcc(int cntPt) {
    dfn[cntPt] = cntTime;
    low[cntPt] = cntTime;
    cntTime++;
    stk.push(cntPt);

    if (cntPt == cntRoot && head[cntPt] == -1) {
        vdcc[vdccNum++].push_back(cntPt);
        return;
    }

    bool isFirst = true;
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (dfn[nextPt] == -1) {
            tarjanVdcc(nextPt);
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    while (cin >> vertexNum >> edgeNum) {
        if (vertexNum == 0 && edgeNum == 0)
            break;
        memset(head, -1, sizeof(head));
        memset(dfn, -1, sizeof(dfn));
        memset(vdccId, -1, sizeof(vdccId));
        memset(isCut, false, sizeof(isCut));
        cntTime = 0, bridgeNum = 0, vdccNum = 0;
        edgePt = 0;
        for (int i = 0; i < vertexNum; i++)
            vdcc[i].clear();

        for (int i = 0; i < edgeNum; i++) {
            int from, to;
            cin >> from >> to;
            addEdge(from, to);
            addEdge(to, from);
        }

        for (int i = 0; i < vertexNum; i++)
            if (dfn[i] == -1)
                tarjanBridge(i, 0);

        memset(dfn, -1, sizeof(dfn));
        cntTime = 0;

        for (int i = 0; i < vertexNum; i++)
            if (dfn[i] == -1)
                cntRoot = i, tarjanVdcc(i);

        int ans = 0;
        for (int i = 0; i < vdccNum; i++) {
            int cntEdge = 0;
            for (auto j : vdcc[i])
                vdccId[j] = i;
            for (auto j : vdcc[i]) {
                for (int k = head[j]; k != -1; k = edge[k].next) {
                    int nextPt = edge[k].to;
                    if (vdccId[nextPt] == i)
                        cntEdge++;
                }
            }
            cntEdge >>= 1;
            if (cntEdge > (int)vdcc[i].size())
                ans += cntEdge;
        }

        cout << bridgeNum << " " << ans << '\n';
    }
    return 0;
}
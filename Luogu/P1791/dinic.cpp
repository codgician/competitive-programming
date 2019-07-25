#include <bits/stdc++.h>
using namespace std;

#define VERTEX_SIZE 1010
#define EDGE_SIZE 4000010

typedef struct _Edge {
    int to, next;
    long long int cap;
} Edge;

Edge edge[EDGE_SIZE];
int head[VERTEX_SIZE], edgePt, vertexNum;
int depth[VERTEX_SIZE], lastVisitedEdge[VERTEX_SIZE];

void addEdge(int from, int to, long long int cap){
    if (cap == 0)
        return;
    edge[edgePt] = {to, head[from], cap};
    head[from] = edgePt++;
    edge[edgePt] = {from, head[to], 0};
    head[to] = edgePt++;
}

bool updateDepth(int startPt, int endPt) {
    memset(depth, -1, sizeof(depth));
    queue<int> q;
    depth[startPt] = 0;
    q.push(startPt);
    while (!q.empty()) {
        int cntPt = q.front();
        q.pop();
        for (int i = head[cntPt]; i != -1; i = edge[i].next) {
            int nextPt = edge[i].to;
            if (depth[nextPt] == -1 && edge[i].cap > 0) {
                depth[nextPt] = depth[cntPt] + 1;
                if (nextPt == endPt)
                    return true;
                q.push(nextPt);
            }
        }
    }
    return false;
}

long long int findAugPath(int cntPt, int endPt, int minCap) {
    if (cntPt == endPt)
        return minCap;
    long long int cntFlow = 0;
    for (int & i = lastVisitedEdge[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (depth[nextPt] == depth[cntPt] + 1 && edge[i].cap > 0) {
            int flowInc = findAugPath(nextPt, endPt, min(minCap - cntFlow, edge[i].cap));
            if (flowInc == 0) {
                depth[nextPt] = -1;
            } else {
                edge[i].cap -= flowInc;
                edge[i ^ 1].cap += flowInc;
                cntFlow += flowInc;
                if (cntFlow == minCap)
                    break;
            }
        }
    }
    return cntFlow;
}

long long int dinic(int srcPt, int snkPt) {
    long long int ret = 0;
    while (updateDepth(srcPt, snkPt)) {
        for (int i = 0; i < vertexNum; i++)
            lastVisitedEdge[i] = head[i];
        long long int flowInc =  findAugPath(srcPt, snkPt, INT_MAX);
        if (flowInc == 0)
            break;
        ret += flowInc;
    }
    return ret;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> vertexNum;
    int srcPt = vertexNum, snkPt = vertexNum + 1;
    fill(head + 0, head + vertexNum + 2, -1); edgePt = 0;

    long long int ans = 0;
    for (int i = 0; i < vertexNum; i++) {
        long long int cnt; cin >> cnt;
        addEdge(srcPt, i, cnt);
    }

    for (int i = 0; i < vertexNum; i++) {
        for (int j = 0; j < vertexNum; j++) {
            long long int cnt; cin >> cnt;
            if (i >= j)
                continue;
            addEdge(i, snkPt, cnt); addEdge(j, snkPt, cnt);
            addEdge(i, j, cnt << 1); addEdge(j, i, cnt << 1);
            ans += (cnt << 1);
        }
    }
    vertexNum += 2;
    cout << ans - dinic(srcPt, snkPt) << '\n';
    return 0;
}

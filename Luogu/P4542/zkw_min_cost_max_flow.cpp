#include <bits/stdc++.h>
using namespace std;

#define VERTEX_SIZE 320
#define EDGE_SIZE 205440

/* ZKW Weighted Network Flow */

typedef struct _Edge {
    int to, next;
    int capacity, cost;
} Edge;

Edge edge[EDGE_SIZE];
int head[VERTEX_SIZE], edgePt;
int dis[VERTEX_SIZE];
bool inQueue[VERTEX_SIZE], hasVisited[VERTEX_SIZE];
int vertexNum;

void addEdge(int from, int to, int capacity, int cost) {
    edge[edgePt] = {to, head[from], capacity, cost};
    head[from] = edgePt++;
    edge[edgePt] = {from, head[to], 0, -cost};
    head[to] = edgePt++;
}

bool isFullFlow(int srcPt, int snkPt) {
    for (int i = 0; i < vertexNum; i++)
        dis[i] = INT_MAX;
    memset(inQueue, false, sizeof(inQueue));
    dis[srcPt] = 0;
    queue<int> q;
    q.push(srcPt);
    inQueue[srcPt] = true;

    while (!q.empty()) {
        int cntPt = q.front();
        q.pop();
        inQueue[cntPt] = false;
        for (int i = head[cntPt]; i != -1; i = edge[i].next) {
            int nextPt = edge[i].to;
            if (edge[i ^ 1].capacity != 0 && dis[nextPt] > dis[cntPt] - edge[i].cost) {
                dis[nextPt] = dis[cntPt] - edge[i].cost;
                if (!inQueue[nextPt]) {
                    inQueue[nextPt] = true;
                    q.push(nextPt);
                }
            }
        }
    }
    return dis[snkPt] != INT_MAX;
}

int findAguPath(int cntPt, int snkPt, int minCap, int & cost) {
    if (cntPt == snkPt) {
        hasVisited[snkPt] = true;
        return minCap;
    }
    int cntFlow = 0;
    hasVisited[cntPt] = true;
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (hasVisited[nextPt])
            continue;
        if (dis[cntPt] - edge[i].cost == dis[nextPt] && edge[i].capacity > 0) {
            int flowInc = findAguPath(nextPt, snkPt, min(minCap - cntFlow, edge[i].capacity), cost);
            if (flowInc != 0) {
                cost += flowInc * edge[i].cost;
                edge[i].capacity -= flowInc;
                edge[i ^ 1].capacity += flowInc;
                cntFlow += flowInc;
            }
            if (cntFlow == minCap)
                break;
        }
    }
    return cntFlow;
}

void zkw(int srcPt, int snkPt, int & flow, int & cost) {
    flow = 0, cost = 0;
    while (isFullFlow(snkPt, srcPt)) {
        hasVisited[snkPt] = true;
        while (hasVisited[snkPt]) {
            memset(hasVisited, false, sizeof(hasVisited));
            flow += findAguPath(srcPt, snkPt, INT_MAX, cost);
        }
    }
}

int dist[VERTEX_SIZE][VERTEX_SIZE];
int edgeNum, personNum;

void floyd() {
    for (int k = 0; k < vertexNum; k++)
        for (int i = 0; i < vertexNum; i++)
            for (int j = 0; j < vertexNum; j++)
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && k <= max(i, j))
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(head, -1, sizeof(head));
    edgePt = 0;
    cin >> vertexNum >> edgeNum >> personNum;
    vertexNum++;
    for (int i = 0; i < vertexNum; i++) {
        dist[i][i] = 0;
        for (int j = i + 1; j < vertexNum; j++)
            dist[i][j] = INT_MAX, dist[j][i] = INT_MAX;
    }

    for (int i = 0; i < edgeNum; i++) {
        int from, to, len;
        cin >> from >> to >> len;
        dist[from][to] = min(dist[from][to], len);
        dist[to][from] = dist[from][to];
    }

    floyd();

    int srcPt = (vertexNum << 1);
    int snkPt = srcPt + 1;
    for (int i = 0; i < vertexNum; i++) {
        addEdge(srcPt, i << 1, i == 0 ? personNum : 1, 0);
        addEdge(i << 1 | 1, snkPt, 1, 0);
        for (int j = i + 1; j < vertexNum; j++)
            if (dist[i][j] != INT_MAX)
                addEdge(i << 1, j << 1 | 1, 1, dist[i][j]);
    }

    vertexNum = snkPt + 1;
    int flow, cost;
    zkw(srcPt, snkPt, flow, cost);
    cout << cost << '\n';

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define VERTEX_SIZE 401
#define EDGE_SIZE 31000

typedef struct _Edge {
    int to, next;
    int cap, cost;
} Edge;

Edge edge[EDGE_SIZE];
int head[VERTEX_SIZE], edgePt;
int dist[VERTEX_SIZE], minCap[VERTEX_SIZE], pre[VERTEX_SIZE];
bool inQueue[VERTEX_SIZE];
int vertexNum, edgeNum;

void addEdge(int from, int to, int cap, int cost) {
    edge[edgePt] = {to, head[from], cap, cost};
    head[from] = edgePt++;
    edge[edgePt] = {from, head[to], 0, -cost};
    head[to] = edgePt++;
}

void updCap(int startPt, int endPt) {
    int cntPt = endPt;
    while (cntPt != startPt) {
        int edgePt = pre[cntPt];
        edge[edgePt].cap -= minCap[endPt];
        edge[edgePt ^ 1].cap += minCap[endPt];
        cntPt = edge[edgePt ^ 1].to;
    }
}

bool findAugPath(int startPt, int endPt) {
    for (int i = 0; i < vertexNum; i++)
        dist[i] = INT_MAX, inQueue[i] = false;

    queue<int> q; q.push(startPt);
    dist[startPt] = 0;
    minCap[startPt] = INT_MAX;
    inQueue[startPt] = true;

    while (!q.empty()) {
        int cntPt = q.front(); q.pop();
        inQueue[cntPt] = false;

        int edgePt = head[cntPt];
        while (edgePt != -1) {
            if (edge[edgePt].cap > 0 && dist[cntPt] != INT_MAX && dist[edge[edgePt].to] > dist[cntPt] + edge[edgePt].cost) {
                dist[edge[edgePt].to] = dist[cntPt] + edge[edgePt].cost;
                minCap[edge[edgePt].to] = min(minCap[cntPt], edge[edgePt].cap);
                pre[edge[edgePt].to] = edgePt;

                if (!inQueue[edge[edgePt].to]) {
                    q.push(edge[edgePt].to);
                    inQueue[edge[edgePt].to] = true;
                }
            }
            edgePt = edge[edgePt].next;
        }
    }

    if (dist[endPt] == INT_MAX)
        return false;
    return true;
}

void edmondsKarp(int startPt, int endPt, int &flow, int &cost) {
    while (findAugPath(startPt, endPt)) {
        updCap(startPt, endPt);
        flow += minCap[endPt];
        cost += dist[endPt] * minCap[endPt];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(head, -1, sizeof(head));
    edgePt = 0;
    cin >> vertexNum >> edgeNum;
    for (int i = 0; i < edgeNum; i++) {
        int from, to, cap, cost;
        cin >> from >> to >> cap >> cost;
        from--; to--;
        addEdge(from, to, cap, cost);
    }

    int flow = 0, cost = 0;
    edmondsKarp(0, vertexNum - 1, flow, cost);
    cout << flow << " " << cost << endl;
    return 0;
}
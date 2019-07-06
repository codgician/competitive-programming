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
int dist[VERTEX_SIZE], lastVisitedEdge[VERTEX_SIZE]; 
bool inQueue[VERTEX_SIZE], hasVisited[VERTEX_SIZE];
int vertexNum, edgeNum;

void addEdge(int from, int to, int cap, int cost) {
    edge[edgePt] = {to, head[from], cap, cost};
    head[from] = edgePt++;
    edge[edgePt] = {from, head[to], 0, -cost};
    head[to] = edgePt++;
}

bool isFullFlow(int startPt, int endPt) {
    for (int i = 0; i < vertexNum; i++)
        dist[i] = INT_MAX, inQueue[i] = false;
    dist[startPt] = 0;
    deque<int> dq; dq.push_back(startPt);
    inQueue[startPt] = true;

    while (!dq.empty()) {
        int cntPt = dq.front();
        dq.pop_front();
        inQueue[cntPt] = false;

        for (int i = head[cntPt]; i != -1; i = edge[i].next) {
            int nextPt = edge[i].to;
            if (edge[i ^ 1].cap != 0 && dist[nextPt] > dist[cntPt] - edge[i].cost) {
                dist[nextPt] = dist[cntPt] - edge[i].cost;
                if (!inQueue[nextPt]) {
                    inQueue[nextPt] = true; 
                    if (!dq.empty() && dist[nextPt] < dist[dq.front()])
                        dq.push_front(nextPt);
                    else
                        dq.push_back(nextPt);
                }
            }
        }
    }
    return dist[endPt] != INT_MAX;
}

int findAguPath(int cntPt, int endPt, int minCap, int & cost) {
    if (cntPt == endPt) {
        hasVisited[endPt] = true;
        return minCap;
    }

    int cntFlow = 0;
    hasVisited[cntPt] = true;
    for (int & i = lastVisitedEdge[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (hasVisited[nextPt])
            continue;
        if (dist[cntPt] - edge[i].cost == dist[nextPt] && edge[i].cap > 0) {
            int flowInc = findAguPath(nextPt, endPt, min(minCap - cntFlow, edge[i].cap), cost);
            if (flowInc != 0) {
                cost += flowInc * edge[i].cost;
                edge[i].cap -= flowInc;
                edge[i ^ 1].cap += flowInc;
                cntFlow += flowInc;
            }
            if (cntFlow == minCap)
                break;
        }
    }
    return cntFlow;
}

void zkw(int startPt, int endPt, int & flow, int & cost) {
    flow = 0, cost = 0;
    while (isFullFlow(endPt, startPt)) {
        hasVisited[endPt] = true;
        while (hasVisited[endPt]) {
            for (int i = 0; i < vertexNum; i++)
                lastVisitedEdge[i] = head[i], hasVisited[i] = false;
            flow += findAguPath(startPt, endPt, INT_MAX, cost);
        }
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
    zkw(0, vertexNum - 1, flow, cost);
    cout << flow << " " << cost << endl;
    return 0;
}
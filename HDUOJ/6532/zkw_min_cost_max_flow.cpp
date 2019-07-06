#include <bits/stdc++.h>
using namespace std;

#define SIZE 510
#define VERTEX_SIZE 2010
#define EDGE_SIZE 40200

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

bool isFullFlow(int startPt, int endPt) {
    for (int i = 0; i < vertexNum; i++)
        dis[i] = INT_MAX;
    memset(inQueue, false, sizeof(inQueue));
    dis[startPt] = 0;
    queue<int> q;
    q.push(startPt);
    inQueue[startPt] = true;

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
    return dis[endPt] != INT_MAX;
}

int findAugPath(int cntPt, int endPt, int minCap, int & cost) {
    if (cntPt == endPt) {
        hasVisited[endPt] = true;
        return minCap;
    }
    int cntFlow = 0;
    hasVisited[cntPt] = true;
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (hasVisited[nextPt])
            continue;
        if (dis[cntPt] - edge[i].cost == dis[nextPt] && edge[i].capacity > 0) {
            int flowInc = findAugPath(nextPt, endPt, min(minCap - cntFlow, edge[i].capacity), cost);
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

void zkw(int startPt, int endPt, int & flow, int & cost) {
    flow = 0, cost = 0;
    while (isFullFlow(endPt, startPt)) {
        hasVisited[endPt] = true;
        while (hasVisited[endPt]) {
            memset(hasVisited, false, sizeof(hasVisited));
            flow += findAugPath(startPt, endPt, INT_MAX, cost);
        }
    }
}

typedef struct _Chess {
    int x, y;
} Chess;
Chess arr[SIZE];

int rowDsc[SIZE], colDsc[SIZE], rowNum, colNum;
int rowLim[SIZE], colLim[SIZE];

/*
    Chess:  [0, v << 1)
    Row:    [v << 1, (v << 1) + R)
    Column: [(v << 1) + R, (v << 1) + R + C)
    Source: (v << 1) + R + C; Sink: (v << 1) + R + C + 1
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    while (cin >> vertexNum) {
        memset(head, -1, sizeof(head));
        edgePt = 0;

        for (int i = 0; i < vertexNum; i++) {
            cin >> arr[i].x >> arr[i].y;
            rowDsc[i] = arr[i].x; colDsc[i] = arr[i].y;
            addEdge(i << 1, i << 1 | 1, 1, -(i + 1));
        }

        sort(rowDsc + 0, rowDsc + vertexNum);
        sort(colDsc + 0, colDsc + vertexNum);
        rowNum = unique(rowDsc + 0, rowDsc + vertexNum) - rowDsc;
        colNum = unique(colDsc + 0, colDsc + vertexNum) - colDsc;

        for (int i = 0; i < vertexNum; i++) {
            int rowId = lower_bound(rowDsc + 0, rowDsc + rowNum, arr[i].x) - rowDsc;
            int colId = lower_bound(colDsc + 0, colDsc + colNum, arr[i].y) - colDsc;
            addEdge((vertexNum << 1) + rowId, i << 1, 1, 0);
            addEdge(i << 1 | 1, (vertexNum << 1) + rowNum + colId, 1, 0);
        }

        for (int i = 0; i < rowNum; i++)
            rowLim[i] = INT_MAX;
        for (int i = 0; i < colNum; i++)
            colLim[i] = INT_MAX;

        int limNum;
        cin >> limNum;
        while (limNum--) {
            char typ;
            int id, val;
            cin >> typ >> id >> val;
            if (typ == 'R') {
                // row
                id = lower_bound(rowDsc + 0, rowDsc + rowNum, id) - rowDsc;
                if (id < rowNum)
                    rowLim[id] = min(rowLim[id], val);
            } else {
                // column
                id = lower_bound(colDsc + 0, colDsc + colNum, id) - colDsc;
                if (id < colNum)
                    colLim[id] = min(colLim[id], val);
            }
        }

        int srcPt = (vertexNum << 1) + rowNum + colNum;
        int snkPt = srcPt + 1;

        addEdge(srcPt, (vertexNum << 1) + 0, rowLim[0], 0);
        for (int i = 1; i < rowNum; i++)
            addEdge((vertexNum << 1) + i - 1, (vertexNum << 1) + i, rowLim[i], 0);
        addEdge((vertexNum << 1) + rowNum + 0, snkPt, colLim[0], 0);
        for (int i = 1; i < colNum; i++)
            addEdge((vertexNum << 1) + rowNum + i, (vertexNum << 1) + rowNum + i - 1, colLim[i], 0);

        vertexNum = snkPt + 1;
        int flow = 0, cost = 0;
        zkw(srcPt, snkPt, flow, cost);
        cout << -cost << '\n';
    }

    return 0;
}

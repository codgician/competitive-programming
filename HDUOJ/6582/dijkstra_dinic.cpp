#include <bits/stdc++.h>
using namespace std;

#define VERTEX_SIZE 10010
#define EDGE_SIZE 20020

typedef struct _Edge {
    int to, next;
    long long int cap;
} Edge;

Edge edge[3][EDGE_SIZE];
int head[3][VERTEX_SIZE], edgePt[3];
int depth[VERTEX_SIZE], lastVisitedEdge[VERTEX_SIZE], vertexNum;

void addEdge(int id, int from, int to, long long int cap){
    edge[id][edgePt[id]] = {to, head[id][from], cap};
    head[id][from] = edgePt[id]++;
    if (id == 2) {
        edge[id][edgePt[id]] = {from, head[id][to], 0};
        head[id][to] = edgePt[id]++;
    }
}

bool updateDepth(int startPt, int endPt) {
    memset(depth, -1, sizeof(depth));
    queue<int> q;
    depth[startPt] = 0;
    q.push(startPt);
    while (!q.empty()) {
        int cntPt = q.front();
        q.pop();
        for (int i = head[2][cntPt]; i != -1; i = edge[2][i].next) {
            int nextPt = edge[2][i].to;
            if (depth[nextPt] == -1 && edge[2][i].cap > 0) {
                depth[nextPt] = depth[cntPt] + 1;
                if (nextPt == endPt)
                    return true;
                q.push(nextPt);
            }
        }
    }
    return false;
}

long long int findAugPath(int cntPt, int endPt, long long int minCap) {
    if (cntPt == endPt)
        return minCap;
    long long int cntFlow = 0;
    for (int & i = lastVisitedEdge[cntPt]; i != -1; i = edge[2][i].next) {
        int nextPt = edge[2][i].to;
        if (depth[nextPt] == depth[cntPt] + 1 && edge[2][i].cap > 0) {
            long long int flowInc = findAugPath(nextPt, endPt, min(minCap - cntFlow, edge[2][i].cap));
            if (flowInc == 0) {
                depth[nextPt] = -1;
            } else {
                edge[2][i].cap -= flowInc;
                edge[2][i ^ 1].cap += flowInc;
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
            lastVisitedEdge[i] = head[2][i];
        long long int flowInc =  findAugPath(srcPt, snkPt, INT_MAX);
        if (flowInc == 0)
            break;
        ret += flowInc;
    }
    return ret;
}

long long int dist[2][VERTEX_SIZE];

void dijkstra(int id, int startPt) {
    priority_queue<
        pair<long long int, int>,
        vector<pair<long long int, int> >,
        greater<pair<long long int, int> >
    > pq;
    fill(dist[id] + 0, dist[id] + vertexNum, LLONG_MAX);
    dist[id][startPt] = 0;
    pq.push(make_pair(dist[id][startPt], startPt));
    while (!pq.empty()) {
        auto p = pq.top(); pq.pop();
        for (int i = head[id][p.second]; i != -1; i = edge[id][i].next) {
            int nextPt = edge[id][i].to;
            if (p.first > dist[id][nextPt])
                continue;
            if (dist[id][nextPt] > dist[id][p.second] + edge[id][i].cap) {
                dist[id][nextPt] = dist[id][p.second] + edge[id][i].cap;
                pq.push(make_pair(dist[id][nextPt], nextPt));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int edgeNum;
        cin >> vertexNum >> edgeNum;
        fill(head[0] + 0, head[0] + vertexNum, -1);
        fill(head[1] + 0, head[1] + vertexNum, -1);
        fill(head[2] + 0, head[2] + vertexNum, -1);
        edgePt[0] = 0; edgePt[1] = 0; edgePt[2] = 0;
        for (int i = 0; i < edgeNum; i++) {
            int from, to, len; cin >> from >> to >> len;
            from--; to--;
            addEdge(0, from, to, len);
            addEdge(1, to, from, len);
        }

        dijkstra(0, 0); dijkstra(1, vertexNum - 1);

        for (int i = 0; i < edgePt[0]; i++) {
            int from = edge[1][i].to, to = edge[0][i].to; long long int len = edge[0][i].cap;
            if (dist[0][from] + dist[1][to] + len == dist[0][vertexNum - 1])
                addEdge(2, from, to, len);
        }

        cout << dinic(0, vertexNum - 1) << '\n';
    }

    return 0;
}
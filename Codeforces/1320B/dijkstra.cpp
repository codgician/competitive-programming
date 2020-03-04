#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

class Edge {
public:
    int to, next;
};

Edge edges[2][SIZE << 1];
int head[2][SIZE], edgesPt[2];
int dist[SIZE], vertexNum, len;
vector<int> path; bool vis[SIZE];

void addEdge(int id, int from, int to) {
    edges[id][edgesPt[id]] = {to, head[id][from]};
    head[id][from] = edgesPt[id]++;
}

void dijkstra(int startPt) {
    for (int i = 0; i < vertexNum; i++)
        vis[i] = false, dist[i] = INT_MAX;
    vis[startPt] = 0; dist[startPt] = 0;
    priority_queue<pair<long long int, int> > pq;
    pq.push(make_pair(-dist[startPt], startPt));

    while (!pq.empty()) {
        int cntPt = pq.top().second; pq.pop(); 
        if (vis[cntPt]) 
            continue;
        vis[cntPt] = true;

        for (int i = head[0][cntPt]; i != -1; i = edges[0][i].next) {
            int nextPt = edges[0][i].to;
            if (dist[nextPt] > dist[cntPt] + 1) {
                dist[nextPt] = dist[cntPt] + 1;
                pq.push(make_pair(-dist[nextPt], nextPt));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int edgeNum;
    cin >> vertexNum >> edgeNum;
    for (int t = 0; t < 2; t++)
        fill(head[t] + 0, head[t] + vertexNum, -1), edgesPt[t] = 0;
    for (int i = 0; i < edgeNum; i++) {
        int from, to; cin >> from >> to; from--; to--; 
        addEdge(0, to, from); addEdge(1, from, to);
    }

    cin >> len;
    for (int i = 0; i < len; i++) {
        int pt; cin >> pt; pt--;
        path.push_back(pt);
    }

    dijkstra(path.back());

    int minv = 0, maxv = 0;
    for (int i = 0; i < len - 1; i++)
        minv += (dist[path[i]] != dist[path[i + 1]] + 1);
    for (int i = 0; i < len - 1; i++) {
        int cntPt = path[i], inc = 0;
        for (int j = head[1][cntPt]; j != -1; j = edges[1][j].next) {
            int nextPt = edges[1][j].to;
            if (path[i + 1] == nextPt) {
                inc |= (dist[nextPt] + 1 != dist[cntPt]);
            } else {
                inc |= (dist[nextPt] + 1 == dist[cntPt]); 
            }
        }
        maxv += inc;
    }

    cout << minv << ' ' << maxv << '\n';
    return 0;
}
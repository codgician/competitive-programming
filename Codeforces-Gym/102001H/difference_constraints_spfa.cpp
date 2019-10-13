#include <bits/stdc++.h>
using namespace std;

#define VERTEX_SIZE 100010
#define EDGE_SIZE 300010

class Edge {
public:
    int to, next, len;
};

Edge edges[EDGE_SIZE];
int head[VERTEX_SIZE], edgesPt, vertexNum;
int dist[VERTEX_SIZE], cnt[VERTEX_SIZE]; bool inQueue[VERTEX_SIZE];

void addEdge(int from, int to, int len) {
    edges[edgesPt] = {to, head[from], len};
    head[from] = edgesPt++;
}

bool spfa() {
    for (int i = 0; i < vertexNum; i++)
        dist[i] = INT_MIN, inQueue[i] = false;
    queue<int> q;
    for (int i = 0; i < vertexNum; i++) {
        cnt[i] = 0; dist[i] = 0;
        inQueue[i] = true; q.push(i);
    }

    while (!q.empty()) {
        int cntPt = q.front(); q.pop(); inQueue[cntPt] = false;
        for (int i = head[cntPt]; i != -1; i = edges[i].next) {
            int nextPt = edges[i].to;
            if (dist[nextPt] < dist[cntPt] + edges[i].len) {
                dist[nextPt] = dist[cntPt] + edges[i].len;
                cnt[nextPt] = cnt[cntPt] + 1;
                if (cnt[nextPt] >= vertexNum)
                    return false;
                if (!inQueue[nextPt]) {
                    q.push(nextPt); inQueue[nextPt] = true;
                }
            }
        }
    }
        
    return true;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int consNum; cin >> vertexNum >> consNum;
    fill(head + 0, head + vertexNum + 2, -1); edgesPt = 0;
    for (int i = 1; i <= vertexNum; i++) {
        int cnt; cin >> cnt;
        if (cnt == 0) {
            // Not prefilled
            addEdge(i - 1, i, 0);
            addEdge(i, i - 1, -1);
        } else if (cnt == 1) {
            // Prefill 1
            addEdge(i - 1, i, 1);
            addEdge(i, i - 1, -1);
        } else {
            // Prefill -1
            addEdge(i - 1, i, 0);
            addEdge(i, i - 1, 0);
        }
    }

    vertexNum++;
    for (int i = 0; i < consNum; i++) {
        int a, b, c; cin >> a >> b >> c;
        addEdge(a - 1, b, (c - (a - b - 1) + 1) >> 1);
    }

    if (!spfa()) {
        cout << "Impossible\n";
    } else {
        for (int i = 1; i < vertexNum; i++)
            cout << (dist[i] - dist[i - 1] > 0 ? 1 : -1) << ' ';
        cout << '\n';
    }

    return 0;
}
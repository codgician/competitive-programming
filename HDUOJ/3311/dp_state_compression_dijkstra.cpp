#include <bits/stdc++.h>
using namespace std;

#define KEY_SIZE 6
#define VERTEX_SIZE 1010
#define EDGE_SIZE 20010

typedef struct _Edge {
    int to, next, len;
} Edge;

Edge edge[EDGE_SIZE];
int head[VERTEX_SIZE], edgePt;

int dp[1 << KEY_SIZE][VERTEX_SIZE];
bool vis[VERTEX_SIZE];

priority_queue<
    pair<int, int>,
    vector<pair<int, int> >,
    greater<pair<int, int> >
> pq;

void addEdge(int from, int to, int len) {
    edge[edgePt] = {to, head[from], len};
    head[from] = edgePt++;
}

void dijkstra(int st) {
    while (!pq.empty()) {
        auto p = pq.top(); pq.pop();
        if (p.first > dp[st][p.second])
            continue;
        for (int i = head[p.second]; i != -1; i = edge[i].next) {
            int nextPt = edge[i].to;
            if (dp[st][nextPt] > dp[st][p.second] + edge[i].len) {
                dp[st][nextPt] = dp[st][p.second] + edge[i].len;
                pq.push(make_pair(dp[st][nextPt], nextPt));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int keyNum, rstNum, edgeNum;
    while (cin >> keyNum >> rstNum >> edgeNum) {
        keyNum++; int vertexNum = keyNum + rstNum; edgePt = 0;
        fill(head + 0, head + vertexNum, -1);
        for (int i = 1; i < vertexNum; i++) {
            int cnt; cin >> cnt;
            addEdge(0, i, cnt); addEdge(i, 0, cnt);
        }
        for (int i = 0; i < edgeNum; i++) {
            int from, to, len; cin >> from >> to >> len;
            addEdge(from, to, len); addEdge(to, from, len);
        }

        for (int st = 0; st < (1 << keyNum); st++)
            fill(dp[st] + 0, dp[st] + vertexNum, INT_MAX);
        for (int i = 0; i < keyNum; i++)
            dp[1 << i][i] = 0;

        for (int st = 0; st < (1 << keyNum); st++) {
            for (int i = 0; i < vertexNum; i++) {
                for (int subst = st & (st - 1); subst > 0; subst = st & (subst - 1)) 
                    if (dp[subst][i] != INT_MAX && dp[st ^ subst][i] != INT_MAX)
                        dp[st][i] = min(dp[st][i], dp[subst][i] + dp[st ^ subst][i]);
                if (dp[st][i] != INT_MAX)
                    pq.push(make_pair(dp[st][i], i)); 
            }
            dijkstra(st); 
        }

        cout << dp[(1 << keyNum) - 1][0] << '\n';
    }

    return 0;
}
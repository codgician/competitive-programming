#include <bits/stdc++.h>
using namespace std;

#define VERTEX_SIZE 51
#define EDGE_SIZE 2010

typedef struct _Edge {
    int to, next, len;
} Edge;

Edge edge[EDGE_SIZE];
int head[VERTEX_SIZE], edgePt;

void addEdge(int from, int to, int len) {
    edge[edgePt] = {to, head[from], len};
    head[from] = edgePt++;
}

int dp[1 << 10][VERTEX_SIZE], dp1[1 << 10];

priority_queue<
    pair<int, int>,
    vector<pair<int, int> >,
    greater<pair<int, int> >
> pq;

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

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int vertexNum, edgeNum, k; edgePt = 0;
        cin >> vertexNum >> edgeNum >> k;
        fill(head + 0, head + vertexNum, -1);
        for (int i = 0; i < edgeNum; i++) {
            int from, to, len; cin >> from >> to >> len;
            from--; to--;
            addEdge(from, to, len); addEdge(to, from, len);
        }

        for (int st = 0; st < (1 << (k << 1)); st++) 
            dp1[st] = INT_MAX, fill(dp[st] + 0, dp[st] + vertexNum, INT_MAX);
        for (int i = 0; i < k; i++)
            dp[1 << i][i] = 0;
        for (int i = 0; i < k; i++)
            dp[1 << (k + i)][vertexNum - 1 - i] = 0;

        for (int st = 0; st < (1 << (k << 1)); st++) {
            for (int i = 0; i < vertexNum; i++) {
                for (int subst = st & (st - 1); subst > 0; subst = st & (subst - 1)) 
                    if (dp[subst][i] != INT_MAX && dp[st ^ subst][i] != INT_MAX)
                        dp[st][i] = min(dp[st][i], dp[subst][i] + dp[st ^ subst][i]);
                if (dp[st][i] != INT_MAX)
                    pq.push(make_pair(dp[st][i], i)); 
            }
            dijkstra(st); 
        }

        for (int st = 0; st < (1 << (k << 1)); st++) 
            if (__builtin_popcount(st >> k) == __builtin_popcount(st & ((1 << k) - 1)))
                for (int i = 0; i < vertexNum; i++)
                    dp1[st] = min(dp1[st], dp[st][i]);

        for (int st = 0; st < (1 << (k << 1)); st++)
            for (int subst = st & (st - 1); subst > 0; subst = st & (subst - 1)) 
                if (dp1[subst] != INT_MAX && dp1[st ^ subst] != INT_MAX)
                    dp1[st] = min(dp1[st], dp1[subst] + dp1[st ^ subst]);

        if (dp1[(1 << (k << 1)) - 1] == INT_MAX)
            cout << "No solution\n";
        else
            cout << dp1[(1 << (k << 1)) - 1] << '\n';
    }

    return 0;
}
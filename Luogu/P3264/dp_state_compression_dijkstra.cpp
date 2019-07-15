#include <bits/stdc++.h>
using namespace std;

#define VERTEX_SIZE 1010
#define EDGE_SIZE 6010
#define KEY_SIZE 11

typedef struct _Edge {
    int to, next, cost;
} Edge;

Edge edge[EDGE_SIZE];
int head[VERTEX_SIZE], edgePt;

pair<int, int> arr[KEY_SIZE]; map<int, int> mp;
int dp[1 << KEY_SIZE][VERTEX_SIZE], dp1[1 << KEY_SIZE];

void addEdge(int from, int to, int cost) {
    edge[edgePt] = {to, head[from], cost};
    head[from] = edgePt++;
}

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
            if (dp[st][nextPt] > dp[st][p.second] + edge[i].cost) {
                dp[st][nextPt] = dp[st][p.second] + edge[i].cost;
                pq.push(make_pair(dp[st][nextPt], nextPt));
            }
        }
    }
}

bool check(int st1, int st2) {
    for (const auto & p : mp)
        if ((st1 & p.second) != p.second && (st2 & p.second) != p.second)
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int vertexNum, edgeNum, keyNum;
    cin >> vertexNum >> edgeNum >> keyNum;
    fill(head + 0, head + vertexNum, -1); edgePt = 0;
    for (int i = 0; i < edgeNum; i++) {
        int from, to, cost; cin >> from >> to >> cost;
        from--; to--;
        addEdge(from, to, cost); addEdge(to, from, cost);
    }

    for (int i = 0; i < keyNum; i++) {
        cin >> arr[i].second >> arr[i].first;
        arr[i].first--; mp[arr[i].second] += (1 << i);
    }

    for (int st = 0; st < (1 << keyNum); st++)
        dp1[st] = INT_MAX, fill(dp[st] + 0, dp[st] + vertexNum, INT_MAX);
    for (int i = 0; i < keyNum; i++)
        dp[1 << i][arr[i].first] = 0;

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

    for (int st = 0; st < (1 << keyNum); st++)
        for (int i = 0; i < vertexNum; i++)
            dp1[st] = min(dp1[st], dp[st][i]);
    for (int st = 0; st < (1 << keyNum); st++)
        for (int subst = st & (st - 1); subst > 0; subst = st & (subst - 1)) 
            if (check(subst, st ^ subst) && dp1[subst] != INT_MAX && dp1[st ^ subst] != INT_MAX)
                dp1[st] = min(dp1[st], dp1[subst] + dp1[st ^ subst]);

    cout << dp1[(1 << keyNum) - 1] << '\n';
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define KEY_SIZE 8
#define VERTEX_SIZE 31
#define EDGE_SIZE 2010

typedef struct _Edge {
    int to, next, len;
} Edge;

Edge edge[EDGE_SIZE];
int head[VERTEX_SIZE], edgePt;

int dp[1 << KEY_SIZE][VERTEX_SIZE], dp1[1 << KEY_SIZE], keyArr[KEY_SIZE];

map<string, int> mp;

void addEdge(int from, int to, int len) {
    edge[edgePt] = {to, head[from], len};
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
            if (dp[st][nextPt] > dp[st][p.second] + edge[i].len) {
                dp[st][nextPt] = dp[st][p.second] + edge[i].len;
                pq.push(make_pair(dp[st][nextPt], nextPt));
            }
        }
    }
}

bool check(int st) {
    for (int i = 0; i < KEY_SIZE; i += 2) {
        int cnt = (1 << i) + (1 << (i + 1));
        if ((st & cnt) != 0 && (st & cnt) != cnt)
            return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int vertexNum, edgeNum, cntId = 0; edgePt = 0;
    cin >> vertexNum >> edgeNum;
    fill(head + 0, head + vertexNum, -1);
    for (int i = 0; i < vertexNum; i++) {
        string str; cin >> str;
        mp[str] = cntId++;
    }

    for (int i = 0; i < edgeNum; i++) {
        string from, to; int len;
        cin >> from >> to >> len;
        addEdge(mp[from], mp[to], len);
        addEdge(mp[to], mp[from], len);
    }

    for (int i = 0; i < KEY_SIZE; i++) {
        string str; cin >> str;
        keyArr[i] = mp[str];
    }

    for (int st = 0; st < (1 << KEY_SIZE); st++)
        dp1[st] = INT_MAX, fill(dp[st] + 0, dp[st] + vertexNum, INT_MAX);
    for (int i = 0; i < KEY_SIZE; i++)
        dp[1 << i][keyArr[i]] = 0;

    for (int st = 0; st < (1 << KEY_SIZE); st++) {
        for (int i = 0; i < vertexNum; i++) {
            for (int subst = st & (st - 1); subst > 0; subst = st & (subst - 1))
                if (dp[subst][i] != INT_MAX && dp[st ^ subst][i] != INT_MAX)
                    dp[st][i] = min(dp[st][i], dp[subst][i] + dp[st ^ subst][i]);
            if (dp[st][i] != INT_MAX)
                pq.push(make_pair(dp[st][i], i));
        }
        dijkstra(st);
    }

    for (int st = 0; st < (1 << KEY_SIZE); st++)
        for (int i = 0; i < vertexNum; i++)
            dp1[st] = min(dp1[st], dp[st][i]);
    for (int st = 0; st < (1 << KEY_SIZE); st++)
       for (int subst = st & (st - 1); subst > 0; subst = st & (subst - 1))
            if (dp1[subst] != INT_MAX && dp1[st ^ subst] != INT_MAX && check(subst) && check(st ^ subst))
                dp1[st] = min(dp1[st], dp1[subst] + dp1[st ^ subst]);
    cout << dp1[(1 << KEY_SIZE) - 1] << '\n';

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define VERTEX_SIZE 210
#define EDGE_SIZE 40010

typedef struct _Circle {
    int x, y, r;
} Circle;

Circle arr[VERTEX_SIZE];

long long int sqr(long long int num) {
    return num * num;
}

bool check(Circle & fst, Circle & snd) {
    return sqr(fst.r + snd.r) >= sqr(fst.x - snd.x) + sqr(fst.y - snd.y);
}

typedef struct _Edge {
    int to, next, len;
} Edge;

Edge edge[EDGE_SIZE];
int head[VERTEX_SIZE], edgePt;

int dp[1 << 3][VERTEX_SIZE];

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int vertexNum; cin >> vertexNum; edgePt = 0;
        fill(head + 0, head + vertexNum, -1); 
        for (int i = 0; i < vertexNum; i++) {
            cin >> arr[i].x >> arr[i].y >> arr[i].r;
            for (int j = 0; j < i; j++) {
                if (check(arr[i], arr[j])) {
                    addEdge(i, j, 1); addEdge(j, i, 1);
                }
            }
        }

        for (int st = 0; st < (1 << 3); st++)
            fill(dp[st] + 0, dp[st] + vertexNum, INT_MAX);
        for (int i = 0; i < 3; i++)
            dp[1 << i][i] = 0;

        for (int st = 0; st < (1 << 3); st++) {
            for (int i = 0; i < vertexNum; i++) {
                for (int subst = st & (st - 1); subst > 0; subst = st & (subst - 1)) 
                    if (dp[subst][i] != INT_MAX && dp[st ^ subst][i] != INT_MAX)
                        dp[st][i] = min(dp[st][i], dp[subst][i] + dp[st ^ subst][i]);
                if (dp[st][i] != INT_MAX)
                    pq.push(make_pair(dp[st][i], i)); 
            }
            dijkstra(st); 
        }
        cout << (dp[(1 << 3) - 1][0] == INT_MAX ? -1 : vertexNum - dp[(1 << 3) - 1][0] - 1) << '\n';
    }
    return 0;
}
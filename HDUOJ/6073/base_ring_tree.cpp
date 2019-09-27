#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

#define SIZE 600010

class Edge {
public:
    int to, next, len;
};

Edge edges[SIZE << 1];
int head[SIZE], edgesPt, deg[SIZE];
bool vis[SIZE], inStack[SIZE]; long long int cnt[2], ans;

void addEdge(int from, int to, int len) {
    edges[edgesPt] = {to, head[from], len};
    head[from] = edgesPt++;
}

void dfs(int cntPt, int col) {
    for (int i = head[cntPt]; i != -1; i = edges[i].next) {
        int nextPt = edges[i].to;
        if (vis[nextPt])
            continue;
        vis[nextPt] = true;
        cnt[col] = cnt[col] * edges[i].len % mod;
        dfs(nextPt, col ^ 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int vertexNum; cin >> vertexNum;
        fill(head + 0, head + (vertexNum << 1), -1);
        fill(deg + 0, deg + (vertexNum << 1), 0);
        fill(vis + 0, vis + (vertexNum << 1), false);
        fill(inStack + 0, inStack + (vertexNum << 1), false);
        edgesPt = 0; ans = 1;

        for (int i = 0; i < vertexNum; i++) {
            for (int t = 0; t < 2; t++) {
                int pt, len; cin >> pt >> len; pt--;
                addEdge(i, vertexNum + pt, len);
                addEdge(vertexNum + pt, i, len);
                deg[i]++; deg[vertexNum + pt]++;
            }
        }

        queue<pair<int, bool> > q;
        for (int i = vertexNum; i < (vertexNum << 1); i++)
            if (deg[i] == 1)
                q.push(make_pair(i, true)), vis[i] = true;
        while (!q.empty()) {
            auto p = q.front(); q.pop();
            for (int i = head[p.first]; i != -1; i = edges[i].next) {
                int nextPt = edges[i].to;
                if (vis[nextPt])
                    continue;
                deg[nextPt]--;
                if (p.second == true)
                    ans = ans * edges[i].len % mod;
                if (deg[nextPt] == 1)
                    q.push(make_pair(nextPt, p.second ^ 1)), vis[nextPt] = true;
            }
        }

        for (int i = 0; i < (vertexNum << 1); i++) {
            if (!vis[i]) {
                cnt[0] = 1, cnt[1] = 1; dfs(i, 0);
                ans = ans * (cnt[0] + cnt[1]) % mod;
            }
        }
        cout << ans << '\n';
    }
    
    return 0;
}
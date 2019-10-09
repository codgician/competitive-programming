#include <bits/stdc++.h>
using namespace std;

#define SIZE 5010
const int mod = 1e9 + 7;

typedef struct _Edge {
    int to, next;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE], edgePt, vertexNum;
int keyNum, lim;

long long int dp[SIZE][SIZE], cnt[SIZE];
int depth[SIZE];
bool isKey[SIZE];

void addEdge(int from, int to) {
    edge[edgePt] = {to, head[from]};
    head[from] = edgePt++;
}

void dfs(int cntPt, int fatherPt) {
    depth[cntPt] = 0;
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (nextPt == fatherPt)
            continue;
        dfs(nextPt, cntPt);
        depth[cntPt] = max(depth[cntPt], depth[nextPt] + 1);
    }

    for (int i = 0; i <= depth[cntPt]; i++)
        dp[cntPt][i] = 0;

    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (nextPt == fatherPt)
            continue;

        for (int i = 0; i <= depth[cntPt]; i++)
            cnt[i] = dp[cntPt][i];

        // One subtree
        for (int j = 0; j <= depth[nextPt]; j++)
            cnt[j + 1] = (cnt[j + 1] + dp[nextPt][j]) % mod;

        // Two subtrees
        for (int i = 0; i <= depth[cntPt] && i <= lim; i++)
            for (int j = 0; j <= depth[nextPt] && i + j + 1 <= lim; j++)
                cnt[max(i, j + 1)] = (cnt[max(i, j + 1)] + 1ll * dp[cntPt][i] * dp[nextPt][j] % mod) % mod;

        for (int i = 0; i <= depth[cntPt]; i++)
            dp[cntPt][i] = cnt[i];
    }

    if (isKey[cntPt]) {
        dp[cntPt][0] = 1;
        // Select / Neglect current subtree root produce two different valid sets.
        for (int i = 1; i <= depth[cntPt] && i <= lim; i++)
            dp[cntPt][i] = (dp[cntPt][i] << 1) % mod;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    while (cin >> vertexNum >> keyNum >> lim) {
        for (int i = 0; i < vertexNum; i++)
            head[i] = -1, isKey[i] = false;
        edgePt = 0;
        for (int i = 1; i < vertexNum; i++) {
            int from, to;
            cin >> from >> to;
            from--; to--;
            addEdge(from, to);
            addEdge(to, from);
        }

        for (int i = 0; i < keyNum; i++) {
            int cntPt; 
            cin >> cntPt;
            isKey[cntPt - 1] = true;
        }

        dfs(0, -1);
        long long int ans = 0;
        for (int j = 0; j <= depth[0] && j <= lim; j++)
            ans = (ans + dp[0][j]) % mod;
        cout << ans << '\n';
    }
    return 0;
}
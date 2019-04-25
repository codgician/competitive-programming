#include <bits/stdc++.h>
using namespace std;

#define SIZE 20010

typedef struct _Edge {
    int to, next, len;
} Edge;
Edge edge[SIZE << 1];
int head[SIZE], edgePt, vertexNum;

long long int dp[SIZE][3], ans;

void addEdge(int from, int to, int len) {
    edge[edgePt] = {to, head[from], len};
    head[from] = edgePt++;
}

void dfs(int cntPt, int fatherPt) {
    dp[cntPt][0] = 1;
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (nextPt == fatherPt)
            continue;
        dfs(nextPt, cntPt);
        for (int j = 0; j < 3; j++)
            ans += (dp[nextPt][j] * dp[cntPt][(6 - j - edge[i].len) % 3]) << 1;
        for (int j = 0; j < 3; j++)
            dp[cntPt][(j + edge[i].len) % 3] += dp[nextPt][j];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(head, -1, sizeof(head));
    memset(dp, 0, sizeof(dp));
    edgePt = 0;
    cin >> vertexNum;
    for (int i = 1; i < vertexNum; i++) {
        int from, to, len;
        cin >> from >> to >> len;
        from--, to--, len %= 3;
        addEdge(from, to, len);
        addEdge(to, from, len);
    }

    ans = 0;
    dfs(0, -1);
    ans += vertexNum;
    long long tot = 1ll * vertexNum * vertexNum;
    long long int gcd = __gcd(ans, tot);
    cout << ans / gcd << "/" << tot / gcd << endl;
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

typedef struct _Edge {
    int to, next;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE], edgePt, vertexNum;
int dp[SIZE], maxLen;

void addEdge(int from, int to) {
    edge[edgePt] = {to, head[from]};
    head[from] = edgePt++;
}

void dfs(int cntPt, int fatherPt) {
    dp[cntPt] = 0;
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (nextPt == fatherPt)
            continue;
        dfs(nextPt, cntPt);
        int cntLen = dp[nextPt] + 1;
        if (cntLen + dp[cntPt] > maxLen)
            maxLen = cntLen + dp[cntPt];
        dp[cntPt] = max(dp[cntPt], cntLen);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(head, -1, sizeof(head));
    edgePt = 0;
    cin >> vertexNum;
    for (int i = 1; i < vertexNum; i++) {
        int from, to;
        cin >> from >> to;
        from--; to--;
        addEdge(from, to);
        addEdge(to, from);
    }

    maxLen = 0;
    dfs(0, -1); maxLen++;
    int ans = (maxLen % 3 != 2);
    cout << (ans ? "First\n" : "Second\n");
    return 0;
}

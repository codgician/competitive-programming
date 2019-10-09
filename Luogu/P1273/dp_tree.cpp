#include <bits/stdc++.h>
using namespace std;

#define SIZE 3010

typedef struct _Edge {
    int to, next;
    int cost;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE], vertexNum, edgePt;
int user[SIZE], dp[SIZE][SIZE], userNum;

void addEdge(int from, int to, int cost) {
    edge[edgePt] = {to, head[from], cost};
    head[from] = edgePt++;
}

int dfs(int cntPt, int fatherPt) {
    dp[cntPt][0] = 0;
    if (cntPt >= vertexNum - userNum) {
        dp[cntPt][1] = user[cntPt - (vertexNum - userNum)];
        return 1;
    }

    int cntNum = 0;
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (nextPt == fatherPt)
            continue;
        cntNum += dfs(nextPt, cntPt);
        for (int j = cntNum; j > 0; j--) {
            for (int k = 0; k <= j; k++) {
                if (dp[nextPt][k] == INT_MIN || dp[cntPt][j - k] == INT_MIN)
                    continue;
                dp[cntPt][j] = max(dp[cntPt][j], dp[nextPt][k] + dp[cntPt][j - k] - edge[i].cost);
            }
        }
    }
    return cntNum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(head, -1, sizeof(head));
    edgePt = 0;
    cin >> vertexNum >> userNum;
    for (int i = 0; i < vertexNum - userNum; i++) {
        int num;
        cin >> num;
        for (int j = 0; j < num; j++) {
            int to, cost;
            cin >> to >> cost;
            to--;
            addEdge(i, to, cost);
            addEdge(to, i, cost);
        }
    }
    for (int i = 0; i < userNum; i++)
        cin >> user[i];

    for (int i = 0; i < vertexNum; i++)
        for (int j = 0; j <= userNum; j++)
            dp[i][j] = INT_MIN;
    dfs(0, -1);
    int ans = 0;
    for (int i = 0; i <= userNum; i++)
        if (dp[0][i] >= 0)
            ans = max(ans, i);
    cout << ans << endl;
    return 0;
}
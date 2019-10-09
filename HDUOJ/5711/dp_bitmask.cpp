#include <bits/stdc++.h>
using namespace std;

#define SIZE 17
#define STATE_SIZE (1 << 17)

pair<int, int> arr[SIZE];
int dp[STATE_SIZE][SIZE];
int dist[SIZE][SIZE], vertexNum, edgeNum;

void floyd() {
    for (int k = 0; k < vertexNum; k++)
        for (int i = 0; i < vertexNum; i++)
            for (int j = 0; j < vertexNum; j++)
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++) {
        int hackLim, lenLim;
        cin >> vertexNum >> edgeNum >> hackLim >> lenLim;
        vertexNum++;
        for (int i = 0; i < vertexNum; i++)
            for (int j = 0; j < vertexNum; j++)
                dist[i][j] = (i == j ? 0 : INT_MAX);
        arr[0] = make_pair(0, 0);
        for (int i = 1; i < vertexNum; i++)
            cin >> arr[i].first;
        for (int i = 1; i < vertexNum; i++)
            cin >> arr[i].second;
        for (int i = 0; i < edgeNum; i++) {
            int from, to, len;
            cin >> from >> to >> len;
            dist[from][to] = min(dist[from][to], len);
            dist[to][from] = min(dist[to][from], len);
        }

        floyd();

        for (int st = 0; st < (1 << vertexNum); st++)
            for (int i = 0; i < vertexNum; i++)
                dp[st][i] = INT_MAX;
        
        dp[0][0] = 0;
        for (int i = 0; i < vertexNum; i++)
            if (dist[0][i] != INT_MAX)
                dp[1 << i][i] = dist[0][i];
        for (int st = 1; st < (1 << vertexNum); st++) {
            for (int i = 0; i < vertexNum; i++) {
                if (!(st & (1 << i)))
                    continue;
                for (int j = 0; j < vertexNum; j++)
                    if (!(st & (1 << j)))
                        dp[st | (1 << j)][j] = min(dp[st | (1 << j)][j], dp[st][i] + dist[i][j]);
            }
        }

        int ans = 0;
        for (int st = 1; st < (1 << vertexNum); st++) {
            bool canExtend = false;
            for (int i = 0; i < vertexNum && !canExtend; i++)
                if ((st & (1 << i)) && dp[st][i] + dist[i][0] <= lenLim)
                    canExtend = true;
            if (!canExtend)
                continue;
            priority_queue<pair<int, int> > pq;
            for (int i = 0; i < vertexNum; i++)
                if (st & (1 << i))
                    pq.push(arr[i]);
            int cntAns = 0;
            for (int i = 0; i < hackLim && pq.size(); i++) {
                auto cntTop = pq.top();
                pq.pop();
                cntAns += cntTop.first;
                cntTop.first -= cntTop.second;
                if (cntTop.first >= 0)
                    pq.push(cntTop);
            }
            ans = max(ans, cntAns);
        }
        cout << "Case " << t << ": " << ans << endl; 
    }
    return 0;
}
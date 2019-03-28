#include <bits/stdc++.h>
using namespace std;

#define SIZE 55
#define LOG_SIZE 64

bool dp[SIZE][SIZE][LOG_SIZE], arr[SIZE][SIZE], isShortest[SIZE];
int dist[SIZE], vertexNum;

void dijkstra(int startPt) {
    for (int i = 0; i < vertexNum; i++) {
        dist[i] = arr[startPt][i] ? 1 : INT_MAX;
        isShortest[i] = false;
    }
    dist[startPt] = 0;

    for (int t = 0; t < vertexNum - 1; t++) {
        int minLen = INT_MAX, minPt = -1;
        for (int i = 0; i < vertexNum; i++)
            if (!isShortest[i] && dist[i] < minLen)
                minLen = dist[i], minPt = i;
        if (minPt == -1)
            break;
        isShortest[minPt] = true;
        for (int i = 0; i < vertexNum; i++)
            if (arr[minPt][i])
                dist[i] = min(dist[i], dist[minPt] + arr[minPt][i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(dp, false, sizeof(dp));
    memset(arr, false, sizeof(arr));
    int edgeNum;
    cin >> vertexNum >> edgeNum;
    for (int i = 0; i < edgeNum; i++) {
        int from, to;
        cin >> from >> to;
        from--, to--;
        dp[from][to][0] = true;
        arr[from][to] = true;
    }

    for (int t = 0; t < LOG_SIZE - 1; t++) {
        for (int j = 0; j < vertexNum; j++) {
            for (int i = 0; i < vertexNum; i++) {
                for (int k = 0; k < vertexNum; k++) {
                    if (dp[i][j][t] && dp[j][k][t]) {
                        dp[i][k][t + 1] = true;
                        arr[i][k] = true;
                    }
                }
            }
        }
    }

    dijkstra(0);
    cout << dist[vertexNum - 1] << endl;

    return 0;
}
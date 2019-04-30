#include <bits/stdc++.h>
using namespace std;

#define SIZE 17
#define STATE_SIZE (1 << 17)

int arr[SIZE][SIZE];
int dp[STATE_SIZE][SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        int vertexNum, edgeNum;
        cin >> vertexNum >> edgeNum;
        for (int i = 0; i < vertexNum; i++)
            for (int j = 0; j < vertexNum; j++)
                arr[i][j] =  i == j ? 0 : INT_MAX;
        for (int i = 0; i < (1 << vertexNum); i++)
            for (int j = 0; j < vertexNum; j++)
                dp[i][j] = INT_MAX;

        for (int i = 0; i < edgeNum; i++) {
            int from, to, len;
            cin >> from >> to >> len;
            from--; to--;
            arr[from][to] = min(arr[from][to], len);
            arr[to][from] = min(arr[to][from], len);
        }

        dp[0][0] = 0;
        for (int i = 0; i < vertexNum; i++)
            if (arr[0][i] != INT_MAX)
                dp[1 << i][i] = arr[0][i];

        for (int st = 1; st < (1 << vertexNum); st++) {
            int repNum = __builtin_popcount(st);
            for (int k = 0; k < repNum; k++) {
                for (int i = 0; i < vertexNum; i++) {
                    if (dp[st][i] == INT_MAX || !(st & (1 << i)))
                        continue;
                    for (int j = 0; j < vertexNum; j++)
                        if (arr[i][j] != INT_MAX)
                            dp[st | (1 << j)][j] = min(dp[st | (1 << j)][j], dp[st][i] + arr[i][j]);
                }
            }
        }

        cout << dp[(1 << vertexNum) - 1][0] << '\n';
    }

    return 0;
}
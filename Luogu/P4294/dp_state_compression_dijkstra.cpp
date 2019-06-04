#include <bits/stdc++.h>
using namespace std;

#define SIZE 15
#define STATE_SIZE 1025

int arr[SIZE][SIZE], dp[STATE_SIZE][SIZE][SIZE];
int row, column, keyPt, dir[2][4] = {1, -1, 0, 0, 0, 0, 1, -1};
pair<int, pair<int, int> > pre[STATE_SIZE][SIZE][SIZE]; // <Last vertex, Last state>
bool ans[SIZE][SIZE];

bool canMove(int x, int y) {
    return x >= 0 && x < row && y >= 0 && y < column;
}

priority_queue<pair<int, pair<int, int> >> pq;

void dijkstra(int st) {
    while (!pq.empty()) {
        pair<int, pair<int, int> > cntTop = pq.top();
        pq.pop();
        int x = cntTop.second.first, y = cntTop.second.second;
        for (int i = 0; i < 4; i++) {
            int x1 = x + dir[0][i], y1 = y + dir[1][i];
            if (!canMove(x1, y1) || dp[st][x][y] == INT_MAX)
                continue;
            if (dp[st][x1][y1] > dp[st][x][y] + arr[x1][y1]) {
                dp[st][x1][y1] = dp[st][x][y] + arr[x1][y1];
                pre[st][x1][y1] = make_pair(st, make_pair(x, y));
                pq.push(make_pair(-dp[st][x1][y1], make_pair(x1, y1)));
            }
        }
    }
}

void storAns(int x, int y, int st) {
    if (pre[st][x][y].first == -1) 
        return;
    ans[x][y] = true;
    int x1 = pre[st][x][y].second.first, y1 = pre[st][x][y].second.second;
    if (x1 == x && y1 == y)
        storAns(x, y, st ^ pre[st][x][y].first);
    storAns(x1, y1, pre[st][x][y].first);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> row >> column; keyPt = 0; int xr = -1, yr = -1;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            for (int st = 0; st < STATE_SIZE; st++)
                dp[st][i][j] = INT_MAX, pre[st][i][j] = make_pair(-1, make_pair(-1, -1));
            ans[i][j] = false;
            cin >> arr[i][j];
            if (arr[i][j] == 0) {
                dp[1 << keyPt][i][j] = 0;
                xr = i; yr = j; keyPt++;
            }
        }
    }

    for (int st = 1; st < (1 << keyPt); st++) {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                for (int subst = st & (st - 1); subst > 0; subst = st & (subst - 1)) {
                    if (dp[subst][i][j] == INT_MAX || dp[st ^ subst][i][j] == INT_MAX)
                        continue;
                    if (dp[st][i][j] > dp[subst][i][j] + dp[st ^ subst][i][j] - arr[i][j]) {
                        dp[st][i][j] = dp[subst][i][j] + dp[st ^ subst][i][j] - arr[i][j];
                        pre[st][i][j] = make_pair(subst, make_pair(i, j));
                    }
                }
                if (dp[st][i][j] != INT_MAX) {
                    pq.push(make_pair(-dp[st][i][j], make_pair(i, j)));
                }
            }
        }
        dijkstra(st);
    }

    cout << dp[(1 << keyPt) - 1][xr][yr] << '\n';
    storAns(xr, yr, (1 << keyPt) - 1);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cout << (arr[i][j] == 0 ? 'x' : (ans[i][j] ? 'o' : '_'));
        }
        cout << '\n';
    }

    return 0;
}
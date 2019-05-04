#include <bits/stdc++.h>
using namespace std;

#define SIZE 1010

typedef struct _Cord {
    int x, y;
    int num;
} Cord;

queue<Cord> q;
bool arr[SIZE][SIZE];
int dir[2][4] = {1, -1, 0, 0, 0, 0, -1, 1};
int row, column;

bool canMove(int x, int y) {
    return x >= 0 && x < row && y >= 0 && y < column && !arr[x][y];
}

int bfs() {
    int ans = 0;
    while (!q.empty()) {
        Cord cntState = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int x1 = cntState.x + dir[0][i], y1 = cntState.y + dir[1][i];
            if (!canMove(x1, y1))
                continue;
            arr[x1][y1] = true;
            Cord nextState = {x1, y1, cntState.num + 1};
            ans = max(ans, nextState.num);
            q.push(nextState);
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> row >> column;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            char ch;
            cin >> ch;
            if (ch == '#') {
                // Black
                arr[i][j] = true;
                q.push({i, j, 0});
            } else {
                // White
                arr[i][j] = false;
            }
        }
    }

    int ans = bfs();
    cout << ans << '\n';
    return 0;
}

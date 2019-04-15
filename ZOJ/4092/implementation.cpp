#include <bits/stdc++.h>
using namespace std;

#define SIZE 2010
#define INS_SIZE 250

int arr[SIZE][SIZE], ins[INS_SIZE], vis[SIZE][SIZE];
int dir[2][4] = {-1, 1, 0, 0, 0, 0, -1, 1};
int cons[4]= {27, 9, 3, 1};
int row, column;

bool canMove(int x, int y) {
    return x > 0 && y > 0 && x < row - 1 && y < column - 1 && arr[x][y] != 1;
}

long long int solve(int sx, int sy, long long int step) {
    int x = sx, y = sy;
    int ans = 0;
    while (step--) {
        int insPt = 81 * arr[x][y];
        for (int i = 0; i < 4; i++) {
            int x1 = x + dir[0][i], y1 = y + dir[1][i];
            insPt += cons[i] * arr[x1][y1];
        }

        if (vis[x][y] == ans)
            break;
        vis[x][y] = ans;

        if (ins[insPt] == 4 && arr[x][y] == 2) {
            arr[x][y] = 0;
            ans++;
        } else if (ins[insPt] < 4) {
            int x1 = x + dir[0][ins[insPt]], y1 = y + dir[1][ins[insPt]];
            if (canMove(x1, y1))
                x = x1, y = y1;
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        int sx, sy;
        long long int step;
        cin >> row >> column;
        cin >> sx >> sy >> step;
        sx--, sy--;
        for (int i = 0; i < 243; i++) {
            char ch;
            cin >> ch;
            if (ch == 'U')
                ins[i] = 0;
            else if (ch == 'D')
                ins[i] = 1;
            else if (ch == 'L')
                ins[i] = 2;
            else if (ch == 'R')
                ins[i] = 3;
            else if (ch == 'P')
                ins[i] = 4;
            else
                ins[i] = 5;
        }

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                char ch;
                cin >> ch;
                arr[i][j] = ch - '0';
                vis[i][j] = -1;
            }
        }

        cout << solve(sx, sy, step) << '\n';
    }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define SIZE 1000010

vector<int> pfx[SIZE], dist[SIZE];
vector<bool> arr[SIZE];
int dirs[2][8] = {-1, -1, -1, 0, 0, 1, 1, 1, -1, 0, 1, -1, 1, -1, 0, 1};
int row, col;

void bfs(int ans) {
    cout << ans << '\n';
    queue<pair<int, int> > q;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (arr[i][j]) {
                dist[i][j] = -1;
            } else {
                dist[i][j] = 0; q.push(make_pair(i, j));
            }
        }
    }

    while (!q.empty()) {
        int x = q.front().first, y = q.front().second; q.pop();
        for (int i = 0; i < 8; i++) {
            int x1 = x + dirs[0][i], y1 = y + dirs[1][i];
            if (x1 < 0 || x1 >= row || y1 < 0 || y1 >= col || dist[x1][y1] != -1)
                continue;
            dist[x1][y1] = dist[x][y] + 1; 
            q.push(make_pair(x1, y1));
        }
    }

    for (int i = 1; i < row - 1; i++) {
        for (int j = 1; j < col - 1; j++)
            cout << (dist[i][j] > ans ? 'X' : '.');
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> row >> col; row += 2; col += 2;
    for (int i = 0; i < row; i++)
        arr[i].resize(col), pfx[i].resize(col), dist[i].resize(col);
    for (int i = 1; i < row - 1; i++) {
        for (int j = 1; j < col - 1; j++) {
            char ch; cin >> ch;
            arr[i][j] = ch == 'X'; pfx[i][j] = arr[i][j];
        }
    }
    
    for (int i = 0; i < row; i++)
        for (int j = 1; j < col; j++)
            pfx[i][j] += pfx[i][j - 1];
    for (int j = 0; j < col; j++)
        for (int i = 1; i < row; i++)
            pfx[i][j] += pfx[i - 1][j];

    int ans = INT_MAX;
    for (int i = 1; i < row - 1; i++) {
        for (int j = 1; j < col - 1; j++) {
            if (!arr[i][j])
                continue;
            int typ = -1;
            if (!arr[i - 1][j] && !arr[i][j - 1]) {
                typ = 0;
            } else if (!arr[i - 1][j] && !arr[i][j + 1]) {
                typ = 1;
            } else if (!arr[i + 1][j] && !arr[i][j - 1]) {
                typ = 2;
            } else if (!arr[i + 1][j] && !arr[i][j + 1]) {
                typ = 3;
            }

            if (typ == -1)
                continue;
 
            int leftPt = 1, rightPt = min(row, col), ret = 0;
            while (leftPt <= rightPt) {
                int midPt = (leftPt + rightPt) >> 1;
                const auto sum = [](int xl, int yl, int xr, int yr) {
                    tie(xl, xr) = make_tuple(min(xl, xr), max(xl, xr));
                    tie(yl, yr) = make_tuple(min(yl, yr), max(yl, yr));
                    if (xl <= 0 || yl <= 0 || xr >= row - 1 || yr >= col - 1)
                        return 0;
                    return pfx[xr][yr] + pfx[xl - 1][yl - 1] - pfx[xr][yl - 1] - pfx[xl - 1][yr];
                };

                if (sum(i, j, i + ((typ >> 1) ? -1 : 1) * midPt, j + ((typ & 1) ? -1 : 1) * midPt) == (midPt + 1) * (midPt + 1)) {
                    leftPt = midPt + 1; ret = midPt;
                } else {
                    rightPt = midPt - 1;
                }
            }
            ans = min(ans, ret);
        }
    }

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            pfx[i][j] = arr[i][j];
    for (int i = 0; i < row; i++) {
        for (int j = 1; j < col; j++) {
            pfx[i][j] = (pfx[i][j] == 0 ? 0 : pfx[i][j - 1] + 1);
            if (pfx[i][j - 1] != 0 && pfx[i][j] == 0)
                ans = min(ans, pfx[i][j - 1] - 1);
        }
        if (pfx[i][col - 1] != 0)
            ans = min(ans, pfx[i][col - 1] - 1);
    }
 
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            pfx[i][j] = arr[i][j];
    for (int j = 0; j < col; j++) {
        for (int i = 1; i < row; i++) {
            pfx[i][j] = (pfx[i][j] == 0 ? 0 : pfx[i - 1][j] + 1);
            if (pfx[i - 1][j] != 0 && pfx[i][j] == 0)
                ans = min(ans, pfx[i - 1][j] - 1);
        }
        if (pfx[row - 1][j] != 0)
            ans = min(ans, pfx[row - 1][j] - 1);
    }

    bfs(ans >> 1);
    return 0;
}
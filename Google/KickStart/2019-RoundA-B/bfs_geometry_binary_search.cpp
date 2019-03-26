#include <bits/stdc++.h>
using namespace std;

#define SIZE 300

int arr[SIZE][SIZE], dist[SIZE][SIZE], maxDist;
int row, column, dir[2][4] = {1, -1, 0, 0, 0, 0, 1, -1};

void bfs() {
    queue<pair<int, int> > q;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (arr[i][j] == 1) {
                q.push(make_pair(i, j));
                dist[i][j] = 0;
            }
        }
    }

    while (!q.empty()) {
        pair<int, int> cnt = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int x1 = cnt.first + dir[0][i], y1 = cnt.second + dir[1][i];
            if (x1 < 0 || x1 > row || y1 < 0 || y1 > column || dist[x1][y1] != -1)
                continue;
            dist[x1][y1] = dist[cnt.first][cnt.second] + 1;
            maxDist = max(maxDist, dist[x1][y1]);
            q.push(make_pair(x1, y1));
        }
    }
}

bool check(int cntDist) {
    int maxFst = INT_MIN, minFst = INT_MAX;
    int maxSnd = INT_MIN, minSnd = INT_MAX;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (dist[i][j] > cntDist) {
                int cntFst = j - i, cntSnd = j + i;
                maxFst = max(maxFst, cntFst), minFst = min(minFst, cntFst);
                maxSnd = max(maxSnd, cntSnd), minSnd = min(minSnd, cntSnd);
            }
        }
    }

    if (maxFst == INT_MIN)
        return true;

    int cnt = max(abs(maxFst - minFst), abs(maxSnd - minSnd));
    if (abs(maxFst - minFst) == abs(maxSnd - minSnd) && (maxSnd - maxFst) & 1)
        cnt++;
    return cnt <= cntDist * 2;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++) {
        cin >> row >> column;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                char ch;
                cin >> ch;
                arr[i][j] = ch - '0';
            }
        }

        memset(dist, -1, sizeof(dist));
        maxDist = 0;
        bfs();

        int leftPt = 0, rightPt = maxDist, ans = maxDist;
        while (leftPt <= rightPt) {
            int midPt = (leftPt + rightPt) >> 1;
            if (check(midPt)) {
                rightPt = midPt - 1;
                ans = midPt;
            } else {
                leftPt = midPt + 1;
            }
        }
        cout << "Case #" << t << ": " << ans << endl;
    }

    return 0;
}
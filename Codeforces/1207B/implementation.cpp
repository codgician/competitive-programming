#include <bits/stdc++.h>
using namespace std;

#define SIZE 51

bool arr[SIZE][SIZE], vis[SIZE][SIZE];
int row, col; 
vector<pair<int, int> > vec;

bool check() {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (arr[i][j] && !vis[i][j]) 
                return false;
    return true;
}

void mark(int x, int y) {
    if (x + 1 < row && y + 1 < col && arr[x][y] && arr[x + 1][y] && arr[x][y + 1] && arr[x + 1][y + 1]) {
        vis[x][y] = true, vis[x + 1][y] = true, vis[x][y + 1] = true, vis[x + 1][y + 1] = true;
        vec.push_back(make_pair(x, y));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> row >> col;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            cin >> arr[i][j];

    memset(vis, false, sizeof(vis));
    for (int i = 0; i < row; i++) 
        for (int j = 0; j < col; j++)
            if (arr[i][j])
                mark(i, j);

    if (!check()) {
        cout << -1 << '\n';
    } else {
        cout << vec.size() << '\n';
        for (auto & p : vec)
            cout << p.first + 1 << ' ' << p.second + 1 << '\n';
    }

    return 0;
}
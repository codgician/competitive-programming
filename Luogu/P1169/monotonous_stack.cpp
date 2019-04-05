#include <bits/stdc++.h>
using namespace std;

#define SIZE 2010

int arr[SIZE][SIZE], row, column;
int height[SIZE], sqrAns, recAns;
stack<pair<int, int> > mstk;

void solve() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            height[j] = arr[i][j] + (i > 0 && arr[i][j] ? height[j] : 0);
        }
        mstk.push(make_pair(0, 0));
        for (int j = 0; j < column; j++) {
            int pt = j;
            while (!mstk.empty() && mstk.top().first >= height[j]) {
                recAns = max(recAns, mstk.top().first * (j - mstk.top().second));
                int side = min(mstk.top().first, j - mstk.top().second);
                sqrAns = max(sqrAns, side * side);
                pt = mstk.top().second;
                mstk.pop();
            }
            mstk.push(make_pair(height[j], pt));
        }
        while (!mstk.empty()) {
            recAns = max(recAns, mstk.top().first * (column - mstk.top().second));
            int side = min(mstk.top().first, column - mstk.top().second);
            sqrAns = max(sqrAns, side * side);
            mstk.pop();
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    sqrAns = 0, recAns = 0;
    cin >> row >> column;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cin >> arr[i][j];
            if ((i + j) & 1)
                arr[i][j] ^= 1;
        }
    }
    solve();
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            arr[i][j] ^= 1;
        }
    }
    solve();

    cout << sqrAns << endl << recAns << endl;
    return 0;
}
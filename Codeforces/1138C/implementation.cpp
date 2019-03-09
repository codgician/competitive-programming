#include <bits/stdc++.h>
using namespace std;

#define SIZE 1010

int arr[SIZE][SIZE], rowArr[SIZE][SIZE], colArr[SIZE][SIZE], ans[SIZE][SIZE];
int rowPt[SIZE], colPt[SIZE];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    int row, column;
    cin >> row >> column;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cin >> arr[i][j];
            rowArr[i][j] = arr[i][j];
            colArr[j][i] = arr[i][j];
        }
        sort(rowArr[i] + 0, rowArr[i] + column);
        rowPt[i] = unique(rowArr[i] + 0, rowArr[i] + column) - rowArr[i];
    }
    for (int j = 0; j < column; j++) {
        sort(colArr[j] + 0, colArr[j] + row);
        colPt[j] = unique(colArr[j] + 0, colArr[j] + row) - colArr[j];
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            ans[i][j] = max(rowPt[i], colPt[j]);
            int rowRank = lower_bound(rowArr[i] + 0, rowArr[i] + rowPt[i], arr[i][j]) - rowArr[i];
            int colRank = lower_bound(colArr[j] + 0, colArr[j] + colPt[j], arr[i][j]) - colArr[j];
            int delta = abs(rowRank - colRank);
            if (rowRank < colRank) {
                ans[i][j] = max(ans[i][j], rowPt[i] + delta);
            } else if (rowRank > colRank) {
                ans[i][j] = max(ans[i][j], colPt[j] + delta);
            }
        }
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

	return 0;
}
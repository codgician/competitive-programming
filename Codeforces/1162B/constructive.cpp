#include <bits/stdc++.h>
using namespace std;

#define SIZE 55

int arr[2][SIZE][SIZE], row, column;

bool check() {
    for (int t = 0; t < 2; t++) {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                if (i > 0 && arr[t][i - 1][j] >= arr[t][i][j])
                    return false;
                if (j > 0 && arr[t][i][j - 1] >= arr[t][i][j])
                    return false;
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> row >> column;
    for (int t = 0; t < 2; t++)
        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++)
                cin >> arr[t][i][j];
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            if (arr[0][i][j] > arr[1][i][j])
                swap(arr[0][i][j], arr[1][i][j]);

    if (check())
        cout << "Possible\n";
    else
        cout << "Impossible\n";
    return 0;
}
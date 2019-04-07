#include <bits/stdc++.h>
using namespace std;

#define SIZE 510

int arr[2][SIZE][SIZE];
int row, column;

bool check() {
    for (int i = 0; i < row; i++)
        if (arr[0][i][column - 1] != arr[1][i][column - 1])
            return false;
    for (int j = 0; j < column; j++)
        if (arr[0][row - 1][j] != arr[1][row - 1][j])
            return false;
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

    for (int t = 0; t < 2; t++) {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                if (arr[t][i][j] == 1) {
                    arr[t][i][j] = 0;
                    arr[t][i][column - 1] ^= 1;
                    arr[t][row - 1][j] ^= 1;
                    arr[t][row - 1][column - 1] ^= 1;
                }
            }
        }
    }

    if (check())
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}
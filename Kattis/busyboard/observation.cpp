#include <bits/stdc++.h>
using namespace std;

#define SIZE 1010

char fst[SIZE][SIZE], snd[SIZE][SIZE];
bool rows[SIZE], cols[SIZE]; int row, col;

bool check() {
    const auto identical = []() {
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                if (fst[i][j] != snd[i][j])
                    return false;
        return true;
    };

    if (identical())
        return true;

    // Pre row check
    for (int i = 0; i < row; i++) {
        int xNum = 0;
        for (int j = 0; j < col; j++)
            xNum += snd[i][j] == 'X';
        rows[i] = xNum <= 1;
    }

    // Pre col check
    for (int j = 0; j < col; j++) {
        int xNum = 0;
        for (int i = 0; i < row; i++)
            xNum += snd[i][j] == 'X';
        cols[j] = xNum <= 1;
    }

    for (int i = 0; i < row; i++) 
        for (int j = 0; j < col; j++) 
            if (fst[i][j] == 'X' && snd[i][j] == 'X' && (!rows[i] || !cols[j]))
                rows[i] = false, cols[j] = false;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (fst[i][j] == 'O' && snd[i][j] == 'X') {
                if (!rows[i] || !cols[j])
                    return false;
            } else if (fst[i][j] == 'X' && snd[i][j] == 'O') {
                if (!rows[i] && !cols[j])
                    return false;
            }
        }
    }

    int fstONum = 0, sndXNum = 0;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++) 
            if (rows[i] && cols[j])
                fstONum += fst[i][j] == 'O', sndXNum += snd[i][j] == 'X';
    return fstONum == 0 && sndXNum == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> row >> col;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            cin >> fst[i][j];
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            cin >> snd[i][j];
    cout << (check() ? 1 : 0) << '\n';
    return 0;
}
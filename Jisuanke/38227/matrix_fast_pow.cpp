#include <bits/stdc++.h>
using namespace std;

#define SIZE 4

const long long int mod = 1e9 + 7;

typedef struct _Matrix {
    long long int arr[SIZE][SIZE];
    int row, column;
    _Matrix(int pRow, int pColumn) {
        row = pRow;
        column = pColumn;
        memset(arr, 0, sizeof(arr));
    }
    _Matrix & operator + (const _Matrix & b) {
        //assert(row == b.row && column == b.column);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                arr[i][j] += b.arr[i][j];
                if (arr[i][j] >= mod)
                    arr[i][j] %= mod;
            }
        }
        return *this;
    }
    _Matrix operator * (const _Matrix & b) const {
        //assert(column == b.row);
        _Matrix ans(row, b.column);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < b.column; j++) {
                for (int k = 0; k < column; k++) {
                    ans.arr[i][j] += (arr[i][k] * b.arr[k][j]);
                    if (ans.arr[i][j] >= mod)
                        ans.arr[i][j] %= mod;
                }
            }
        }
        return ans;
    }
    _Matrix & operator = (const _Matrix & b) {
        memcpy(arr, b.arr, sizeof(b.arr));
        return *this;
    }

    void print() {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                cerr << arr[i][j] << " ";
            }
            cerr << endl;
        }
    }

} Matrix;

Matrix matrixFastPow(Matrix matrix, long long int n) {
    // assert(matrix.row == matrix.column);
    Matrix ans(matrix.row, matrix.column);
    for (int i = 0; i < matrix.row; i++)
        ans.arr[i][i] = 1;
    while (n > 0) {
        if (n & 1)
            ans = ans * matrix;
        matrix = matrix * matrix;
        n >>= 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    long long int n;
    cin >> n;

    Matrix base(2, 1), trans(2, 2);

    trans.arr[0][0] = 2;
    trans.arr[0][1] = 1;
    trans.arr[1][0] = 2;
    trans.arr[1][1] = 1;

    base.arr[0][0] = 1;
    base.arr[1][0] = 0;

    Matrix ans = matrixFastPow(trans, n - 1) * base;

    long long int ret = 0;
    for (int i = 0; i < 2; i++)
        ret = (ret + ans.arr[i][0]) % mod;
    cout << ret << '\n';

    return 0;
}
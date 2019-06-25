#include <bits/stdc++.h>
using namespace std;

#define SIZE 5

const int mod = 1e9 + 6;

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1;
    a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ret;
}

typedef struct _Matrix {
    long long int arr[SIZE][SIZE];
    int row, column;
    _Matrix(int pRow, int pColumn) {
        row = pRow;
        column = pColumn;
        memset(arr, 0, sizeof(arr));
    }
    _Matrix & operator + (const _Matrix & b) {
        assert(row == b.row && column == b.column);
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
        assert(column == b.row);
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
            for (int j = 0; j < column; j++)
                cerr << arr[i][j] << " ";
            cerr << endl;
        }
    }
} Matrix;

Matrix matrixFastPow(Matrix matrix, long long int n) {
    assert(matrix.row == matrix.column);
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

    long long int n, f1, f2, f3, c;
    cin >> n >> f1 >> f2 >> f3 >> c;
    if (n == 1) {
        cout << f1 << '\n';
        return 0;
    }
    if (n == 2) {
        cout << f2 << '\n';
        return 0;
    }
    if (n == 3) {
        cout << f3 << '\n';
        return 0;
    }

    long long int ans = 1;
    Matrix base1(3, 1), trans1(3, 3);

    trans1.arr[0][0] = 1;
    trans1.arr[0][1] = 1;
    trans1.arr[0][2] = 1;
    trans1.arr[1][0] = 1;
    trans1.arr[2][1] = 1;

    // For f1
    base1.arr[2][0] = 1;
    base1.print();
    Matrix ans1 = matrixFastPow(trans1, n - 3) * base1;
    ans = ans * fastPow(f1, ans1.arr[0][0], mod + 1) % (mod + 1); 

    // For f2
    memset(base1.arr, 0, sizeof(base1.arr));
    base1.arr[1][0] = 1;
    ans1 = matrixFastPow(trans1, n - 3) * base1;
    ans = ans * fastPow(f2, ans1.arr[0][0], mod + 1) % (mod + 1);

    // For f3
    memset(base1.arr, 0, sizeof(base1.arr));
    base1.arr[0][0] = 1;
    ans1 = matrixFastPow(trans1, n - 3) * base1;
    ans = ans * fastPow(f3, ans1.arr[0][0], mod + 1) % (mod + 1);

    // For c
    Matrix base2(5, 1), trans2(5, 5);
    base2.arr[3][0] = 1;
    base2.arr[4][0] = 1; 

    trans2.arr[0][0] = 1;
    trans2.arr[0][1] = 1;
    trans2.arr[0][2] = 1;
    trans2.arr[0][3] = 2;
    trans2.arr[1][0] = 1;
    trans2.arr[2][1] = 1;
    trans2.arr[3][3] = 1;
    trans2.arr[3][4] = 1;
    trans2.arr[4][4] = 1;

    Matrix ans2 = matrixFastPow(trans2, n - 3) * base2;
    ans = ans * fastPow(c, ans2.arr[0][0], mod + 1) % (mod + 1);
    cout << ans << '\n';

    return 0;
}
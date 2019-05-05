#include <bits/stdc++.h>
using namespace std;

#define SIZE 3

long long int mod = 1e9 + 7;

/* Matrix */

typedef struct _Matrix {
    long long int arr[SIZE][SIZE];
    int row, column;
    _Matrix(int pRow, int pColumn) {
        row = pRow;
        column = pColumn;
        memset(arr, 0, sizeof(arr));
    }
    _Matrix & operator + (const _Matrix & b) {
        // assert(row == b.row && column == b.column);
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
        // assert(column == b.row);
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

long long int fastPow(long long int a, long long int n) {
    long long int ans = 1;
    a %= mod;
    while (n > 0) {
        if (n & 1)
            ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

vector<int> fac;

void getFac(int num) {
    fac.clear();
    for (int i = 1; i * i <= num; i++) {
        if (num % i != 0)
            continue;
        fac.push_back(i);
        if (i * i != num)
            fac.push_back(num / i);
    }
}

int phi(int num) {
    int ret = num;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            ret -= ret / i;
            while (num % i == 0)
                num /= i;
        }
    }
    if (num > 1)
        ret -= ret / num;
    return ret;
}

long long int dp(int len, int color) {
    if (len == 1)
        return color;
    if (len == 2)
        return 1ll * color * (color - 1) % mod;
    if (len == 3)
        return 1ll * color * (color - 1) % mod * (color - 2) % mod;

    Matrix trans(2, 2), base(2, 1);
    trans.arr[0][0] = color - 2;
    trans.arr[0][1] = color - 1;
    trans.arr[1][0] = 1;
    trans.arr[1][1] = 0;

    base.arr[0][0] = 1ll * color * (color - 1) % mod * (color - 2) % mod;
    base.arr[1][0] = 1ll * color * (color - 1) % mod;

    Matrix ans = matrixFastPow(trans, len - 3) * base;
    return ans.arr[0][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int num, color;
    while (cin >> num >> color) {
        getFac(num);
        long long int ans = 0;
        for (auto i : fac) 
            if (i > 1)
                ans = (ans + phi(num / i) * dp(i, color - 1) % mod) % mod;
        ans = ans * fastPow(num, mod - 2) % mod;
        ans = ans * color % mod;
        cout << ans << '\n';
    }
    return 0;
}

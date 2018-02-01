#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 10
using namespace std;

long long int mod;

typedef struct _Matrix
{
    long long int arr[SIZE][SIZE];
    int row, column;

    _Matrix(int iRow, int iColumn)
    {
        row = iRow;
        column = iColumn;
        memset(arr, 0, sizeof(arr));
    }

    _Matrix &operator + (const _Matrix &b)
    {
        if (row != b.row || column != b.column)
        {
            return *this;
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                arr[i][j] += b.arr[i][j];
                if (arr[i][j] >= mod)
                    arr[i][j] %= mod;
            }
        }
        return *this;
    }

    _Matrix operator * (const _Matrix &b)
    {
        _Matrix ans(row, b.column);
        if (column != b.row)
        {
            return ans;
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < b.column; j++)
            {
                for (int k = 0; k < column; k++)
                {
                    ans.arr[i][j] += (arr[i][k] * b.arr[k][j]) % mod;
                    if (ans.arr[i][j] >= mod)
                        ans.arr[i][j] %= mod;
                }
            }
        }
        return ans;
    }

    _Matrix &operator = (const _Matrix &b)
    {
        memcpy(arr, b.arr, sizeof(b.arr));
        return *this;
    }

    void print()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                cout << arr[i][j];
                if (j < column - 1)
                    cout << " ";
                else
                    cout << endl;
            }
        }
    }
} Matrix;

Matrix matrixQuickPow(Matrix matrix, long long int n)
{
    Matrix ans(matrix.row, matrix.column);
    if (matrix.row != matrix.column)
    {
        return ans;
    }

    for (int i = 0; i < matrix.row; i++)
    {
        ans.arr[i][i] = 1;
    }
    while (n > 0)
    {
        if (n & 1)
        {
            ans = ans * matrix;
        }
        matrix = matrix * matrix;
        n >>= 1;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    long long int k;
    while (cin >> k >> mod)
    {
        if (k < 10)
        {
            cout << k % mod << endl;
        }
        else
        {
            Matrix mat(SIZE, SIZE), base(SIZE, 1);
            long long int tmp = 0;
            for (int i = 0; i < SIZE; i++)
            {
                cin >> mat.arr[0][i];
                base.arr[i][0] = 9 - i;
                if (i + 1 < SIZE)
                    mat.arr[i + 1][i] = 1;
            }
            Matrix ans = matrixQuickPow(mat, k - 9) * base;
            cout << ans.arr[0][0] << endl;
        }
    }
    return 0;
}

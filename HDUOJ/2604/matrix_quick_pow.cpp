#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 4
using namespace std;

long long int mod;

typedef struct _Matrix
{
    long long int arr[SIZE][SIZE];
    int row, column;

    _Matrix()
    {
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
        _Matrix ans;
        if (column != b.row)
        {
            return ans;
        }
        ans.row = row;
        ans.column = b.column;

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
    Matrix ans;
    if (matrix.row != matrix.column)
    {
        return ans;
    }
    ans.row = matrix.row;
    ans.column = matrix.column;

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
    int len;
    Matrix mat, base;
    mat.row = 4;
    mat.column = 4;
    mat.arr[0][0] = 1;
    mat.arr[0][2] = 1;
    mat.arr[0][3] = 1;
    mat.arr[1][0] = 1;
    mat.arr[2][1] = 1;
    mat.arr[3][2] = 1;
    base.row = 4;
    base.column = 1;
    base.arr[0][0] = 9;
    base.arr[1][0] = 6;
    base.arr[2][0] = 4;
    base.arr[3][0] = 2;
    while (cin >> len >> mod)
    {
        if (len == 0)
        {
            cout << 0 << endl;
        }
        else if (len <= 4)
        {
            cout << base.arr[4 - len][0] % mod << endl;
        }
        else
        {
            Matrix ans = matrixQuickPow(mat, len - 4) * base;
            cout << ans.arr[0][0] % mod << endl;
        }
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
#include <cassert>
using namespace std;

#define SIZE 9

const int mod = 1e9 + 7;

typedef struct _Matrix
{
    long long int arr[SIZE][SIZE];
    int row, column;

    _Matrix(int pRow, int pColumn)
    {
        row = pRow;
        column = pColumn;
        memset(arr, 0, sizeof(arr));
    }

    _Matrix(int pRow, int pColumn, long long int pArr[][SIZE])
    {
        row = pRow;
        column = pColumn;
        for (int i = 0; i < pRow; i++)
        {
            for (int j = 0; j < pColumn; j++)
            {
                arr[i][j] = pArr[i][j];
            }
        }
    }

    _Matrix &operator + (const _Matrix &b)
    {
        assert(row == b.row && column == b.column);

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
        assert(column == b.row);

        _Matrix ans(row, b.column);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < b.column; j++)
            {
                for (int k = 0; k < column; k++)
                {
                    ans.arr[i][j] += (arr[i][k] * b.arr[k][j]);
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
    assert(matrix.row == matrix.column);

    Matrix ans(matrix.row, matrix.column);
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

long long int tmp[SIZE][SIZE] = {
    0, 0, 0, 1 ,0 ,0, 1, 0, 0,
    1, 0, 0, 0 ,0 ,0, 1 ,0, 0,
    1, 0, 0, 1 ,0 ,0, 1 ,0, 0,
    0, 1, 0, 0 ,1 ,0, 0 ,0, 0,
    0, 1, 0, 0 ,0 ,0, 0 ,1, 0,
    0, 0, 0, 0 ,1 ,0, 0 ,1, 0,
    0, 0, 1, 0 ,0 ,1, 0 ,0, 1,
    0, 0, 1, 0 ,0 ,0, 0 ,0, 1,
    0, 0, 1, 0 ,0 ,1, 0 ,0, 0
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    Matrix trans(9, 9, tmp);

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        long long int len;
        cin >> len;
        if (len == 1)
        {
            cout << 3 << endl;
            continue;
        }
        else if (len == 2)
        {
            cout << 9 << endl;
            continue;
        }

        Matrix ret = matrixQuickPow(trans, len - 2);

        long long int ans = 0;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                ans += ret.arr[i][j];
                if (ans >= mod)
                    ans %= mod;
            } 
        }
        cout << ans << endl;
    }

    return 0;
}
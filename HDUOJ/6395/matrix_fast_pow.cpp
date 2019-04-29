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
using namespace std;

#define SIZE 5

const long long int mod = 1e9 + 7;

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

    _Matrix & operator + (const _Matrix &b)
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

    _Matrix operator * (const _Matrix & b) const
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

    _Matrix operator = (const _Matrix & b)
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
                cerr << arr[i][j];
                if (j < column - 1)
                    cerr << " ";
                else
                    cerr << endl;
            }
        }
    }
} Matrix;

Matrix matrixFastPow(Matrix matrix, long long int n)
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
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int A, B, C, D, P, n;
        cin >> A >> B >> C >> D >> P >> n;

        if (n == 1)
        {
            cout << A << endl;
            continue;
        }
        else if (n == 2)
        {
            cout << B << endl;
            continue;
        }

        Matrix base(3, 1);
        base.arr[0][0] = B;
        base.arr[1][0] = A;
        base.arr[2][0] = 1;

        Matrix trans(3, 3);
        trans.arr[0][0] = D; 
        trans.arr[0][1] = C; 
        trans.arr[1][0] = 1; 
        trans.arr[1][1] = 0; 
        trans.arr[1][2] = 0; 
        trans.arr[2][0] = 0; 
        trans.arr[2][1] = 0; 
        trans.arr[2][2] = 1;

        Matrix ans(3, 1);
        bool isFirst = true;

        for (int l = 3, r; l <= n; l = r + 1)
        {
            if (P / l == 0)
                r = n;
            else
                r = P / (P / l);
            if (r >= n)
                r = n;

            int blockLen = r - l + 1;
            
            trans.arr[0][2] = P / l;

            if (isFirst)
            {
                isFirst = false;
                ans = matrixFastPow(trans, blockLen) * base;
            }
            else
            {
                ans = matrixFastPow(trans, blockLen) * ans;
            }
        }

        cout << ans.arr[0][0] % mod << endl;
    }
    return 0;
}
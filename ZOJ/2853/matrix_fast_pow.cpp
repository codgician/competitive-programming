#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 201
using namespace std;

typedef struct _Matrix
{
    double arr[SIZE][SIZE];
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
                    ans.arr[i][j] += (arr[i][k] * b.arr[k][j]);
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

Matrix matrixFastPow(Matrix matrix, int n)
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
    int speciesNum, subProcessNum;
    while (cin >> speciesNum >> subProcessNum)
    {
        if (speciesNum == 0 && subProcessNum == 0)
            break;

        Matrix base(speciesNum, 1);
        for (int i = 0; i < speciesNum; i++)
        {
            cin >> base.arr[i][0];
        }

        Matrix trans(speciesNum, speciesNum);
        for (int i = 0; i < speciesNum; i++)
        {
            trans.arr[i][i] = 1;
        }

        int ruleNum;
        cin >> ruleNum;
        for (int i = 0; i < ruleNum; i++)
        {
            int from, to;
            double percent;
            cin >> from >> to >> percent;
            trans.arr[to][from] += percent;
            trans.arr[from][from] -= percent;
        }

        Matrix ans = matrixFastPow(trans, subProcessNum) * base;
        cout << fixed << setprecision(0) << ans.arr[speciesNum - 1][0] << endl;
    }
    return 0;
}

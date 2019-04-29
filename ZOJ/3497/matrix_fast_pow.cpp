#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 25
using namespace std;

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
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        int row, column;
        scanf("%d%d", &row, &column);
        getchar();
        Matrix mat(row * column, row * column);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                int x[4], y[4];
                scanf("((%d,%d),(%d,%d),(%d,%d),(%d,%d))", &x[0], &y[0], &x[1], &y[1], &x[2], &y[2], &x[3], &y[3]);
                getchar();
                if (i == row - 1 && j == column - 1)
                    continue;
                for (int k = 0; k < 4; k++)
                {
                    mat.arr[i * column + j][(x[k] - 1) * column + y[k] - 1] = 1;
                }
            }
        }

        int queryNum;
        scanf("%d", &queryNum);
        while (queryNum--)
        {
            int p;
            scanf("%d", &p);
            Matrix ans = matrixFastPow(mat, p);
            if (ans.arr[0][row * column - 1] == 0)
            {
                printf("False\n");
            }
            else
            {
                bool flag = true;
                for (int i = 0; i < row * column - 1; i++)
                {
                    if (ans.arr[0][i])
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    printf("True\n");
                }
                else
                {
                    printf("Maybe\n");
                }
            }
        }
        printf("\n");
    }
    return 0;
}

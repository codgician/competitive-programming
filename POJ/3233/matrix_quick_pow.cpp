#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 31
using namespace std;

int matrixSize;
long long int mod;

typedef struct _Matrix
{
    long long int arr[SIZE][SIZE];

    _Matrix()
    {
        memset(arr, 0, sizeof(arr));
    }

    _Matrix &operator + (const _Matrix &b)
    {
        for (int i = 0; i < matrixSize; i++)
        {
            for (int j = 0; j < matrixSize; j++)
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
        for (int i = 0; i < matrixSize; i++)
        {
            for (int j = 0; j < matrixSize; j++)
            {
                for (int k = 0; k < matrixSize; k++)
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
} Matrix;

void printMatrix(Matrix matrix)
{
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            if (matrix.arr[i][j] >= mod)
                matrix.arr[i][j] %= mod;
            cout << matrix.arr[i][j];
            if (j < matrixSize - 1)
                cout << " ";
            else
                cout << endl;
        }
    }
}

Matrix matrixQuickPow(Matrix matrix, long long int n)
{
    Matrix ans;
    for (int i = 0; i < matrixSize; i++)
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

Matrix solve(Matrix a, long long int k)
{
    if (k == 1)
        return a;

    Matrix ans, tmp1 = solve(a, k >> 1);
    if (k & 1)
    {
        Matrix tmp2 = matrixQuickPow(a, (k + 1) >> 1);
        return tmp1 + tmp2 + tmp1 * tmp2;
    }
    else
    {
        Matrix tmp2 = matrixQuickPow(a, k >> 1);
        return tmp1 + tmp1 * tmp2;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    long long int k;
    cin >> matrixSize >> k >> mod;
    Matrix a;
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            cin >> a.arr[i][j];
            if (a.arr[i][j] >= mod)
                a.arr[i][j] %= mod;
        }
    }
    Matrix ans;
    ans = solve(a, k);
    printMatrix(ans);
    return 0;
}

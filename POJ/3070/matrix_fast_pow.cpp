#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 2
#define MOD 10000
using namespace std;

typedef struct _Matrix
{
    int arr[SIZE][SIZE];
    _Matrix()
    {
        memset(arr, 0, sizeof(arr));
    }
    _Matrix operator * (const _Matrix b)
    {
        _Matrix ans;
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < SIZE; k++)
                {
                    ans.arr[i][j] += arr[i][k] * b.arr[k][j];
                    ans.arr[i][j] %= MOD;
                }
            }
        }
        return ans;
    }
    _Matrix operator = (const _Matrix b)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                arr[i][j] = b.arr[i][j];
            }
        }
    }
} Matrix;


Matrix matrixFastPow(Matrix matrix, int n)
{
    Matrix ans;
    for (int i = 0; i < SIZE; i++)
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
    int n;
    while (cin >> n)
    {
        if (n == -1)
            break;
        Matrix ans;
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                ans.arr[i][j] = 1;
            }
        }
        ans.arr[1][1] = 0;
        ans = matrixFastPow(ans, n);
        cout << ans.arr[0][1] << endl;
    }
    return 0;
}

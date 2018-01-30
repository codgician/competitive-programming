#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 11
#define MOD 9973
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

Matrix matrixQuickPow(Matrix matrix, int n)
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
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int n, k;
        cin >> n >> k;
        Matrix mat;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> mat.arr[i][j];
            }
        }
        mat = matrixQuickPow(mat, k);
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            ans += mat.arr[i][i];
            if (ans > MOD)
                ans %= MOD;
        }
        cout << ans << endl;
    }
    return 0;
}

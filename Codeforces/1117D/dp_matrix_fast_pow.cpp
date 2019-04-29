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
#include <bitset>
#include <cassert>
using namespace std;

const long long int mod = 1e9 + 7;

#define SIZE 110

long long int factorialArr[SIZE], invFactorialArr[SIZE];

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

    _Matrix & operator + (const _Matrix & b)
    {
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

    _Matrix operator * (const _Matrix & b) const
    {
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

    _Matrix & operator = (const _Matrix & b)
    {
        memcpy(arr, b.arr, sizeof(b.arr));
        return *this;
    }

} Matrix;

Matrix matrixFastPow(Matrix matrix, long long int n)
{
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

long long int fastPow(long long int a, long long int n)
{
    long long int ans = 1;
    a %= mod;
    while (n > 0)
    {
        if (n & 1)
            ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

void initFactorial()
{
    factorialArr[0] = 1;
    for (int i = 1; i < SIZE; i++)
        factorialArr[i] = factorialArr[i - 1] * i % mod;
}

void initInvFactorial()
{
    invFactorialArr[SIZE - 1] = fastPow(factorialArr[SIZE - 1], mod - 2);
    for (int i = SIZE - 2; i >= 0; i--)
        invFactorialArr[i] = invFactorialArr[i + 1] * (i + 1) % mod;
}

long long int getComb(int n, int m)
{
    if (m > n)
        return 0;
    return factorialArr[n] * invFactorialArr[m] % mod * invFactorialArr[n - m] % mod;
}

long long int naive(int len, int num)
{
    long long int ans = 0;
    for (int i = 0; i <= len / num; i++)
    {
        ans += getComb(len - i * (num - 1), i) % mod;
        ans %= mod;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    initFactorial();
    initInvFactorial();

    long long int len, num;
    cin >> len >> num;

    if (len <= num)
    {
        cout << naive(len, num) << endl;
        return 0;
    }

    // dp[i] = dp[i - 1] + dp[i - len]
    Matrix base(num, 1), trans(num, num);
    for (int i = 1; i <= num; i++)
        base.arr[num - i][0] = naive(i, num);
    trans.arr[0][0] = 1;
    trans.arr[0][num - 1] = 1;
    for (int i = 1; i < num; i++)
        trans.arr[i][i - 1] = 1; 

    Matrix res = matrixFastPow(trans, len - num) * base;
    cout << res.arr[0][0] << endl;
    return 0;
}
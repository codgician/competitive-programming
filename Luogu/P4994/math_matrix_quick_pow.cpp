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

#define SIZE 4

long long int mod;

vector<pair<int, int> > facArr;
vector<int> facArr2;

long long int quickPow(long long int a, long long int n)
{
    long long int ans = 1;
    while (n > 0)
    {
        if (n & 1)
            ans = ans * a;
        a = a * a;
        n >>= 1;
    }
    return ans;
}

long long int quickPowMod(long long int a, long long int n)
{
    long long int ans = 1;
    a %= mod;
    while (n > 0)
    {
        if (n & 1)
            ans = ans * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return ans;
}


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

    _Matrix & operator + (const _Matrix & b)
    {
        assert(row == b.row && column == b.column);

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++)
            {
                arr[i][j] += b.arr[i][j];
                if (arr[i][j] >= mod)
                    arr[i][j] %= mod;
            }
        }
        return *this;
    }

    _Matrix operator * (const _Matrix & b)
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

    _Matrix & operator = (const _Matrix & b)
    {
        memcpy(arr, b.arr, sizeof(b.arr));
        return *this;
    }

} Matrix;

Matrix matrixQuickPow(Matrix matrix, int n)
{
    assert(matrix.row == matrix.column);

    Matrix ans(matrix.row, matrix.column);

    for (int i = 0; i < matrix.row; i++)
        ans.arr[i][i] = 1;

    while (n > 0)
    {
        if (n & 1)
            ans = ans * matrix;
        matrix = matrix * matrix;
        n >>= 1;
    }

    return ans;
}

long long int getFibo(int n)
{
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;

    Matrix base(2, 1);
    base.arr[0][0] = 1;
    base.arr[1][0] = 0;

    Matrix trans(2, 2);
    trans.arr[0][0] = 1;
    trans.arr[0][1] = 1;
    trans.arr[1][0] = 1;
    trans.arr[1][1] = 0;

    Matrix res = matrixQuickPow(trans, n - 1) * base;
    return res.arr[0][0] % mod;
}

bool checkQuadRes(int n)
{
    return quickPowMod(n, (mod - 1) >> 1) == 1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int m;
    cin >> m;

    for (int i = 2; i * i <= m; i++)
    {
        if (m % i == 0)
        {
            m /= i;
            int exp = 1;
            while (m % i == 0)
            {
                exp++;
                m /= i;
            }
            facArr.push_back(make_pair(i, exp));
        }
    }
    if (m != 1)
        facArr.push_back(make_pair(m, 1));


    long long int ans = 1;
    for (auto it = facArr.begin(); it != facArr.end(); ++it)
    {
        int cntPrime = it -> first, cntExp = it -> second;
        mod = cntPrime;
        int primeLoop = INT_MAX;
        if (it -> first == 2)
            primeLoop = 3;
        else if (it -> first == 3)
            primeLoop = 8;
        else if (it -> first == 5)
            primeLoop = 20;
        else
        {
            int cnt;
            if (checkQuadRes(5))
                cnt = cntPrime - 1;
            else
                cnt = (cntPrime + 1) << 1;
            
            facArr2.clear();
            for (int i = 2; i * i <= cnt; i++)
            {
                if (cnt % i == 0)
                {
                    facArr2.push_back(i);
                    facArr2.push_back(cnt / i);
                }
            }
            facArr2.push_back(cnt);

            for (auto it2 = facArr2.begin(); it2 != facArr2.end(); ++it2)
            {
                int cntFibo = getFibo(*it2);
                int cntFiboNxt = getFibo(*it2 + 1);

                if (cntFibo == 0 && cntFiboNxt == 1)
                {
                    primeLoop = min(primeLoop, *it2);
                    break;
                }
            }
        }

        assert(primeLoop != INT_MAX);

        long long int cntLoop = primeLoop * quickPow(cntPrime, cntExp - 1);
        ans = ans / __gcd(ans, cntLoop) * cntLoop;
    }

    cout << ans << endl;

    return 0;
}
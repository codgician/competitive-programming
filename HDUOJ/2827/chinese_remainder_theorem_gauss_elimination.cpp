#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <functional>
#include <iterator>
#define SIZE 101
#define MAX_PRIME 10001
using namespace std;

long long int primeArr[MAX_PRIME], primePt;
long long int factorArr[MAX_PRIME];

long long int mod[SIZE], cst[SIZE];
int equNum;

long long int origArr[SIZE][SIZE], cntArr[SIZE][SIZE];
int n;

void initPrime()
{
    memset(factorArr, 0, sizeof(factorArr));
    primePt = 0;
    for (int i = 2; i < MAX_PRIME; i++)
    {
        if (factorArr[i] == 0)
        {
            factorArr[i] = i;
            primeArr[primePt++] = i;
        }

        for (int j = 0; j < primePt; j++)
        {
            if (primeArr[j] > factorArr[i] || primeArr[j] > (MAX_PRIME - 1) / i)
                break;
            factorArr[i * primeArr[j]] = primeArr[j];
        }
    }
}

long long int extEuclidean(long long int a, long long int b, long long int &x, long long int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    long long int gcd = extEuclidean(b, a % b, x, y);
    long long int tmp = x;
    x = y;
    y = tmp - y * (a / b);

    return gcd;
}

long long int crt()
{
    long long int modProd = mod[0], prevAns = cst[0];

    for (int i = 1; i < equNum; i++)
    {
        long long int x, y;
        long long int a = modProd, b = mod[i], c = cst[i] - prevAns;
        long long int gcd = extEuclidean(a, b, x, y);

        if (c % gcd != 0)
            return -1;

        long long int cntAns = c / gcd * x;
        if (cntAns < 0)
            cntAns = (mod[i] / gcd) - (-cntAns) % (mod[i] / gcd);
        else
            cntAns %= mod[i] / gcd;

        prevAns += modProd * cntAns;
        modProd = modProd / gcd * mod[i];
    }

    return prevAns % modProd;
}

long long int quickPow(long long int a, long long int n, long long int mod)
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
    return ans % mod;
}

long long int gauss(long long int mod)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cntArr[i][j] = origArr[i][j];
        }
    }

    long long int ans = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int x = i, y = j;
            while (cntArr[y][i])
            {
                // long long int multi = cntArr[x][i] / cntArr[y][i];
                if (cntArr[x][i] < cntArr[y][i])
                {
                    swap(x, y);
                    continue;
                }
                long long int rev = quickPow(cntArr[y][i], mod - 2, mod);
                long long int multi = (cntArr[x][i] % mod) * rev % mod;
                for (int k = i; k < n; k++)
                {
                    cntArr[x][k] = (cntArr[x][k] - cntArr[y][k] * multi % mod) % mod;
                }
                swap(x, y);
            }
            if (x != i)
            {
                for (int k = 0; k < n; k++)
                    swap(cntArr[i][k], cntArr[j][k]);
                ans = -ans;
            }
        }

        ans = ans * cntArr[i][i] % mod;
    }
    return (ans + mod) % mod;
}

int main()
{
    ios::sync_with_stdio(false);
    initPrime();
    long long int m;
    while (cin >> n >> m)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> origArr[i][j];
            }
        }

        equNum = 0;
        for (int i = 0; i < primePt && m > 1; i++)
        {
            if (m % primeArr[i] == 0)
            {
                mod[equNum] = primeArr[i];
                cst[equNum] = gauss(primeArr[i]);
                m /= primeArr[i];
                equNum++;
            }
        }

        long long int ans = crt();
        cout << ans << endl;
    }
    return 0;
}
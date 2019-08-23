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

#define SIZE 100010

const int mod = 258280327;

int arr[SIZE];

int primeArr[SIZE], facArr[SIZE], mu[SIZE], primePt;
long long int factorialArr[SIZE], invFactorialArr[SIZE];
long long int twoPow[SIZE];

long long int F[2][SIZE], f[2][SIZE], ansArr[2];
int mulNum[SIZE];
int num;

long long int fastPow(long long int a, long long int n)
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

void initMu()
{
    memset(facArr, 0, sizeof(facArr));
    primePt = 0;
    mu[1] = 1;
    for (int i = 2; i < SIZE; i++)
    {
        if (facArr[i] == 0)
        {
            facArr[i] = i;
            mu[i] = -1;
            primeArr[primePt++] = i;
        }

        for (int j = 0; j < primePt; j++)
        {
            if (primeArr[j] > facArr[i] || primeArr[j] > (SIZE - 1) / i)
                break;
            facArr[i * primeArr[j]] = primeArr[j];

            if (facArr[i] == primeArr[j])
                mu[i * primeArr[j]] = 0;
            else
                mu[i * primeArr[j]] = -mu[i];
        }
    }
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

void initTwoPow()
{
    twoPow[0] = 1;
    for (int i = 1; i < SIZE; i++)
        twoPow[i] = (twoPow[i - 1] << 1) % mod;
}

long long int getPermu(int n, int m)
{
    if (m > n)
        return 0;
    return factorialArr[n] * invFactorialArr[n - m] % mod;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    initMu();
    initFactorial();
    initInvFactorial();
    initTwoPow();

    while (cin >> num)
    {
        int maxNum = -1;
        memset(mulNum, 0, sizeof(mulNum));
        memset(ansArr, 0, sizeof(ansArr));
        for (int i = 0; i < num; i++)
        {
            cin >> arr[i];
            maxNum = max(maxNum, arr[i]);
            mulNum[arr[i]]++;
        }
        
        for (int i = 1; i <= maxNum; i++)
        {
            for (int j = 2; i * j <= maxNum; j++)
            {
                mulNum[i] += mulNum[i * j];
            }
        }

        for (int i = 1; i <= maxNum; i++)
        {
            F[0][i] = 0;
            for (int j = 1; j <= mulNum[i]; j++)
            {
                F[0][i] += getPermu(mulNum[i], j) * factorialArr[num + 1 - j] % mod;
                F[0][i] %= mod;
            }
            F[1][i] = mulNum[i] * twoPow[mulNum[i] - 1] % mod;
            F[1][i] %= mod;
        }
        
        for (int i = 1; i <= maxNum; i++)
        {
            for (int t = 0; t < 2; t++)
            {
                f[t][i] = 0;
                for (int k = 1; k * i <= maxNum; k++)
                {
                    f[t][i] += mu[k] * F[t][k * i] % mod;
                    f[t][i] %= mod;
                }
            }
        }

        for (int i = 1; i <= maxNum; i++)
        {
            for (int t = 0; t < 2; t++)
            {
                ansArr[t] += i * f[t][i] % mod;
                ansArr[t] %= mod;
            }
        }

        if (ansArr[1] > ansArr[0])
            cout << "Mr. Hdu " << ansArr[1] << endl;
        else if (ansArr[0] > ansArr[1])
            cout << "Mr. Zstu " << ansArr[0] << endl;
        else
            cout << "Equal " << ansArr[1] << endl; 
    }

    return 0;
}
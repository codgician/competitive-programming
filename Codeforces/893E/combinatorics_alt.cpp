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

#define SIZE 1000100
#define DIV_SIZE 30

const long long int mod = 1e9 + 7;

int primeArr[SIZE], factorArr[SIZE], primePt;
long long int factorialArr[SIZE], invFactorialArr[SIZE];
int twoPowArr[SIZE];
int indexArr[DIV_SIZE], divisorNum;

inline long long int fastPow(long long int a, long long int n)
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

inline void initFactorial()
{
    factorialArr[0] = 1;
    for (int i = 1; i < SIZE; i++)
        factorialArr[i] = factorialArr[i - 1] * i % mod;
}

inline void initPrime()
{
    memset(factorialArr, 0, sizeof(factorialArr));
    primePt = 0;
    for (int i = 2; i < SIZE; i++)
    {
        if (factorArr[i] == 0)
        {
            factorArr[i] = i;
            primeArr[primePt++] = i;
        }

        for (int j = 0; j < primePt; j++)
        {
            if (primeArr[j] > factorArr[i] || primeArr[j] > (SIZE - 1) / i)
                break;
            factorArr[i * primeArr[j]] = primeArr[j];
        }
    }
}

inline void initInvFactorial()
{
    invFactorialArr[SIZE - 1] = fastPow(factorialArr[SIZE - 1], mod - 2);
    for (int i = SIZE - 2; i >= 0; i--)
        invFactorialArr[i] = invFactorialArr[i + 1] * (i + 1) % mod;
}

inline void initTwoPow()
{
    twoPowArr[0] = 1;
    for (int i = 1; i < SIZE; i++)
        twoPowArr[i] = (twoPowArr[i - 1] << 1) % mod;
}

inline long long int getComb(long long int n, long long int m)
{
    if (m > n)
        return 0;
    return factorialArr[n] * invFactorialArr[m] % mod * invFactorialArr[n - m] % mod;
}

int main()
{
    initPrime();
    initFactorial();
    initInvFactorial();
    initTwoPow();

    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        int prod, num;
        scanf("%d%d", &prod, &num);

        int divisorNum = 0;
        for (int i = 0; primeArr[i] <= prod / primeArr[i]; i++)
        {
            if (prod % primeArr[i] == 0)
            {
                indexArr[divisorNum] = 0;
                while (prod % primeArr[i] == 0)
                {
                    prod /= primeArr[i];
                    indexArr[divisorNum]++;
                }
                divisorNum++;
            }
        }
        if (prod != 1)
            indexArr[divisorNum++] = 1;

        long long int ans = twoPowArr[num - 1];
        for (int i = 0; i < divisorNum; i++)
        {
            ans *= getComb(num + indexArr[i] - 1, indexArr[i]);
            ans %= mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
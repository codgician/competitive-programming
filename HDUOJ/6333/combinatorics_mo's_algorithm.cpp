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

const long long int mod = 1e9 + 7;

#define SIZE 100001

typedef struct _Query
{
    int index;
    int n, m;
    int ans;
} Query;

Query arr[SIZE];
int posArr[SIZE];

long long int factorialArr[SIZE], invFactorialArr[SIZE];

inline long long int fastPow(long long int a, long long int n)
{
    long long int ans = 1;
    while (n > 0)
    {
        if (n & 1)
        {
            ans *= a;
            if (ans >= mod)
                ans %= mod;
        }
        a *= a;
        if (a >= mod)
            a %= mod;
        n >>= 1;
    }
    return ans;
}

inline void initFactorial()
{
    factorialArr[0] = 1;
    for (int i = 1; i < SIZE; i++)
    {
        factorialArr[i] = factorialArr[i - 1] * i;
        if (factorialArr[i] >= mod)
            factorialArr[i] %= mod;
    }
}

inline void initInvFactorial()
{
    invFactorialArr[SIZE - 1] = fastPow(factorialArr[SIZE - 1], mod - 2);
    for (int i = SIZE - 2; i >= 0; i--)
    {
        invFactorialArr[i] = invFactorialArr[i + 1] * (i + 1);
        if (invFactorialArr[i] >= mod)
            invFactorialArr[i] %= mod;
    }
}

inline long long int getComb(long long int n, long long int m)
{
    if (m > n)
        return 0;
    long long int ans = factorialArr[n] * invFactorialArr[m];
    if (ans >= mod)
        ans %= mod;
    ans *= invFactorialArr[n - m];
    if (ans >= mod)
        ans %= mod;
    return ans;
}

int main()
{
    initFactorial();
    initInvFactorial();
    int caseNum;
    scanf("%d", &caseNum);
    for (int i = 0; i < caseNum; i++)
    {
        scanf("%d%d", &arr[i].n, &arr[i].m);
        arr[i].index = i;
    }

    int blockSize = sqrt(SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        posArr[i] = i / blockSize;
    }

    sort(arr + 0, arr + caseNum, [](Query & fst, Query & snd) {
        if (posArr[fst.n] == posArr[snd.n])
            return fst.m < snd.m;
        return fst.n < snd.n;
    });

    int cntN = 1, cntM = 0;
    long long int ans = 1;
    for (int i = 0; i < caseNum; i++)
    {
        while (cntN < arr[i].n)
        {
            ans = ((ans << 1) - getComb(cntN, cntM) + mod) % mod;
            cntN++;
        }
        while (cntN > arr[i].n)
        {
            ans = (ans + getComb(cntN - 1, cntM)) % mod * invFactorialArr[2] % mod;
            cntN--;
        }
        while (cntM < arr[i].m)
        {
            ans = (ans + getComb(cntN, cntM + 1)) % mod;
            cntM++;
        }
        while (cntM > arr[i].m)
        {
            ans = (ans - getComb(cntN, cntM) + mod) % mod;
            cntM--;
        }
        arr[i].ans = ans;
    }

    sort(arr + 0, arr + caseNum, [](Query & fst, Query & snd) {
        return fst.index < snd.index;
    });

    for (int i = 0; i < caseNum; i++)
    {
        printf("%d\n", arr[i].ans);
    }

    return 0;
}
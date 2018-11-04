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

#define SIZE 22

const long long int mod = 998244353;

long long int arr[SIZE];
long long int factorialArr[SIZE], invFactorialArr[SIZE];

long long int quickPow(long long int a, long long int n)
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

void initFactorial()
{
    factorialArr[0] = 1;
    for (int i = 1; i < SIZE; i++)
        factorialArr[i] = factorialArr[i - 1] * i % mod;
}

void initInvFactorial()
{
    invFactorialArr[SIZE - 1] = quickPow(factorialArr[SIZE - 1], mod - 2);
    for (int i = SIZE - 2; i >= 0; i--)
        invFactorialArr[i] = invFactorialArr[i + 1] * (i + 1) % mod;
}

long long int getComb(int n, int m)
{
    if (m > n)
        return 0;
    return factorialArr[n] * invFactorialArr[m] % mod * invFactorialArr[n - m] % mod;
}

void init()
{
    arr[0] = 1;
    arr[1] = 1;

    for (int i = 2; i < SIZE; i++)
    {
        arr[i] = 0;
        for (int j = 1; j <= i; j++)
        {
            arr[i] += getComb(i, j) * arr[i - j] % mod;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    initFactorial();
    initInvFactorial();
    init();

    int taskNum, sryNum;
    cin >> taskNum >> sryNum;

    long long int ans = 0;
    for (int i = 0; i < sryNum; i++)
    {
        string str;
        long long int val; 
        cin >> str >> val;

        int oneNum = 0;
        for (auto it = str.begin(); it != str.end(); ++it)
        {
            if (*it == '1')
                oneNum++;
        }

        ans += arr[oneNum] * arr[taskNum - oneNum] % mod * val % mod;
        ans %= mod;
    }

    cout << ans << endl;

    return 0;
}
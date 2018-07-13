#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
#define SIZE 100010
using namespace std;

long long int factorialArr[SIZE];
long long int treeNum, saveNum, mod;

long long int quickPow(long long int a, long long int n)
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

long long int getComb(long long int n, long long int m)
{
    if (m > n)
        return 0;
    return factorialArr[n] * quickPow(factorialArr[m], mod - 2) % mod * quickPow(factorialArr[n - m], mod - 2) % mod;
}

long long int lucas(long long int n, long long int m)
{
    if (n == 0)
        return 1;
    return getComb(n % mod, m % mod) * lucas(n / mod, m / mod) % mod;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        cin >> treeNum >> saveNum >> mod;

        factorialArr[0] = 1;
        for (int i = 1; i <= mod; i++)
        {
            factorialArr[i] = factorialArr[i - 1] * i % mod;
        }

        cout << lucas(saveNum + treeNum, saveNum) << endl;
    }
    return 0;
}
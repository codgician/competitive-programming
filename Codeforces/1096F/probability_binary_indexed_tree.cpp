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

#define SIZE 200010

const int mod = 998244353;

int bitArr[SIZE];
int arr[SIZE], unkArr[SIZE], len;

long long int quickPow(long long int a, int n)
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

int getLowbit(int n)
{
    return n & (-n);
}

void add(int pos, int val)
{
    for (int i = pos; i <= len; i += getLowbit(i))
    {
        bitArr[i] += val;
    }
}

int prefixSum(int pos)
{
    int ans = 0;
    for (int i = pos; i > 0; i -= getLowbit(i))
    {
        ans += bitArr[i];
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(bitArr, 0, sizeof(bitArr));
    memset(unkArr, 0, sizeof(unkArr));

    int unkNum = 0;
    cin >> len;
    for (int i = 0; i < len; i++)
    {
        cin >> arr[i];
        if (arr[i] == -1)
        {
            unkNum++;
            unkArr[i] = 1;
        }
    }
    for (int i = 1; i < len; i++)
        unkArr[i] += unkArr[i - 1];

    long long int ans = 1ll * unkNum * (unkNum - 1) % mod * quickPow(4, mod - 2) % mod;
    for (int i = len - 1; i >= 0; i--)
    {
        if (arr[i] == -1)
            continue;
        ans += prefixSum(arr[i] - 1);
        ans %= mod;
        add(arr[i], 1);
    }

    long long int inv = quickPow(unkNum, mod - 2);
    for (int i = 0; i < len; i++)
    {
        if (arr[i] == -1)
            continue;
        ans += 1ll * unkArr[i] * (unkNum - arr[i] + prefixSum(arr[i])) % mod * inv % mod;
        ans += 1ll * (unkNum - unkArr[i]) * (arr[i] - prefixSum(arr[i])) % mod * inv % mod;
        ans %= mod;
    }

    cout << ans << endl;
    return 0;
}
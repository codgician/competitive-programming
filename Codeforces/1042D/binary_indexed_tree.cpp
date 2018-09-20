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

#define SIZE 200010

long long int prefixSum[SIZE], bitArr[SIZE];
map<long long int, int> mp;
int len;

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

long long int getPrefixSum(int pos)
{
    long long int ans = 0;
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

    long long int lim;

    mp.clear();
    mp[0] = -1;
    memset(bitArr, 0, sizeof(bitArr));
    cin >> len >> lim;
    prefixSum[0] = 0;
    for (int i = 1; i <= len; i++)
    {
        long long int cnt;
        cin >> cnt;
        prefixSum[i] = prefixSum[i - 1] + cnt;
        mp[prefixSum[i]] = -1;
    }

    int cntPt = 1;
    for (auto it = mp.begin(); it != mp.end(); ++it)
    {
        it -> second = cntPt++;
    }

    add(mp[0], 1);
    long long int ans = 0, minVal = 0;
    for (int i = 1; i <= len; i++)
    {
        long long int cmp = prefixSum[i] - lim;
        if (minVal > cmp)
        {
            ans += i;
        }
        else
        {
            auto it = mp.upper_bound(cmp);

            if (it != mp.end())
            {
                ans += i - getPrefixSum(it -> second - 1);
            }
        }

        add(mp[prefixSum[i]], 1);
        minVal = min(minVal, prefixSum[i]);
    }

    cout << ans << endl;
    return 0;
}
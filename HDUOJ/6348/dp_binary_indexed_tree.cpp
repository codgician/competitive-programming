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

#define SIZE 100010

const int mod = 1e9 + 7;

long long int arr[SIZE], ans[SIZE];
long long int bitArr[SIZE];
long long int dp[2][SIZE];

int len;

int getLowbit(int n)
{
    return n & -n;
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
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        cin >> len;
        for (int i = 1; i <= len; i++)
        {
            cin >> arr[i];
            dp[1][i] = 1;
        }

        memset(ans, 0, sizeof(ans));
        ans[1] = len;

        for (int i = 2; i <= len; i++)
        {
            if (ans[i - 1] == 0)
                break;
            memset(bitArr, 0, sizeof(bitArr));
            for (int j = 1; j <= len; j++)
            {
                long long int cnt = getPrefixSum(arr[j] - 1) % mod;
                ans[i] = (ans[i] + cnt) % mod;

                dp[i & 1][j] = cnt;
                add(arr[j], dp[!(i & 1)][j]);
            }
        }

        cout << "Case #" << t << ":";
        for (int i = 1; i <= len; i++)
        {
            cout << " " << ans[i];
        }
        cout << endl;
    }
    return 0;
}
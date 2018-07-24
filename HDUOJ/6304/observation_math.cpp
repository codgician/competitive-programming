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

long long int getLowbitSum(long long int x)
{
    long long int ans = 0;
    for (int i = 0; i <= 60 && (1ll << i) <= x; i++)
        ans += x >> i;
    return ans;
}

long long int getPrefixSum(long long int x)
{
    long long int ans = 0;
    for (int i = 0; i <= 60 && (1ll << i) <= x; i++)
    {
        long long int num = (((x >> i) + 1) >> 1) % mod;
        ans += (i + 1) * num % mod * num % mod * ((1ll << i) % mod) % mod;
        ans %= mod;
    }
    return ans;
}

bool check(long long int x, long long int chkSum)
{
    long long int cntSum = getLowbitSum(x);
    return cntSum <= chkSum;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        long long int pos;
        cin >> pos;
        pos--;

        long long int leftPt = max(1ll, (pos >> 1) - 1), rightPt = min(pos, (pos >> 1) + 50);
        long long int lowbitPos = -1;
        while (leftPt <= rightPt)
        {
            long long int midPt = (leftPt + rightPt) >> 1;
            if (check(midPt, pos))
            {
                leftPt = midPt + 1;
                lowbitPos = midPt;
            }
            else
            {
                rightPt = midPt - 1;
            }
        }

        long long int ans = getPrefixSum(lowbitPos) % mod;
        long long int lowbitSum = getLowbitSum(lowbitPos);
        if (pos > lowbitSum)
        {
            ans += (pos - lowbitSum) * ((lowbitPos + 1) % mod) % mod;
            ans %= mod;
        }
        ans = (ans + 1) % mod;

        cout << ans << endl;
    }

    return 0;
}

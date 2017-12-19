#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

bool isConsisitOfNine(long long int n)
{
    while (n > 0)
    {
        if (n % 10 != 9)
            return false;
        n /= 10;
    }
    return true;
}

long long int getDigitCount(long long int n)
{
    long long int ans = 0;
    while (n > 0)
    {
        ans++;
        n /= 10;
    }
    return ans;
}

long long int constructNine(long long int nineCount)
{
    long long int ans = 0, t = 1;
    while (nineCount--)
    {
        ans += ((t << 3) + t);
        t = (t << 3) + (t << 1);
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    long long int n;
    cin >> n;
    long long int maxSum = (n << 1) - 1, ans = 0;
    if (isConsisitOfNine(maxSum))
    {
        ans = 1;
    }
    else
    {
        long long int maxNineCount = getDigitCount(maxSum) - 1;
        long long int cnt = constructNine(maxNineCount);
        long long int adder = cnt + 1;
        while (cnt <= maxSum)
        {
            ans += (cnt - 1) / 2;
            if (cnt > n + 1)
            {
                ans -= (cnt - n - 1);
            }
            cnt += adder;
        }
    }
    cout << ans << endl;
    return 0;
}

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int getBitNum(int n)
{
    int ans = 0;
    while (n > 0)
    {
        ans++;
        n /= 10;
    }
    return ans;
}

int getBitSum(int n)
{
    int ans = 0;
    while (n > 0)
    {
        ans += n % 10;
        n /= 10;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int left, right, s;
    while (cin >> left >> right >> s)
    {
        if (s % 9 == 0)
            s--;
        s = (s / 9) * 9;
        int tmp = s + 9 * getBitNum(s);
        while (tmp - getBitSum(tmp) > s)
        {
            tmp -= 10;
        }
        tmp += (9 - (tmp % 10));

        right = min(right, tmp);
        if (right < left)
            cout << 0 << endl;
        else
            cout << right - left + 1 << endl;
    }
    return 0;
}

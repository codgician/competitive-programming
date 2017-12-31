#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int c;

int calc(int a, int b)
{
    return b * b + a * b + a * a;
}

int work(int k)
{
    int st = c / k;
    for (int a = 1; ; a++)
    {
        if (calc(a, a + k) == st)
            return a;
        if (calc(a, a + k) > st)
            return -1;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int a, b;
    bool hasFound;
    while (cin >> c)
    {
        hasFound = false;
        for (int k = pow(c, 1.0/3); k >= 1; k--)
        {
            if (c % k == 0)
            {
                int ans = work(k);
                if (ans > -1)
                {
                    cout << ans << " " << ans + k << endl;
                    hasFound = true;
                    break;
                }
            }
        }

        if (!hasFound)
            cout << "-1" << endl;
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    long long int n;
    while (cin >> n)
    {
        int ans = 0;
        for (long long int i = 2; i <= sqrt(n) * 2; i++)
        {
            if ((2 * n) % i == 0)
            {
                int t = (2 * n) / i - i + 1;
                if ((t & 1) == 0 && t >= 2)
                    ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

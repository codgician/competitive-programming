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
    unsigned long long int n;
    while (cin >> n)
    {
        if (n == 0)
            break;

        unsigned long long int ans = sqrt(n) - 1;
        unsigned long long int tmp = (ans + 1) * (ans + 1);
        while (tmp <= n)
        {
            if (ans > 1e9)
                break;
            ans++;
            tmp = (ans + 1) * (ans + 1);
        }
        cout << ans << endl;
    }
    return 0;
}

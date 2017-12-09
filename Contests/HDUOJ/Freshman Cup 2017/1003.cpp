#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    long long int n, m;
    while (cin >> n >> m)
    {
        long long int t1, t2, t3 ,t4;
        cin >> t1 >> t2 >> t3 >> t4;

        // Walk
        long long int walk = t4 * (n - 1);

        // Elevator
        long long int eve = 0;
        if (m >= n)
        {
            eve = t1 * (m - 1) + 2 * t2 + t3;
        }
        else
        {
            long long int opt1 = t1 * (n - 1 + n - m) + 2 * t2 + t3;
            long long int opt2 = t4 * (n - m) + t1 * (n - 1) + 2 * t2 + t3;
            eve = min(opt1, opt2);
        }

        long long int ans = min(walk, eve);

        cout << ans << endl;
    }
    return 0;
}

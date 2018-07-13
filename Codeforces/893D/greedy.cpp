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

int main()
{
    ios::sync_with_stdio(false);
    int num, lim;
    cin >> num >> lim;

    int ans = 0;
    int lowerBound = 0, upperBound = 0;
    for (int i = 0; i < num; i++)
    {
        int cnt;
        cin >> cnt;

        if (cnt != 0)
        {
            lowerBound += cnt;
            upperBound = min(upperBound + cnt, lim);

            if (lowerBound > lim)
            {
                ans = -1;
                break;
            }
        }
        else
        {
            lowerBound = max(0, lowerBound);
            if (upperBound < 0)
            {
                ans++;
                lowerBound = 0;
                upperBound = lim;
            }
        }
    }

    cout << ans << endl;
    return 0;
}
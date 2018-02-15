#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int riverNum, dis, casePt = 1;
    while (cin >> riverNum >> dis)
    {
        if (riverNum == 0 && dis == 0)
            break;

        double ans = 0;
        int riverLenSum = 0;
        for (int i = 0; i < riverNum; i++)
        {
            int dis, len, velocity;
            cin >> dis >> len >> velocity;
            ans += (double)(len << 1) / velocity;
            riverLenSum +=  len;
        }
        ans += (dis - riverLenSum);

        cout << "Case " << casePt++ << ": " << fixed << setprecision(3) << ans << endl << endl;
    }
    return 0;
}

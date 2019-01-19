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
#include <cassert>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int cnt;
        cin >> cnt;

        // 180 * k == cnt * n, k <= n - 2
        int gcd = __gcd(cnt, 180);
        cnt /= gcd;
        int ans = 180 / gcd;
        
        if (cnt + 1 == ans)
            ans <<= 1;
        cout << ans << endl;
    }

    return 0;
}
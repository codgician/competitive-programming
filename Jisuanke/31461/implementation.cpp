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
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int len;
        char seed;
        cin >> len >> seed;

        string str;
        cin >> str;

        int ans = len << 1;
        int pt;
        for (pt = 0; pt < len; pt++)
        {
            if (str[pt] == seed)
            {
                ans -= 2;
            }
            else
            {
                break;
            }
        }

        if (pt >= len)
        {
            ans = 1;
        }
        else if (abs(str[pt] - seed) < 10)
        {
            ans--;
        }

        cout << ans << endl;
    }
    return 0;
}
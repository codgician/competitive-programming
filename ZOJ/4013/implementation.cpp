#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        map<int, bool> mp;
        int len;
        cin >> len;
        for (int i = 0; i < len; i++)
        {
            int cnt;
            cin >> cnt;
            mp[cnt] = true;
        }

        int ans = -1;
        for (int i = 0; i < len; i++)
        {
            int cnt;
            cin >> cnt;
            if (ans == -1 && mp.count(cnt))
            {
                ans = cnt;
            }
        }

        cout << ans << endl;
    }
    return 0;
}

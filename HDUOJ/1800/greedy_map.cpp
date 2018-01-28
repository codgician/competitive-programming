#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
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
    int soldierNum;
    while (cin >> soldierNum)
    {
        map<string, int> mp;
        int ans = 1;

        for (int i = 0; i < soldierNum; i++)
        {
            string tmp;
            cin >> tmp;
            string::iterator its = tmp.begin();
            while (*its == '0')
            {
                tmp.erase(its);
            }
            mp[tmp]++;
            ans = max(ans, mp[tmp]);
        }
        cout << ans << endl;
    }
    return 0;
}

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

map<string, bool> mp;

int main()
{
    ios::sync_with_stdio(false);
    string str = "";
    long long int ans = 0;
    char ch;
    while (ch = getchar())
    {
        if (ch == '#')
            break;
        else if (ch == ' ' || ch == '\n')
        {
            if (!str.empty() && !mp[str])
            {
                mp[str] = true;
                ans++;
            }
            str = "";
            if (ch == '\n')
            {
                cout << ans << endl;
                mp.clear();
                ans = 0;
            }
        }
        else
        {
            str += ch;
        }
    }
    return 0;
}

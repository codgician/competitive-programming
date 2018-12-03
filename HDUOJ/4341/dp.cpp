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

#define GOLD_SIZE 205
#define TIME_SIZE 40005

map<pair<int, int>, vector<pair<int, pair<int, int> > > > mp;

int dp[TIME_SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int casePt = 0;
    int goldNum, timeLim;
    while (cin >> goldNum >> timeLim)
    {
        memset(dp, 0, sizeof(dp));
        mp.clear();
        for (int i = 0; i < goldNum; i++)
        {
            int x, y, cost, val;
            cin >> x >> y >> cost >> val;

            int sgn = 1;
            if (x < 0)
            {
                sgn = -1;
                x = -x;
            }

            int gcd = __gcd(x, y);
            x /= gcd;
            y /= gcd;
            mp[make_pair(sgn * x, y)].push_back(make_pair(gcd, make_pair(cost, val)));
        }

        for (auto it = mp.begin(); it != mp.end(); ++it)
        {
            sort(it -> second.begin(), it -> second.end());
            for (int i = 1; i < (int)it -> second.size(); i++)
            {
                it -> second[i].second.first += it -> second[i - 1].second.first;
                it -> second[i].second.second += it -> second[i - 1].second.second;
            }

            for (int j = timeLim; j >= it -> second.begin() -> second.first; j--)
            {
                for (auto k : it -> second)
                {
                    if (j - k.second.first < 0)
                        break;
                    dp[j] = max(dp[j], dp[j - k.second.first] + k.second.second);
                }
            }
        }

        cout << "Case " << ++casePt << ": " << dp[timeLim] << endl;
    }

    return 0;
}
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

#define SIZE 100010

set<pair<int, int> > st[SIZE];
map<pair<int, int>, int> mp;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        mp.clear();
        int frameNum;
        cin >> frameNum;
        for (int i = 0; i < frameNum; i++)
        {
            st[i].clear();
            int cntNum;
            cin >> cntNum;
            for (int j = 0; j < cntNum; j++)
            {
                int fst, snd;
                cin >> fst >> snd;
                st[i].insert(make_pair(fst, snd));
            }
        }

        int ans = 0;
        for (int i = 0; i < frameNum; i++)
        {
            for (auto it = st[i].begin(); it != st[i].end(); ++it)
            {
                if (i == 0)
                {
                    mp[*it] = 1;
                }
                else if (st[i - 1].find(*it) == st[i - 1].end())
                {
                    ans = max(ans, mp[*it]);
                    mp[*it] = 1;
                }
                else
                {
                    mp[*it]++;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
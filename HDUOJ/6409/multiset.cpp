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

int father[SIZE], arr[SIZE];
multiset<int> mst[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int num;
        cin >> num;

        for (int i = 0; i < num; i++)
        {
            mst[i] = multiset<int>();
        }

        for (int i = 1; i < num; i++)
        {
            cin >> father[i];
            father[i]--;
        }

        for (int i = 0; i < num; i++)
        {
            cin >> arr[i];
            if (i > 0)
                mst[father[i]].insert(arr[i]);
        }

        long long int minAns = 0, maxAns = 0;
        if (arr[0] < 0)
            minAns += arr[0];
        else
            maxAns += arr[0];

        for (int i = 0; i < num; i++)
        {
            if (mst[i].size() == 0)
                continue;
            else if (mst[i].size() == 1)
            {
                auto it = mst[i].begin();
                if (*it < 0)
                    minAns += *it;
                else
                    maxAns += *it;
                mst[i].erase(it);
                continue;
            }

            auto it = prev(mst[i].end());
            if (*it > 0)
            {
                maxAns += *it;
                mst[i].erase(it);
            }

            it = mst[i].begin();
            if (*it < 0)
            {
                minAns += *it;
                mst[i].erase(it);
            }
        }

        int maxVal = INT_MIN, minVal = INT_MAX;
        for (int i = 0; i < num; i++)
        {
            if (mst[i].size() == 0)
                continue;

            auto it = prev(mst[i].end());
            maxVal = max(maxVal, *it);
            it = mst[i].begin();
            minVal = min(minVal, *it);
        }

        if (maxVal > 0)
            maxAns += maxVal;
        if (minVal < 0)
            minAns += minVal;

        cout << maxAns << " " << minAns << endl;
    }
    return 0;
}
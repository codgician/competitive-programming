#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
#define SIZE 110
using namespace std;

typedef struct _Node
{
    long long int size, value;
} Node;

Node arr[SIZE];

map<long long int, long long int> dp;

int main()
{
    ios::sync_with_stdio(false);
    int num;
    long long int lim;
    while (cin >> num >> lim)
    {
        long long int ans = 0;
        dp.clear();
        dp[0] = 0;
        for (int i = 0; i < num; i++)
        {
            cin >> arr[i].size >> arr[i].value;
            if (arr[i].size > lim)
            {
                num--;
                i--;
            }
        }

        for (int i = 0; i < num; i++)
        {
            // From big to small
            for (map<long long int, long long int>::reverse_iterator rit = dp.rbegin(); rit != dp.rend(); ++rit)
            {
                long long int cntSize = rit -> first, cntValue = rit -> second;
                if (cntSize + arr[i].size <= lim)
                {
                    dp[cntSize + arr[i].size] = max(dp[cntSize + arr[i].size], cntValue + arr[i].value);
                }
            }

            // From small to big
            // Erase useless states to save memory
            long long int prevValue = 0;
            map<long long int, long long int>::iterator it = dp.begin();
            ++it;   // Skip dp[0]
            while (it != dp.end())
            {
                long long int cntValue = it -> second;
                if (cntValue <= prevValue)
                {
                    it = dp.erase(it);
                }
                else
                {
                    prevValue = cntValue;
                    ans = max(ans, cntValue);
                    ++it;
                }
            }
        }

        cout << ans << endl;
    }
    return 0;
}
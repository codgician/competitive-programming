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
#define SIZE 501
using namespace std;

bool arr[SIZE][SIZE], hasTried[SIZE];
int boyMatch[SIZE];
int girlNum, boyNum;

bool canFind(int girlId)
{
    for (int i = 0; i < boyNum; i++)
    {
        if (arr[girlId][i] && !hasTried[i])
        {
            hasTried[i] = true;
            if (boyMatch[i] == -1 || canFind(boyMatch[i]))
            {
                boyMatch[i] = girlId;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    int possComb;
    while (cin >> possComb)
    {
        if (possComb == 0)
            break;
        memset(arr, false, sizeof(arr));
        memset(boyMatch, -1, sizeof(boyMatch));
        cin >> girlNum >> boyNum;
        for (int i = 0; i < possComb; i++)
        {
            int girlId, boyId;
            cin >> girlId >> boyId;
            arr[--girlId][--boyId] = true;
        }

        int ans = 0;
        for (int i = 0; i < girlNum; i++)
        {
            memset(hasTried, false, sizeof(hasTried));
            if (canFind(i))
                ans++;
        }

        cout << ans << endl;
    }
    return 0;
}


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
#define SIZE 101
using namespace std;

bool arr[SIZE][SIZE], hasTried[SIZE];
int bMatch[SIZE];
int aModeNum, bModeNum, jobNum;

bool canFind(int aModeId)
{
    for (int i = 0; i < bModeNum; i++)
    {
        if (arr[aModeId][i] && !hasTried[i])
        {
            hasTried[i] = true;
            if (bMatch[i] == -1 || canFind(bMatch[i]))
            {
                bMatch[i] = aModeId;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> aModeNum)
    {
        if (aModeNum == 0)
            break;
        memset(arr, false, sizeof(arr));
        memset(bMatch, -1, sizeof(bMatch));
        cin >> bModeNum >> jobNum;
        for (int i = 0; i < jobNum; i++)
        {
            int id, aMode, bMode;
            cin >> id >> aMode >> bMode;
            arr[aMode][bMode] = true;
        }

        int ans = 0;
        // Status 0 need no restart.
        for (int i = 1; i < aModeNum; i++)
        {
            memset(hasTried, false, sizeof(hasTried));
            if (canFind(i))
                ans++;
        }

        cout << ans << endl;
    }
    return 0;
}

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
#define SIZE 121
using namespace std;

bool arr[SIZE][SIZE], hasTried[SIZE];
int bMatch[SIZE];
int intNum, strNum;

bool canFind(int aId)
{
    for (int i = 0; i < intNum; i++)
    {
        if (arr[aId][i] && !hasTried[i])
        {
            hasTried[i] = true;
            if (bMatch[i] == -1 || canFind(bMatch[i]))
            {
                bMatch[i] = aId;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(arr, false, sizeof(arr));
        memset(bMatch, -1, sizeof(bMatch));
        cin >> intNum >> strNum;
        for (int i = 0; i < strNum; i++)
        {
            int a, b;
            cin >> a >> b;
            arr[--a][--b] = true;
        }

        int ans = 0;
        for (int i = 0; i < intNum; i++)
        {
            memset(hasTried, false, sizeof(hasTried));
            if (canFind(i))
                ans++;
        }

        cout << intNum - ans << endl;
    }
    return 0;
}

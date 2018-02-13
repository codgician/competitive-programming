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
#include <set>
#include <map>
#define SIZE 27
using namespace std;

bool arr[SIZE][SIZE];
int path[SIZE], dp[SIZE];
int nodeNum, maxNum, cntStartPt;

bool canAdd(int cntPt, int cntNum)
{
    for (int i = 0; i < cntNum; i++)
    {
        if (!arr[cntPt][path[i]])
        {
            return false;
        }
    }
    return true;
}

void dfs(int cntPt, int cntNum)
{
    maxNum = max(maxNum, cntNum);

    if (cntNum + nodeNum - cntPt - 1 <= maxNum)
        return;

    for (int i = cntPt + 1; i < nodeNum; i++)
    {
        if (dp[i] + cntNum <= maxNum)
            return;

        if (canAdd(i, cntNum))
        {
            path[cntNum] = i;
            dfs(i, cntNum + 1);
        }
    }

    return;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> nodeNum)
    {
        if (nodeNum == 0)
            break;

        memset(arr, false, sizeof(arr));
        maxNum = 1;
        for (int i = 0; i < nodeNum; i++)
        {
            char tmp;
            cin >> tmp >> tmp;
            cin >> noskipws >> tmp;
            while (tmp != '\n')
            {
                arr[i][tmp - 'A'] = true;
                cin >> noskipws >> tmp;
            }
        }

        dp[nodeNum - 1] = 1;
        for (int i = nodeNum - 2; i >= 0; i--)
        {
            path[0] = i;
            dfs(i, 1);
            dp[i] = maxNum;
        }
        cout << maxNum;

        if (maxNum <= 1)
            cout << " channel";
        else
            cout << " channels";
        cout << " needed." << endl;
    }
    return 0;
}

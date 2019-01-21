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

#define SIZE 45
#define EVENT_SIZE 100010

bool arr[SIZE][SIZE];
int path[SIZE], dp[SIZE], ans[SIZE];
int vertexNum, maxSize;

map<string, int> mp;
int cntArr[EVENT_SIZE], cntPt, mpPt;

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
    maxSize = max(maxSize, cntNum);
    if (cntNum == maxSize)
    {
        for (int i = 0; i < cntNum; i++)
        {
            ans[i] = path[i];
        }
    }

    if (cntNum + vertexNum - cntPt - 1 <= maxSize)
        return;

    for (int i = cntPt + 1; i < vertexNum; i++)
    {
        if (dp[i] + cntNum <= maxSize)
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
    cin.tie(0);
    cout.tie(0);
    mpPt = 0, cntPt = 0;

    int len;
    cin >> len >> vertexNum;
    for (int i = 0; i < vertexNum; i++)
    {
        arr[i][i] = true;
        for (int j = i + 1; j < vertexNum; j++)
        {
            arr[i][j] = true;
            arr[j][i] = true;
        }
    }

    for (int i = 0; i < len; i++)
    {
        int opr;
        cin >> opr;
        if (opr == 1)
        {
            for (int i = 0; i < cntPt; i++)
            {
                for (int j = i + 1; j < cntPt; j++)
                {
                    arr[cntArr[i]][cntArr[j]] = false;
                    arr[cntArr[j]][cntArr[i]] = false;
                }
            }
            cntPt = 0;
        }
        else if (opr == 2)
        {
            string name;
            cin >> name;
            if (mp.find(name) == mp.end())
                mp[name] = mpPt++;
            cntArr[cntPt++] = mp[name];
        }
    }

    for (int i = 0; i < cntPt; i++)
    {
        for (int j = i + 1; j < cntPt; j++)
        {
            arr[cntArr[i]][cntArr[j]] = false;
            arr[cntArr[j]][cntArr[i]] = false;
        }
    }

    maxSize = 1;
    dp[vertexNum - 1] = 1;
    for (int i = vertexNum - 2; i >= 0; i--)
    {
        path[0] = i;
        dfs(i, 1);
        dp[i] = maxSize;
    }
    cout << maxSize << endl;

    return 0;
}
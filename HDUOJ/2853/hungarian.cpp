#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SIZE 51
using namespace std;

int arr[SIZE][SIZE];
int compEx[SIZE], missEx[SIZE];
int missMatch[SIZE], missNeed[SIZE];
int cntCompMatch[SIZE];
bool compVisited[SIZE], missVisited[SIZE];

int compNum, missNum;

bool canFind(int compId)
{
    compVisited[compId] = true;
    for (int i = 0; i < missNum; i++)
    {
        if (missVisited[i])
            continue;

        int delta = compEx[compId] + missEx[i] - arr[compId][i];
        if (delta == 0)
        {
            missVisited[i] = true;
            if (missMatch[i] == -1 || canFind(missMatch[i]))
            {
                missMatch[i] = compId;
                return true;
            }
        }
        else
        {
            missNeed[i] = min(missNeed[i], delta);
        }
    }
    return false;
}

int hungarian()
{
    memset(missMatch, -1, sizeof(missMatch));
    memset(missEx, 0, sizeof(missEx));
    for (int i = 0; i < compNum; i++)
    {
        compEx[i] = arr[i][0];
        for (int j = 1; j < compNum; j++)
        {
            compEx[i] = max(compEx[i], arr[i][j]);
        }
    }

    for (int i = 0; i < compNum; i++)
    {
        for (int j = 0; j < missNum; j++)
            missNeed[j] = INT_MAX;

        while (true)
        {
            memset(compVisited, false, sizeof(compVisited));
            memset(missVisited, false, sizeof(missVisited));

            if (canFind(i))
                break;

            int minDelta = INT_MAX;
            for (int j = 0; j < missNum; j++)
            {
                if (!missVisited[j])
                    minDelta = min(minDelta, missNeed[j]);
            }

            for (int j = 0; j < compNum; j++)
            {
                if (compVisited[j])
                    compEx[j] -= minDelta;
            }
            for (int j = 0; j < missNum; j++)
            {
                if (missVisited[j])
                    missEx[j] += minDelta;
                else
                    missNeed[j] -= minDelta;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < missNum; i++)
    {
        if (missMatch[i] == -1)
            continue;
        ans += arr[missMatch[i]][i];
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> compNum >> missNum)
    {
        for (int i = 0; i < compNum; i++)
        {
            for (int j = 0; j < missNum; j++)
            {
                cin >> arr[i][j];
                arr[i][j] *= (compNum + 1);
            }
        }

        int cntEff = 0, changedNum = 0;
        for (int i = 0; i < compNum; i++)
        {
            cin >> cntCompMatch[i];
            cntCompMatch[i]--;
            cntEff += arr[i][cntCompMatch[i]] / (compNum + 1);
            arr[i][cntCompMatch[i]]++;
        }

        int ans = hungarian() / (compNum + 1);

        for (int i = 0; i < compNum; i++)
        {
            if (missMatch[cntCompMatch[i]] != i)
                changedNum++;
        }

        cout << changedNum << " " << ans - cntEff << endl;
    }
    return 0;
}

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
#define SIZE 201
#define INF 100001
using namespace std;

int arr[SIZE][SIZE];
int srcEx[SIZE], destEx[SIZE];
int destMatch[SIZE], destNeed[SIZE];
bool srcVisited[SIZE], destVisited[SIZE];
int cityNum;

bool canFind(int srcId)
{
    srcVisited[srcId] = true;
    for (int i = 0; i < cityNum; i++)
    {
        if (destVisited[i])
            continue;

        int delta = srcEx[srcId] + destEx[i] - arr[srcId][i];
        if (delta == 0)
        {
            destVisited[i] = true;
            if (destMatch[i] == -1 || canFind(destMatch[i]))
            {
                destMatch[i] = srcId;
                return true;
            }
        }
        else
        {
            destNeed[i] = min(destNeed[i], delta);
        }
    }
    return false;
}

int hungarian()
{
    memset(destMatch, -1, sizeof(destMatch));
    memset(destEx, 0, sizeof(destEx));

    for (int i = 0; i < cityNum; i++)
    {
        srcEx[i] = arr[i][0];
        for (int j = 1; j < cityNum; j++)
        {
            srcEx[i] = max(srcEx[i], arr[i][j]);
        }
    }

    for (int i = 0; i < cityNum; i++)
    {
        for (int j = 0; j < cityNum; j++)
            destNeed[j] = INF;

        while (true)
        {
            memset(srcVisited, false, sizeof(srcVisited));
            memset(destVisited, false, sizeof(destVisited));

            if (canFind(i))
                break;

            int minDelta = INF;
            for (int j = 0; j < cityNum; j++)
            {
                if (!destVisited[j])
                    minDelta = min(minDelta, destNeed[j]);
            }

            for (int j = 0; j < cityNum; j++)
            {
                if (srcVisited[j])
                    srcEx[j] -= minDelta;

                if (destVisited[j])
                    destEx[j] += minDelta;
                else
                    destNeed[j] -= minDelta;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < cityNum; i++)
    {
        ans += arr[destMatch[i]][i];
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int roadNum;
        cin >> cityNum >> roadNum;
        for (int i = 0; i < cityNum; i++)
        {
            for (int j = 0; j < cityNum; j++)
            {
                arr[i][j] = -INF;
            }
        }

        for (int i = 0; i < roadNum; i++)
        {
            int from, to, length;
            cin >> from >> to >> length;
            from--;
            to--;
            if (arr[from][to] < -length)
                arr[from][to] = -length;
        }

        int ans = hungarian();
        cout << -ans << endl;
    }
    return 0;
}

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
#define SIZE 1001
#define INF 100010
using namespace std;

int rankMat[SIZE][SIZE];
int arr[SIZE][SIZE];
int fstEx[SIZE], sndEx[SIZE];
int sndMatch[SIZE], sndNeed[SIZE];
bool fstVisited[SIZE], sndVisited[SIZE];

int vertexNum, picNum;

bool canFind(int fstId)
{
    fstVisited[fstId] = true;
    for (int i = 0; i < vertexNum; i++)
    {
        if (arr[fstId][i] == -INF)
            continue;
        if (sndVisited[i])
            continue;

        int delta = fstEx[fstId] + sndEx[i] - arr[fstId][i];
        if (delta == 0)
        {
            sndVisited[i] = true;
            if (sndMatch[i] == -1 || canFind(sndMatch[i]))
            {
                sndMatch[i] = fstId;
                return true;
            }
        }
        else
        {
            sndNeed[i] = min(sndNeed[i], delta);
        }
    }
    return false;
}

int hungarian()
{
    memset(sndMatch, -1, sizeof(sndMatch));
    memset(sndEx, 0, sizeof(sndEx));

    for (int i = 0; i < vertexNum; i++)
    {
        fstEx[i] = arr[i][0];
        for (int j = 1; j < vertexNum; j++)
        {
            fstEx[i] = max(fstEx[i], arr[i][j]);
        }
    }

    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
            sndNeed[j] = INF;
        }

        while (true)
        {
            memset(fstVisited, false, sizeof(fstVisited));
            memset(sndVisited, false, sizeof(sndVisited));

            if (canFind(i))
                break;

            int minDelta = INF;
            for (int j = 0; j < vertexNum; j++)
            {
                if (!sndVisited[j])
                    minDelta = min(minDelta, sndNeed[j]);
            }

            if (minDelta == INF)
                return 1;

            for (int j = 0; j < vertexNum; j++)
            {
                if (fstVisited[j])
                    fstEx[j] -= minDelta;

                if (sndVisited[j])
                    sndEx[j] += minDelta;
                else
                    sndNeed[j] -= minDelta;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < vertexNum; i++)
    {
        if (arr[sndMatch[i]][i] == -INF)
            return 1;
        ans += arr[sndMatch[i]][i];
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        int edgeNum;
        cin >> vertexNum >> edgeNum;
        for (int i = 0; i < vertexNum; i++)
        {
            for (int j = 0; j < vertexNum; j++)
            {
                arr[i][j] = -INF;
            }
        }

        for (int i = 0; i < edgeNum; i++)
        {
            int from, to, weight;
            cin >> from >> to >> weight;
            from--;
            to--;
            if (-arr[from][to] > weight)
            {
                arr[from][to] = -weight;
                arr[to][from] = -weight;
            }
        }

        int ans = -hungarian();
        cout << "Case " << t << ": ";
        if (ans == -1)
            cout << "NO" << endl;
        else
            cout << ans << endl;
    }
    return 0;
}

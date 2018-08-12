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
#define SIZE 201
#define INF 400010
using namespace std;
int arr[SIZE][SIZE];
int fstEx[SIZE], sndEx[SIZE];
int sndMatch[SIZE], sndNeed[SIZE];
bool fstVisited[SIZE], sndVisited[SIZE];
int snd[SIZE];
int sndNum, fstNum;

map<string, int> fstMap, sndMap;
int cntFstId, cntSndId;

bool canFind(int fstId)
{
    fstVisited[fstId] = true;
    for (int i = 0; i < sndNum; i++)
    {
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

    for (int i = 0; i < fstNum; i++)
    {
        fstEx[i] = arr[i][0];
        for (int j = 1; j < sndNum; j++)
        {
            fstEx[i] = max(fstEx[i], arr[i][j]);
        }
    }

    for (int i = 0; i < fstNum; i++)
    {
        for (int j = 0; j < sndNum; j++)
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
            for (int j = 0; j < sndNum; j++)
            {
                if (!sndVisited[j])
                    minDelta = min(minDelta, sndNeed[j]);
            }

            for (int j = 0; j < fstNum; j++)
            {
                if (fstVisited[j])
                    fstEx[j] -= minDelta;
            }
            for (int j = 0; j < sndNum; j++)
            {
                if (sndVisited[j])
                    sndEx[j] += minDelta;
                else
                    sndNeed[j] -= minDelta;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < sndNum; i++)
    {
        if (sndMatch[i] == -1 || arr[sndMatch[i]][i] == -INF)
            continue;
        ans += arr[sndMatch[i]][i];
    }
    return ans;
}

int getFstId(string &name)
{
    if (!fstMap.count(name))
        fstMap[name] = cntFstId++;
    return fstMap[name];
}

int getSndId(string &name)
{
    if (!sndMap.count(name))
        sndMap[name] = cntSndId++;
    return sndMap[name];
}

int main()
{
    ios::sync_with_stdio(false);
    int battleNum;
    while (cin >> fstNum >> sndNum >> battleNum)
    {
        cntFstId = 0;
        cntSndId = 0;
        fstMap.clear();
        sndMap.clear();
        for (int i = 0; i < fstNum; i++)
        {
            for (int j = 0; j < sndNum; j++)
            {
                arr[i][j] = -INF;
            }
        }
        while (battleNum--)
        {
            string fst, snd;
            int cost;
            cin >> fst >> snd >> cost;
            int fstId = getFstId(fst);
            int sndId = getSndId(snd);
            if (arr[fstId][sndId] < -cost)
                arr[fstId][sndId] = -cost;
        }

        int ans = hungarian();
        cout << -ans << endl;
    }
    return 0;
}

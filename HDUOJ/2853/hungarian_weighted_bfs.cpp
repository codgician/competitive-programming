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
int fstEx[SIZE], sndEx[SIZE];
int sndMatch[SIZE], sndNeed[SIZE], pre[SIZE];
bool sndVisited[SIZE];
int cntCompMatch[SIZE];
int sndNum, fstNum;

void bfs(int fstId)
{
    for (int i = 0; i < sndNum; i++)
    {
        sndVisited[i] = false;
        sndNeed[i] = INT_MAX;
        pre[i] = -1;
    }

    int cntSnd = -1;
    while (cntSnd == -1 || sndMatch[cntSnd] != -1)
    {
        int cntFst;
        if (cntSnd == -1)
            cntFst = fstId;
        else
        {
            cntFst = sndMatch[cntSnd];
            sndVisited[cntSnd] = true;
        }

        long long int minDelta = LLONG_MAX;
        int minSnd = -1;
        for (int i = 0; i < sndNum; i++)
        {
            if (!sndVisited[i])
            {
                if (sndNeed[i] > fstEx[cntFst] + sndEx[i] - arr[cntFst][i])
                {
                    sndNeed[i] = fstEx[cntFst] + sndEx[i] - arr[cntFst][i];
                    pre[i] = cntSnd;
                }

                if (sndNeed[i] < minDelta)
                {
                    minDelta = sndNeed[i];
                    minSnd = i;
                }
            }
        }

        fstEx[fstId] -= minDelta;
        for (int i = 0; i < sndNum; i++)
        {
            if (sndVisited[i])
            {
                fstEx[sndMatch[i]] -= minDelta;
                sndEx[i] += minDelta;
            }
            else
                sndNeed[i] -= minDelta;
        }

        cntSnd = minSnd;
    }

    while (cntSnd != -1)
    {
        if (pre[cntSnd] == -1)
            sndMatch[cntSnd] = fstId;
        else
            sndMatch[cntSnd] = sndMatch[pre[cntSnd]];
        cntSnd = pre[cntSnd];
    }
}

int hungarian()
{
    for (int i = 0; i < sndNum; i++)
    {
        sndMatch[i] = -1;
        sndEx[i] = 0;
    }

    for (int i = 0; i < fstNum; i++)
    {
        fstEx[i] = arr[i][0];
        for (int j = 1; j < sndNum; j++)
        {
            fstEx[i] = max(fstEx[i], arr[i][j]);
        }
    }

    for (int i = 0; i < sndNum; i++)
    {
        bfs(i);
    }

    int ans = 0;
    for (int i = 0; i < sndNum; i++)
    {
        if (sndMatch[i] != -1)
        {
            ans += arr[sndMatch[i]][i];
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> fstNum >> sndNum)
    {
        memset(arr, 0, sizeof(arr));
        for (int i = 0; i < fstNum; i++)
        {
            for (int j = 0; j < sndNum; j++)
            {
                cin >> arr[i][j];
                arr[i][j] *= (fstNum + 1);
            }
        }

        int cntEff = 0, changedNum = 0;
        for (int i = 0; i < fstNum; i++)
        {
            cin >> cntCompMatch[i];
            cntCompMatch[i]--;
            cntEff += arr[i][cntCompMatch[i]] / (fstNum + 1);
            arr[i][cntCompMatch[i]]++;
        }

        int ans = hungarian() / (fstNum + 1);

        for (int i = 0; i < fstNum; i++)
        {
            if (sndMatch[cntCompMatch[i]] != i)
                changedNum++;
        }

        cout << changedNum << " " << ans - cntEff << endl;
    }
    return 0;
}

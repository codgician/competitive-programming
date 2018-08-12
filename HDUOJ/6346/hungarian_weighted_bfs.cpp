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
using namespace std;

#define SIZE 210

int arr[SIZE][SIZE];
int fstEx[SIZE], sndEx[SIZE];
int sndMatch[SIZE], sndNeed[SIZE], pre[SIZE];
bool sndVisited[SIZE];
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

long long int hungarian()
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

    long long int ans = 0;
    for (int i = 0; i < sndNum; i++)
    {
        if (sndMatch[i] != -1)
            ans += arr[sndMatch[i]][i];
    }
    return ans;
}

int main()
{
    int caseNum, num;
    scanf("%d", &caseNum);
    for (int t = 1; t <= caseNum; t++)
    {
        scanf("%d", &num);
        for (int i = 0; i < num; i++)
        {
            for (int j = 0; j < num; j++)
            {
                scanf("%d", *(arr + i) + j);
                arr[i][j] *= -1;
            }
        }

        fstNum = num;
        sndNum = num;
        long long int ans = -hungarian();
        printf("Case #%d: %lld\n", t, ans);
    }
    return 0;
}
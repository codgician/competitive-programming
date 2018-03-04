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
using namespace std;

int arr[SIZE][SIZE];
int fstEx[SIZE], sndEx[SIZE];
int sndMatch[SIZE], sndNeed[SIZE];
bool fstVisited[SIZE], sndVisited[SIZE];
string card[SIZE];
int cardNum;

bool canFind(int fstId)
{
    fstVisited[fstId] = true;
    for (int i = 0; i < cardNum; i++)
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

    for (int i = 0; i < cardNum; i++)
    {
        fstEx[i] = arr[i][0];
        for (int j = 1; j < cardNum; j++)
        {
            fstEx[i] = max(fstEx[i], arr[i][j]);
        }
    }

    for (int i = 0; i < cardNum; i++)
    {
        for (int j = 0; j < cardNum; j++)
        {
            sndNeed[j] = INT_MAX;
        }

        while (true)
        {
            memset(fstVisited, false, sizeof(fstVisited));
            memset(sndVisited, false, sizeof(sndVisited));

            if (canFind(i))
                break;

            int minDelta = INT_MAX;
            for (int j = 0; j < cardNum; j++)
            {
                if (!sndVisited[j])
                    minDelta = min(minDelta, sndNeed[j]);
            }

            for (int j = 0; j < cardNum; j++)
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
    for (int i = 0; i < cardNum; i++)
    {
        ans += arr[sndMatch[i]][i];
    }
    return ans;
}

int getScore(string &a, string &b)
{
    int aPt = a.length() - 1, bPt = 0, ans = 0;
    while (a[aPt] == b[bPt] && aPt >= 0 && bPt < b.length())
    {
        aPt--;
        bPt++;
        ans++;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> cardNum)
    {
        for (int i = 0; i < cardNum; i++)
        {
            cin >> card[i];
        }

        for (int i = 0; i < cardNum; i++)
        {
            for (int j = 0; j < cardNum; j++)
            {
                if (i == j)
                    arr[i][j] = 0;
                else
                    arr[i][j] = getScore(card[i], card[j]);
            }
        }

        int ans = hungarian();
        cout << ans << endl;
    }
    return 0;
}

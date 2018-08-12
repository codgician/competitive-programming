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
#define SIZE 101
using namespace std;

int arr[SIZE][SIZE];
int score[SIZE];
int fstHp[SIZE], sndHp[SIZE];
int fstAttack[SIZE], sndAttack[SIZE];
int fstEx[SIZE], sndEx[SIZE];
int sndMatch[SIZE], sndNeed[SIZE];
bool fstVisited[SIZE], sndVisited[SIZE];

int bruteNum;

bool canFind(int fstId)
{
    fstVisited[fstId] = true;
    for (int i = 0; i < bruteNum; i++)
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

    for (int i = 0; i < bruteNum; i++)
    {
        fstEx[i] = arr[i][0];
        for (int j = 1; j < bruteNum; j++)
        {
            fstEx[i] = max(fstEx[i], arr[i][j]);
        }
    }

    for (int i = 0; i < bruteNum; i++)
    {
        for (int j = 0; j < bruteNum; j++)
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
            for (int j = 0; j < bruteNum; j++)
            {
                if (!sndVisited[j])
                    minDelta = min(minDelta, sndNeed[j]);
            }

            for (int j = 0; j < bruteNum; j++)
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
    for (int i = 0; i < bruteNum; i++)
    {
        ans += arr[sndMatch[i]][i] / (bruteNum + 1);
        if (sndMatch[i] == i && arr[sndMatch[i]][i] < 0)
            ans--;
    }
    return ans;
}

bool canWin(int fstId, int sndId)
{
    int fstRound = fstHp[fstId] / sndAttack[sndId];
    if (fstHp[fstId] % sndAttack[sndId] != 0)
        fstRound++;
    int sndRound = sndHp[sndId] / fstAttack[fstId];
    if (sndHp[sndId] % fstAttack[fstId] != 0)
        sndRound++;

    if (fstRound >= sndRound)
        return true;
    else
        return false;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> bruteNum)
    {
        if (bruteNum == 0)
            break;

        for (int i = 0; i < bruteNum; i++)
        {
            int cnt;
            cin >> score[i];
        }
        for (int i = 0; i < bruteNum; i++)
        {
            cin >> fstHp[i];
        }
        for (int i = 0; i < bruteNum; i++)
        {
            cin >> sndHp[i];
        }
        for (int i = 0; i < bruteNum; i++)
        {
            cin >> fstAttack[i];
        }
        for (int i = 0; i < bruteNum; i++)
        {
            cin >> sndAttack[i];
        }

        for (int i = 0; i < bruteNum; i++)
        {
            for (int j = 0; j < bruteNum; j++)
            {
                if (canWin(i, j))
                {
                    arr[i][j] = score[i] * (bruteNum + 1);
                }
                else
                {
                    arr[i][j] = -score[i] * (bruteNum + 1);
                }

                if (i == j)
                    arr[i][j]++;
            }
        }

        int ans = hungarian();
        if (ans < 0)
        {
            cout << "Oh, I lose my dear seaco!" << endl;
        }
        else
        {
            cout << ans << " ";
            int sameNum = 0;
            for (int i = 0; i < bruteNum; i++)
            {
                if (sndMatch[i] == i)
                {
                    sameNum++;
                }
            }
            cout << fixed << setprecision(3) << (double)sameNum / bruteNum * 100 << "%" << endl;
        }
    }
    return 0;
}

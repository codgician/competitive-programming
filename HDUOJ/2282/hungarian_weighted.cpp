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
#define SIZE 501
using namespace std;

int arr[SIZE][SIZE];
int chocoEx[SIZE], boxEx[SIZE];
int boxMatch[SIZE], boxNeed[SIZE];
bool chocoVisited[SIZE], boxVisited[SIZE];
int box[SIZE];
int boxNum, chocoNum;

bool canFind(int chocoId)
{
    chocoVisited[chocoId] = true;
    for (int i = 0; i < boxNum; i++)
    {
        if (boxVisited[i])
            continue;

        int delta = chocoEx[chocoId] + boxEx[i] - arr[chocoId][i];
        if (delta == 0)
        {
            boxVisited[i] = true;
            if (boxMatch[i] == -1 || canFind(boxMatch[i]))
            {
                boxMatch[i] = chocoId;
                return true;
            }
        }
        else
        {
            boxNeed[i] = min(boxNeed[i], delta);
        }
    }
    return false;
}

int hungarian()
{
    memset(boxMatch, -1, sizeof(boxMatch));
    memset(boxEx, 0, sizeof(boxEx));

    for (int i = 0; i < chocoNum; i++)
    {
        chocoEx[i] = arr[i][0];
        for (int j = 1; j < boxNum; j++)
        {
            chocoEx[i] = max(chocoEx[i], arr[i][j]);
        }
    }

    for (int i = 0; i < chocoNum; i++)
    {
        for (int j = 0; j < boxNum; j++)
        {
            boxNeed[j] = INT_MAX;
        }

        while (true)
        {
            memset(chocoVisited, false, sizeof(chocoVisited));
            memset(boxVisited, false, sizeof(boxVisited));

            if (canFind(i))
                break;

            int minDelta = INT_MAX;
            for (int j = 0; j < boxNum; j++)
            {
                if (!boxVisited[j])
                    minDelta = min(minDelta, boxNeed[j]);
            }

            for (int j = 0; j < chocoNum; j++)
            {
                if (chocoVisited[j])
                    chocoEx[j] -= minDelta;
            }
            for (int j = 0; j < boxNum; j++)
            {
                if (boxVisited[j])
                    boxEx[j] += minDelta;
                else
                    boxNeed[j] -= minDelta;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < boxNum; i++)
    {
        if (boxMatch[i] == -1)
            continue;
        ans += arr[boxMatch[i]][i];
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> boxNum)
    {
        chocoNum = 0;
        for (int i = 0; i < boxNum; i++)
        {
            cin >> box[i];
            for (int j = 0; j < box[i]; j++)
            {
                for (int k = 0; k < boxNum; k++)
                {
                    int cnt = abs(i - k);
                    if (cnt > (boxNum >> 1))
                        cnt = boxNum - cnt;
                    arr[chocoNum + j][k] = -cnt;
                }
            }
            chocoNum += box[i];
        }

        int ans = hungarian();
        cout << -ans << endl;
    }
    return 0;
}


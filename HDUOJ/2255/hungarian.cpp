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
#define SIZE 301
using namespace std;

int arr[SIZE][SIZE];
int houseEx[SIZE], buyerEx[SIZE];
int buyerMatch[SIZE], buyerNeed[SIZE];
bool houseVisited[SIZE], buyerVisited[SIZE];
int houseNum;

bool canFind(int houseId)
{
    houseVisited[houseId] = true;
    for (int i = 0; i < houseNum; i++)
    {
        if (buyerVisited[i])
            continue;

        int delta = houseEx[houseId] + buyerEx[i] - arr[houseId][i];
        if (delta == 0)
        {
            buyerVisited[i] = true;
            if (buyerMatch[i] == -1 || canFind(buyerMatch[i]))
            {
                buyerMatch[i] = houseId;
                return true;
            }
        }
        else
        {
            buyerNeed[i] = min(buyerNeed[i], delta);
        }
    }
    return false;
}

int hungarain()
{
    memset(buyerMatch, -1, sizeof(buyerMatch));
    memset(buyerEx, 0, sizeof(buyerEx));
    memset(houseEx, 0, sizeof(houseEx));

    for (int i = 0; i < houseNum; i++)
    {
        for (int j = 0; j < houseNum; j++)
        {
            houseEx[i] = max(houseEx[i], arr[i][j]);
        }
    }

    for (int i = 0; i < houseNum; i++)
    {
        for (int j = 0; j < houseNum; j++)
            buyerNeed[j] = INT_MAX;

        while (true)
        {
            memset(houseVisited, false, sizeof(houseVisited));
            memset(buyerVisited, false, sizeof(buyerVisited));

            if (canFind(i))
                break;

            int minDelta = INT_MAX;
            for (int j = 0; j < houseNum; j++)
            {
                if (!buyerVisited[j])
                    minDelta = min(minDelta, buyerNeed[j]);
            }

            for (int j = 0; j < houseNum; j++)
            {
                if (houseVisited[j])
                    houseEx[j] -= minDelta;

                if (buyerVisited[j])
                    buyerEx[j] += minDelta;
                else
                    buyerNeed[j] -= minDelta;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < houseNum; i++)
    {
        if (buyerMatch[i] != -1)
            ans += arr[buyerMatch[i]][i];
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> houseNum)
    {
        memset(arr, 0, sizeof(arr));
        for (int i = 0; i < houseNum; i++)
        {
            for (int j = 0; j < houseNum; j++)
            {
                cin >> arr[i][j];
            }
        }
        int ans = hungarain();
        cout << ans << endl;
    }
    return 0;
}

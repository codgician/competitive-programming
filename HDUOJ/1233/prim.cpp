#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define INF 999999999
#define SIZE 101
using namespace std;

int road[SIZE][SIZE];
int dis[SIZE];  // The minimum distance to the spawned tree.
bool isInTree[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int villageNum;
    while (cin >> villageNum)
    {
        if (villageNum == 0)
            break;

        int roadNum = villageNum * (villageNum - 1) / 2;

        for (int i = 0; i < villageNum; i++)
        {
            for (int j = 0; j < villageNum; j++)
            {
                if (i == j)
                    road[i][j] = 0;
                else
                    road[i][j] = INF;
            }
        }

        for (int i = 0; i < roadNum; i++)
        {
            int a, b, length;
            cin >> a >> b >> length;
            road[a - 1][b - 1] = length;
            road[b - 1][a - 1] = length;
        }

        memset(isInTree, false, sizeof(isInTree));
        for (int i = 0; i < villageNum; i++)
        {
            dis[i] = road[0][i];
        }

        int ans = 0, num = 1;
        isInTree[0] = true;
        while (num < villageNum)
        {
            int minDistance = INF, minDistanceIndex;
            for (int i = 0; i < villageNum; i++)
            {
                if (!isInTree[i] && dis[i] < minDistance)
                {
                    minDistance = dis[i];
                    minDistanceIndex = i;
                }
            }
            isInTree[minDistanceIndex] = true;
            ans += dis[minDistanceIndex];
            num++;

            for (int i = 0; i < villageNum; i++)
            {
                if (!isInTree[i] && dis[i] > road[minDistanceIndex][i])
                {
                    dis[i] = road[minDistanceIndex][i];
                }
            }
        }

        cout << ans << endl;
    }
    return 0;
}

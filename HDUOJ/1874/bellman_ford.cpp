#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SIZE 201
#define INF 100000001
using namespace std;

int arr[SIZE][SIZE], dis[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int townNum, roadNum;
    while (cin >> townNum >> roadNum)
    {
        for (int i = 0; i < townNum; i++)
        {
            for (int j = 0; j < townNum; j++)
            {
                if (i == j)
                    arr[i][j] = 0;
                else
                    arr[i][j] = INF;
            }
        }

        for (int i = 0; i < roadNum; i++)
        {
            int from, to, len;
            cin >> from >> to >> len;
            if (len < arr[from][to])
            {
                arr[from][to] = len;
                arr[to][from] = len;
            }
        }

        int startPt, endPt;
        cin >> startPt >> endPt;
        for (int i = 0; i < townNum; i++)
        {
            dis[i] = INF;
        }
        dis[startPt] = 0;

        for (int t = 0; t < townNum - 1; t++)
        {
            bool hasChanged = false;
            for (int i = 0; i < townNum; i++)
            {
                for (int j = 0; j < townNum; j++)
                {
                    if (arr[i][j] == INF)
                        continue;

                    if (dis[i] > dis[j] + arr[j][i])
                    {
                        hasChanged = true;
                        dis[i] = dis[j] + arr[j][i];
                    }
                }
            }

            if (!hasChanged)
                break;
        }

        if (dis[endPt] == INF)
        {
            cout << -1 << endl;
        }
        else
        {
            cout << dis[endPt] << endl;
        }
    }
    return 0;
}

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

int arr[SIZE][SIZE];
int dis[SIZE];
bool isShortest[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int townNum, roadNum;
    while (cin >> townNum >> roadNum)
    {
        if (townNum == 0 && roadNum == 0)
            break;

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
            from--;
            to--;
            if (len < arr[from][to])
            {
                arr[from][to] = len;
                arr[to][from] = len;
            }
        }

        int startPt = 0, endPt = townNum - 1;

        memset(isShortest, false, sizeof(isShortest));
        isShortest[startPt] = true;
        for (int i = 0; i < townNum; i++)
        {
            dis[i] = arr[startPt][i];
        }

        for (int t = 0; t < townNum - 1; t++)
        {
            int minLen = INF, minPt = -1;
            for (int i = 0; i < townNum; i++)
            {
                if (!isShortest[i] && dis[i] < minLen)
                {
                    minLen = dis[i];
                    minPt = i;
                }
            }

            if (minPt == -1)
                break;

            isShortest[minPt] = true;
            for (int i = 0; i < townNum; i++)
            {
                if (arr[minPt][i] != INF)
                {
                    dis[i] = min(dis[i], dis[minPt] + arr[minPt][i]);
                }
            }
        }

            cout << dis[endPt] << endl;
    }
    return 0;
}

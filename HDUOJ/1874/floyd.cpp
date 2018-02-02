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
            if (len < arr[to][from])
            {
                arr[to][from] = len;
                arr[from][to] = len;
            }
        }

        for (int k = 0; k < townNum; k++)
        {
            for (int i = 0; i < townNum; i++)
            {
                for (int j = 0; j < townNum; j++)
                {
                    arr[i][j] = min(arr[i][j], arr[i][k] + arr[k][j]);
                }
            }
        }

        int startPt, endPt;
        cin >> startPt >> endPt;
        if (arr[startPt][endPt] == INF)
        {
            cout << -1 << endl;
        }
        else
        {
            cout << arr[startPt][endPt] << endl;
        }
    }
    return 0;
}

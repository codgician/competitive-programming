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
#define SIZE 99
using namespace std;

typedef struct _Node
{
    int x;
    int y;
} Node;

Node arr[SIZE];
int path[SIZE], dp[SIZE];
double dis[SIZE][SIZE], bin[SIZE * SIZE];

int nodeNum, pickNum, maxNum;
double ans, cntDis = 0;

double getDistance(Node a, Node b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool canAdd(int cntPt, int cntNum)
{
    for (int i = 0; i < cntNum; i++)
    {
        if (dis[cntPt][path[i]] < cntDis)
        {
            return false;
        }
    }
    return true;
}

void dfs(int cntPt, int cntNum)
{
    maxNum = max(maxNum, cntNum);
    if (maxNum >= pickNum)
        return;

    if (cntNum + nodeNum - cntPt - 1 <= maxNum)
        return;

    for (int i = cntPt + 1; i < nodeNum; i++)
    {
        if (dp[i] + cntNum <= maxNum)
            return;

        if (canAdd(i, cntNum))
        {
            path[cntNum] = i;
            dfs(i, cntNum + 1);
        }

        if (maxNum >= pickNum)
            return;
    }
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> nodeNum >> pickNum)
    {
        int binPt = 0;
        for (int i = 0; i < nodeNum; i++)
        {
            cin >> arr[i].x >> arr[i].y;
            for (int j = 0; j < i; j++)
            {
                dis[i][j] = getDistance(arr[i], arr[j]);
                dis[j][i] = dis[i][j];
                bin[binPt++] = dis[i][j];
            }
        }
        sort(bin + 0, bin + binPt);

        int leftPt = 0, rightPt = binPt - 1;
        while (leftPt <= rightPt)
        {
            int midPt = (leftPt + rightPt) >> 1;
            cntDis = bin[midPt];

            maxNum = 1;
            dp[nodeNum - 1] = 1;
            for (int i = nodeNum - 2; i >= 0; i--)
            {
                path[0] = i;
                dfs(i, 1);
                dp[i] = maxNum;
                if (maxNum >= pickNum)
                    break;
            }

            if (maxNum >= pickNum)
            {
                leftPt = midPt + 1;
                ans = cntDis;
            }
            else
            {
                rightPt = midPt - 1;
            }
        }
        cout << fixed << setprecision(2) << sqrt(ans) << endl;
    }
    return 0;
}

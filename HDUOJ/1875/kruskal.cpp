#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 101
using namespace std;

typedef struct _Island {
    int x;
    int y;
} island;

typedef struct _Bridge {
    int startPt;
    int endPt;
    double length;
} bridge;

island islandArr[SIZE];
bridge bridgeArr[SIZE * SIZE];
int arr[SIZE];
int bridgeArrPt;

double getLength(island a, island b)
{
    return sqrt((double)(a.x - b.x) * (a.x - b.x) + (double)(a.y - b.y) * (a.y - b.y));
}

bool cmpRule (bridge a, bridge b)
{
    return a.length < b.length;
}

int getParent(int n)
{
    if (arr[n] == n)
        return n;
    else
    {
        arr[n] = getParent(arr[n]);
        return arr[n];
    }
}

bool mergeIsland(int a, int b)
{
    int aParent = getParent(a);
    int bParent = getParent(b);

    if (aParent != bParent)
    {
        arr[bParent] = aParent;
        return true;
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        bridgeArrPt = 0;
        int islandNum;
        cin >> islandNum;
        for (int i = 0; i < islandNum; i++)
        {
            cin >> islandArr[i].x >> islandArr[i].y;
            for (int j = 0; j < i; j++)
            {
                bridge tmp;
                tmp.startPt = j;
                tmp.endPt = i;
                tmp.length = getLength(islandArr[i], islandArr[j]);
                if (tmp.length >= 10 && tmp.length <= 1000)
                    bridgeArr[bridgeArrPt++] = tmp;
            }
        }

        sort(bridgeArr + 0, bridgeArr + bridgeArrPt, cmpRule);

        double ans = 0, num = 0;
        for (int i = 0; i < islandNum; i++)
            arr[i] = i;

        for (int i = 0; i < bridgeArrPt && num < islandNum - 1; i++)
        {
            if (mergeIsland(bridgeArr[i].startPt, bridgeArr[i].endPt))
            {
                ans += bridgeArr[i].length;
                num++;
            }
        }

        int rootNum = 0;
        for (int i = 0; i < islandNum; i++)
        {
            if (arr[i] == i)
            {
                rootNum++;
            }
            if (rootNum > 1)
                break;
        }

        if (rootNum > 1)
            cout << "oh!" << endl;
        else
            cout << fixed << setprecision(1) << ans * 100 << endl;
    }
    return 0;
}

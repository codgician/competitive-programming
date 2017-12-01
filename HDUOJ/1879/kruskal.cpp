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

typedef struct _Road {
    int startPt;
    int endPt;
    int cost;
} road;

road roadArr[SIZE * SIZE];
int arr[SIZE];

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

bool mergeVillage(int a, int b)
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

bool cmpRule(road a, road b)
{
    return a.cost < b.cost;
}

int main()
{
    ios::sync_with_stdio(false);
    int villageNum;
    while (cin >> villageNum)
    {
        if (villageNum == 0)
            break;

        int roadNum = villageNum * (villageNum - 1) / 2;
        for (int i = 0; i < roadNum; i++)
        {
            cin >> roadArr[i].startPt >> roadArr[i].endPt >> roadArr[i].cost;
            bool isEstablished;
            cin >> isEstablished;
            if (isEstablished)
                roadArr[i].cost = 0;
        }

        sort (roadArr + 0, roadArr + roadNum, cmpRule);

        long long int ans = 0;
        int num = 0;
        for (int i = 0; i < villageNum; i++)
            arr[i] = i;
        for (int i = 0; i < roadNum && num < villageNum - 1; i++)
        {
            if (mergeVillage(roadArr[i].startPt - 1, roadArr[i].endPt - 1))
            {
                ans += roadArr[i].cost;
                num++;
            }
        }

        cout << ans << endl;
    }
    return 0;
}

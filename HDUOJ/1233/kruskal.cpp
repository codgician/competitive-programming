#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 10000001
using namespace std;

typedef struct _Road {
    int startPt;
    int endPt;
    int length;
} road;

road arr[SIZE];
int parent[SIZE];

int getParent(int n)
{
    if (parent[n] == n)
        return n;
    else
    {
        parent[n] = getParent(parent[n]);
        return parent[n];
    }
}

bool mergeVillage(int a, int b)
{
    int aParent = getParent(a);
    int bParent = getParent(b);

    if (aParent != bParent)
    {
        parent[bParent] = aParent;
        return true;
    }

    return false;
}

bool cmpRule(road a, road b)
{
    return a.length < b.length;
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
            cin >> arr[i].startPt >> arr[i].endPt >> arr[i].length;
        }

        sort(arr + 0, arr + roadNum, cmpRule);

        long long int ans = 0;
        int num = 0;
        for (int i = 0; i < villageNum; i++)
        {
            parent[i] = i;
        }
        for (int i = 0; i < roadNum && num < villageNum - 1; i++)
        {
            if (mergeVillage(arr[i].startPt - 1, arr[i].endPt - 1))
            {
                num++;
                ans += arr[i].length;
            }
        }

        cout << ans << endl;
    }
    return 0;
}

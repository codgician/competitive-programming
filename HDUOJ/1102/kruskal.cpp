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
    int length;
} road;

road roadArr[SIZE * SIZE / 2];
int arr[SIZE];
int roadArrPt = 0;

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
    return a.length < b.length;
}

int main()
{
    ios::sync_with_stdio(false);
    int villageNum;
    while (cin >> villageNum)
    {
        roadArrPt = 0;
        for (int i = 0; i < villageNum; i++)
        {
            for (int j = 0; j < villageNum; j++)
            {
                int tmp;
                cin >> tmp;
                if (i < j)
                {
                    roadArr[roadArrPt].startPt = i;
                    roadArr[roadArrPt].endPt = j;
                    roadArr[roadArrPt].length = tmp;
                    roadArrPt++;
                }
            }
        }
        int builtNum;
        cin >> builtNum;
        for (int i = 0; i < builtNum; i++)
        {
            int startPt, endPt;
            cin >> startPt >> endPt;
            startPt--;
            endPt--;
            if (startPt > endPt)
            {
                swap(startPt, endPt);
            }
            for (int j = 0; j < roadArrPt; j++)
            {
                if (roadArr[j].startPt == startPt && roadArr[j].endPt == endPt)
                {
                    roadArr[j].length = 0;
                    break;
                }
            }
        }

        sort(roadArr + 0, roadArr + roadArrPt, cmpRule);

        long long int ans = 0;
        int num = 0;
        for (int i = 0; i < villageNum; i++)
            arr[i] = i;
        for (int i = 0; i < roadArrPt && num < villageNum - 1; i++)
        {
            if (mergeVillage(roadArr[i].startPt, roadArr[i].endPt))
            {
                ans += roadArr[i].length;
                num++;
            }
        }

        cout << ans << endl;
    }
    return 0;
}

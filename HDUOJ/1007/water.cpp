#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <climits>
#define SIZE 100010
using namespace std;

typedef struct Node {
    double x;
    double y;
} toy;

toy arr[SIZE];

double getDistanceSquare(toy a, toy b)
{
    return pow((a.x - b.x), 2) + pow((a.y - b.y), 2);
}

bool cmpRuleX(toy a, toy b)
{
    if (a.x == b.x)
        return a.y < b.y;
    else
        return a.x < b.x;
}

bool cmpRuleY(toy a, toy b)
{
    if (a.y == b.y)
        return a.x < b.x;
    else
        return a.y < b.y;
}

int main()
{
    ios::sync_with_stdio(false);
    int dotNum;
    while (cin >> dotNum)
    {
        if (dotNum == 0)
            break;
        for (int t = 0; t < dotNum; t++)
            cin >> arr[t].x >> arr[t].y;

        sort(arr, arr + dotNum, cmpRuleX);

        double minDistanceSquare = INT_MAX;

        for (int i = 0; i < dotNum - 1; i++)
        {
            double distance = getDistanceSquare(arr[i], arr[i + 1]);
            if (distance < minDistanceSquare)
                minDistanceSquare = distance;
        }

        sort(arr, arr + dotNum, cmpRuleY);

        for (int i = 0; i < dotNum - 1; i++)
        {
            double distance = getDistanceSquare(arr[i], arr[i + 1]);
            if (distance < minDistanceSquare)
                minDistanceSquare = distance;
        }

        printf("%.2lf\n", sqrt(minDistanceSquare) / 2);

    }
    return 0;
}

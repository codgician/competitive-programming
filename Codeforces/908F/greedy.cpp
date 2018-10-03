#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define RED 0
#define GREEN 1
#define BLUE 2
#define SIZE 300001
using namespace std;

typedef struct _Point {
    int color;
    long long int distance;
} point;

point arr[SIZE];

bool cmpRule(point a, point b)
{
    return a.distance < b.distance;
}

int main()
{
    ios::sync_with_stdio(false);
    int pointNum;
    cin >> pointNum;
    for (int i = 0; i < pointNum; i++)
    {
        cin >> arr[i].distance;
        char ch;
        cin >> ch;
        if (ch == 'G')
        {
            arr[i].color = GREEN;
        }
        else if (ch == 'R')
        {
            arr[i].color = RED;
        }
        else if (ch == 'B')
        {
            arr[i].color = BLUE;
        }
    }

    sort(arr + 0, arr + pointNum, cmpRule);

    int pt = 0;
    while (arr[pt].color != GREEN && pt < pointNum)
    {
        pt++;
    }
    int minGreenPt = pt;
    pt = pointNum - 1;
    while (arr[pt].color != GREEN && pt >= 0)
    {
        pt--;
    }
    int maxGreenPt = pt;

    long long int ans = 0;

    // If no green points (orz!)
    if (minGreenPt == pointNum && maxGreenPt == -1)
    {
        pt = 0;
        while (arr[pt].color != RED && pt < pointNum)
        {
            pt++;
        }
        int minRedPt = pt;
        pt = pointNum - 1;
        while (arr[pt].color != RED && pt >= 0)
        {
            pt--;
        }
        int maxRedPt = pt;

        if (minRedPt < pointNum && maxRedPt >= 0)
        {
            ans += arr[maxRedPt].distance - arr[minRedPt].distance;
        }

        pt = 0;
        while (arr[pt].color != BLUE && pt < pointNum)
        {
            pt++;
        }
        int minBluePt = pt;
        pt = pointNum - 1;
        while (arr[pt].color != BLUE && pt >= 0)
        {
            pt--;
        }
        int maxBluePt = pt;

        if (minBluePt < pointNum && maxBluePt >= 0)
        {
            ans += arr[maxBluePt].distance - arr[minBluePt].distance;
        }
    }
    else
    {
        bool redFlag = false, blueFlag = false;
        for (int i = 0; i < minGreenPt; i++)
        {
            if (!redFlag && arr[i].color == RED)
            {
                ans += (arr[minGreenPt].distance - arr[i].distance);
                redFlag = true;
            }
            if (!blueFlag && arr[i].color == BLUE)
            {
                ans += (arr[minGreenPt].distance - arr[i].distance);
                blueFlag = true;
            }
            if (redFlag && blueFlag)
                break;
        }

        int prevRed = minGreenPt, prevBlue = minGreenPt, prevGreen = minGreenPt;
        long long int maxRedInterval = 0, maxBlueInterval = 0;
        for (int i = minGreenPt + 1; i <= maxGreenPt; i++)
        {
            if (arr[i].color == RED)
            {
                maxRedInterval = max(maxRedInterval, arr[i].distance - arr[prevRed].distance);
                prevRed = i;
            }
            else if (arr[i].color == BLUE)
            {
                maxBlueInterval = max(maxBlueInterval, arr[i].distance - arr[prevBlue].distance);
                prevBlue = i;
            }
            else if (arr[i].color == GREEN)
            {
                maxRedInterval = max(maxRedInterval, arr[i].distance - arr[prevRed].distance);
                maxBlueInterval = max(maxBlueInterval, arr[i].distance - arr[prevBlue].distance);
                ans += min((arr[i].distance - arr[prevGreen].distance) * 2, (arr[i].distance - arr[prevGreen].distance) * 3 - maxRedInterval - maxBlueInterval);
                maxRedInterval = 0;
                maxBlueInterval = 0;
                prevRed = i;
                prevBlue = i;
                prevGreen = i;
            }
        }

        redFlag = false, blueFlag = false;
        for (int i = pointNum - 1; i > maxGreenPt; i--)
        {
            if (!redFlag && arr[i].color == RED)
            {
                ans += (arr[i].distance - arr[maxGreenPt].distance);
                redFlag = true;
            }
            if (!blueFlag && arr[i].color == BLUE)
            {
                ans += (arr[i].distance - arr[maxGreenPt].distance);
                blueFlag = true;
            }
            if (redFlag && blueFlag)
                break;
        }
    }
    cout << ans << endl;
    return 0;
}

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

#define SIZE 1010

const double eps = 1e-6;

int takeOff[SIZE], land[SIZE];
int planetNum;
double weight;

inline bool check(double cntFuel)
{
    cntFuel -= (weight + cntFuel) / takeOff[0];
    if (cntFuel < 0)
        return false;

    for (int i = 1; i < planetNum; i++)
    {
        cntFuel -= (weight + cntFuel) / land[i];
        if (cntFuel < 0)
            return false;
        cntFuel -= (weight + cntFuel) / takeOff[i];
        if (cntFuel < 0)
            return false;
    }

    cntFuel -= (weight + cntFuel) / land[0];
    if (cntFuel < 0)
        return false;
    return true;
}

int main()
{
    scanf("%d%lf", &planetNum, &weight);
    for (int i = 0; i < planetNum; i++)
        scanf("%d", takeOff + i);
    for (int i = 0; i < planetNum; i++)
        scanf("%d", land + i);

    double leftPt = 0, rightPt = 1e9 + 1;
    double ans = -1;
    while (rightPt - leftPt > eps)
    {
        double midPt = (leftPt + rightPt) / 2;
        if (check(midPt))
        {
            rightPt = midPt;
            ans = midPt;
        }
        else
        {
            leftPt = midPt;
        }
    }

    if (ans > 0)
        printf("%.6lf\n", ans);
    else
        puts("-1");
    return 0;
}
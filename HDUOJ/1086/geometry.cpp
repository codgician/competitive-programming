#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#define SIZE 101
using namespace std;

typedef struct _Dot {
    double x;
    double y;
} dot;

typedef struct _Segment {
    dot startPt;
    dot endPt;
} segment;

segment arr[SIZE];

double getCrossedProduct(dot a, dot b)
{
    return a.x * b.y - b.x * a.y;
}

dot dotMinus(dot a, dot b)
{
    dot ans;
    ans.x = a.x - b.x;
    ans.y = a.y - b.y;
    return ans;
}

bool isOnSegment(segment a, dot b)
{
    double xMin = min(a.startPt.x, a.endPt.x);
    double xMax = max(a.startPt.x, a.endPt.x);
    double yMin = min(a.startPt.y, a.endPt.y);
    double yMax = max(a.startPt.y, a.endPt.y);

    return b.x >= xMin && b.x <= xMax && b.y >= yMin && b.y <= yMax;
}

bool hasIntersect(segment a, segment b)
{
    double cp1 = getCrossedProduct(dotMinus(a.endPt, a.startPt), dotMinus(b.startPt, a.startPt));
    double cp2 = getCrossedProduct(dotMinus(a.endPt, a.startPt), dotMinus(b.endPt, a.startPt));
    double cp3 = getCrossedProduct(dotMinus(b.endPt, b.startPt), dotMinus(a.startPt, b.startPt));
    double cp4 = getCrossedProduct(dotMinus(b.endPt, b.startPt), dotMinus(a.endPt, b.startPt));

    if (cp1 * cp2 < 0 && cp3 * cp4 < 0)
        return true;
    else if (cp1 == 0 && isOnSegment(a, b.startPt))
        return true;
    else if (cp2 == 0 && isOnSegment(a, b.endPt))
        return true;
    else if (cp3 == 0 && isOnSegment(b, a.startPt))
        return true;
    else if (cp4 == 0 && isOnSegment(b, a.endPt))
        return true;
    else
        return false;
}

int main()
{
    ios::sync_with_stdio(false);
    int segmentNum;
    while (cin >> segmentNum)
    {
        if (segmentNum == 0)
            break;
        for (int i = 0; i < segmentNum; i++)
        {
            cin >> arr[i].startPt.x >> arr[i].startPt.y >> arr[i].endPt.x >> arr[i].endPt.y;
        }

        int ans = 0;
        for (int i = 0; i < segmentNum; i++)
        {
            for (int j = i + 1; j < segmentNum; j++)
            {
                if (hasIntersect(arr[i], arr[j]))
                    ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

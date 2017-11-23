#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#define SIZE 101
using namespace std;

typedef struct _Node {
    double x;
    double y;
} node;

typedef struct _Line {
    node startPt;
    node endPt;
} line;

line arr[SIZE];

double getCrossedProduct(node a, node b)
{
    return a.x * b.y - b.x * a.y;
}

node nodeMinus(node a, node b)
{
    node ans;
    ans.x = a.x - b.x;
    ans.y = a.y - b.y;
    return ans;
}

bool isOnSegment(line a, node b)
{
    double xMin = min(a.startPt.x, a.endPt.x);
    double xMax = max(a.startPt.x, a.endPt.x);
    double yMin = min(a.startPt.y, a.endPt.y);
    double yMax = max(a.startPt.y, a.endPt.y);

    return b.x >= xMin && b.x <= xMax && b.y >= yMin && b.y <= yMax;
}

bool hasIntersect(line a, line b)
{
    double cp1 = getCrossedProduct(nodeMinus(a.endPt, a.startPt), nodeMinus(b.startPt, a.startPt));
    double cp2 = getCrossedProduct(nodeMinus(a.endPt, a.startPt), nodeMinus(b.endPt, a.startPt));
    double cp3 = getCrossedProduct(nodeMinus(b.endPt, b.startPt), nodeMinus(a.startPt, b.startPt));
    double cp4 = getCrossedProduct(nodeMinus(b.endPt, b.startPt), nodeMinus(a.endPt, b.startPt));

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
    int lineNum;
    while (cin >> lineNum)
    {
        if (lineNum == 0)
            break;
        for (int i = 0; i < lineNum; i++)
        {
            cin >> arr[i].startPt.x >> arr[i].startPt.y >> arr[i].endPt.x >> arr[i].endPt.y;
        }

        int ans = 0;
        for (int i = 0; i < lineNum; i++)
        {
            for (int j = i + 1; j < lineNum; j++)
            {
                if (hasIntersect(arr[i], arr[j]))
                    ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

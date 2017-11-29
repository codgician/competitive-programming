#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#define SIZE 1001
using namespace std;

typedef struct _Dot {
    double x;
    double y;
} dot;

typedef struct _Segment {
    dot startPt;
    dot endPt;
} segment;

segment segArr[SIZE];
int arr[SIZE];
int segArrPt;

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

bool hasIntersection(segment a, segment b)
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

void mergeSegment(int a, int b)
{
    int aParent = getParent(a);
    int bParent = getParent(b);

    if (aParent != bParent)
    {
        arr[bParent] = aParent;
    }
}

int querySetSize(int n)
{
    int ans = 0;
    int root = getParent(n);
    for (int i = 0; i < segArrPt; i++)
    {
        if (getParent(arr[i]) == root)
            ans++;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        segArrPt = 0;
        for (int i = 0; i < SIZE; i++)
        {
            arr[i] = i;
        }

        int cmdNum;
        cin >> cmdNum;

        for (int i = 0; i < cmdNum; i++)
        {
            char cmd;
            cin >> cmd;
            if (cmd == 'P')
            {
                segment a;
                cin >> a.startPt.x >> a.startPt.y >> a.endPt.x >> a.endPt.y;
                segArr[segArrPt] = a;
                for (int j = 0; j < segArrPt; j++)
                {
                    if (hasIntersection(segArr[j], segArr[segArrPt]))
                        mergeSegment(j, segArrPt);
                }
                segArrPt++;
            }
            else if (cmd == 'Q')
            {
                int n;
                cin >> n;
                cout << querySetSize(n - 1) << endl;
            }
        }
        if (t < caseNum - 1)
           cout << endl;
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#define SIZE 99999
using namespace std;

typedef struct _Node {
    long long int x;
    long long int y;
} node;

typedef struct _Line {
    node startPt;
    node endPt;
} line;

line arr[SIZE];

int arrPt = 0;

long long int getCrossedProduct(node a, node b)
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
    long long int xMin = min(a.startPt.x, a.endPt.x);
    long long int xMax = max(a.startPt.x, a.endPt.x);
    long long int yMin = min(a.startPt.y, a.endPt.y);
    long long int yMax = max(a.startPt.y, a.endPt.y);

    return b.x >= xMin && b.x <= xMax && b.y >= yMin && b.y <= yMax;
}

bool hasIntersect(line a, line b)
{
    long long int cp1 = getCrossedProduct(nodeMinus(a.endPt, a.startPt), nodeMinus(b.startPt, a.startPt));
    long long int cp2 = getCrossedProduct(nodeMinus(a.endPt, a.startPt), nodeMinus(b.endPt, a.startPt));
    long long int cp3 = getCrossedProduct(nodeMinus(b.endPt, b.startPt), nodeMinus(a.startPt, b.startPt));
    long long int cp4 = getCrossedProduct(nodeMinus(b.endPt, b.startPt), nodeMinus(a.endPt, b.startPt));

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

bool isNodeEqual(node a, node b)
{
    return a.x == b.x && a.y == b.y;
}

int main()
{
    ios::sync_with_stdio(false);
    int pipeNum;
    while (cin >> pipeNum)
    {
        arrPt = 0;
        for (int i = 0; i < pipeNum; i++)
        {
            int nodeNum;
            cin >> nodeNum;

            node prev;
            cin >> prev.x >> prev.y;
            for (int i = 1; i < nodeNum; i++)
            {
                node cnt;
                cin >> cnt.x >> cnt.y;
                arr[arrPt].startPt = prev;
                arr[arrPt].endPt = cnt;
                prev = cnt;
                arrPt++;
            }
        }

        bool isFound = false;
        for (int i = 0; i < arrPt; i++)
        {
            bool hasEscaped = false;
            for (int j = i + 1; j < arrPt; j++)
            {
                if (!hasEscaped && isNodeEqual(arr[j].startPt, arr[j - 1].endPt))
                {
                    continue;
                }
                else
                {
                    hasEscaped = true;
                    if (hasIntersect(arr[i], arr[j]))
                    {
                        isFound = true;
                        break;
                    }
                }
            }

            if (isFound)
                break;
        }

        cout << ((isFound) ? "Yes" : "No") << endl;
    }
    return 0;
}

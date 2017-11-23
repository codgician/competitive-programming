#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#define SIZE 99999
using namespace std;

typedef struct _Node {
    int x;
    int y;
} node;

node arr[SIZE];

int getCrossedProduct(node a, node b)
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

int main()
{
    ios::sync_with_stdio(false);
    int nodeNum;
    while (cin >> nodeNum)
    {
        if (nodeNum == 0)
            break;

        // The Problem stated that all the nodes were given in counterclockwise order.
        for (int i = 0; i < nodeNum; i++)
        {
            cin >> arr[i].x >> arr[i].y;
        }

        bool isConvex = true;

        // Should always be turning left.
        for (int p1 = 0; p1 < nodeNum; p1++)
        {
            int p2 = (p1 + 1 >= nodeNum) ? p1 + 1 - nodeNum : p1 + 1;
            int p3 = (p1 + 2 >= nodeNum) ? p1 + 2 - nodeNum : p1 + 2;
            if (getCrossedProduct(nodeMinus(arr[p2], arr[p1]), nodeMinus(arr[p3], arr[p2])) < 0)
            {
                isConvex = false;
                break;
            }
        }
        cout << ((isConvex) ? "convex" : "concave") << endl;
    }
    return 0;
}

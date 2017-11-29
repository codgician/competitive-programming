#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#define SIZE 99999
using namespace std;

typedef struct _Dot {
    int x;
    int y;
} dot;

dot arr[SIZE];

int getCrossedProduct(dot a, dot b)
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

int main()
{
    ios::sync_with_stdio(false);
    int dotNum;
    while (cin >> dotNum)
    {
        if (dotNum == 0)
            break;

        // The Problem stated that all the dots were given in counterclockwise order.
        for (int i = 0; i < dotNum; i++)
        {
            cin >> arr[i].x >> arr[i].y;
        }

        bool isConvex = true;

        // Should always be turning left.
        for (int p1 = 0; p1 < dotNum; p1++)
        {
            int p2 = (p1 + 1 >= dotNum) ? p1 + 1 - dotNum : p1 + 1;
            int p3 = (p1 + 2 >= dotNum) ? p1 + 2 - dotNum : p1 + 2;
            if (getCrossedProduct(dotMinus(arr[p2], arr[p1]), dotMinus(arr[p3], arr[p2])) < 0)
            {
                isConvex = false;
                break;
            }
        }
        cout << ((isConvex) ? "convex" : "concave") << endl;
    }
    return 0;
}

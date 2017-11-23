#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>
#define SIZE 1000001
using namespace std;

typedef struct _Node {
    double x;
    double y;
} node;

node arr[SIZE];

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

double getArea(node a, node b, node c)
{
    return getCrossedProduct(nodeMinus(b, a), nodeMinus(c, a));
}

node getGravity(node a, node b, node c)
{
    node ans;
    ans.x = a.x + b.x + c.x;
    ans.y = a.y + b.y + c.y;
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int nodeNum;
        cin >> nodeNum;
        for (int i = 0; i < nodeNum; i++)
        {
            cin >> arr[i].x >> arr[i].y;
        }

        double areaSum = 0;
        node gravitySum;
        gravitySum.x = 0;
        gravitySum.y = 0;
        for (int i = 1; i < nodeNum - 1; i++)
        {
            double area = getArea(arr[0], arr[i], arr[i + 1]);
            node gravity = getGravity(arr[0], arr[i], arr[i + 1]);
            areaSum += area;
            gravitySum.x += gravity.x * area;
            gravitySum.y += gravity.y * area;
        }

        cout << fixed << setprecision(2) << gravitySum.x / (3 * areaSum) << " " << gravitySum.y / (3 * areaSum) << endl;

    }
    return 0;
}

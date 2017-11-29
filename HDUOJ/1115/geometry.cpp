#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>
#define SIZE 1000001
using namespace std;

typedef struct _Dot {
    double x;
    double y;
} dot;

dot arr[SIZE];

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

double getArea(dot a, dot b, dot c)
{
    return getCrossedProduct(dotMinus(b, a), dotMinus(c, a));
}

dot getGravity(dot a, dot b, dot c)
{
    dot ans;
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
        int dotNum;
        cin >> dotNum;
        for (int i = 0; i < dotNum; i++)
        {
            cin >> arr[i].x >> arr[i].y;
        }

        double areaSum = 0;
        dot gravitySum;
        gravitySum.x = 0;
        gravitySum.y = 0;
        for (int i = 1; i < dotNum - 1; i++)
        {
            double area = getArea(arr[0], arr[i], arr[i + 1]);
            dot gravity = getGravity(arr[0], arr[i], arr[i + 1]);
            areaSum += area;
            gravitySum.x += gravity.x * area;
            gravitySum.y += gravity.y * area;
        }

        cout << fixed << setprecision(2) << gravitySum.x / (3 * areaSum) << " " << gravitySum.y / (3 * areaSum) << endl;

    }
    return 0;
}

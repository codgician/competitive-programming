#include <iostream>
#include <cstdio>
#include <cmath>
#include <iomanip>
#define SIZE 10010
using namespace std;

typedef struct _Dot {
    int x;
    int y;
} dot;

dot arr[SIZE];

double getArea(dot p0, dot p1, dot p2)
{
    // return 0.5 *((p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x));
    return 0.5 * (p0.x * p1.y + p2.x * p0.y + p1.x * p2.y - p2.x * p1.y - p0.x * p2.y - p1.x * p0.y);
}

int main()
{
    ios::sync_with_stdio(false);
    int dotNum;
    while (cin >> dotNum)
    {
        if (dotNum == 0)
            break;
        for (int i = 0; i < dotNum; i++)
            cin >> arr[i].x >> arr[i].y;
        double area = 0;
        for (int i = 1; i < dotNum - 1; i++)
            area += getArea(arr[0], arr[i], arr[i + 1]);

        cout << fixed << setprecision(1) << area << endl;
    }
    return 0;
}

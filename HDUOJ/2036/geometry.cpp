#include <iostream>
#include <cstdio>
#include <cmath>
#define SIZE 10010
using namespace std;

typedef struct Node {
    int x;
    int y;
} data;

data arr[SIZE];

double getArea(data p0, data p1, data p2)
{
    // return 0.5 *((p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x));
    return 0.5 * (p0.x * p1.y + p2.x * p0.y + p1.x * p2.y - p2.x * p1.y - p0.x * p2.y - p1.x * p0.y);
}

int main()
{
    ios::sync_with_stdio(false);
    int dataNum;
    while (cin >> dataNum)
    {
        if (dataNum == 0)
            break;
        for (int i = 0; i < dataNum; i++)
            cin >> arr[i].x >> arr[i].y;
        double area = 0;
        for (int i = 1; i < dataNum - 1; i++)
            area += getArea(arr[0], arr[i], arr[i + 1]);

        printf("%.1lf\n", area);
    }
    return 0;
}

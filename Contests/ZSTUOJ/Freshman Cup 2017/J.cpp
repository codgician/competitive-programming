#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define PI acos(-1.0)
using namespace std;

typedef struct _Type {
    double area;
    string str;
} type;

type arr[3];

double getCircleArea(int r)
{
    return PI * r * r;
}

double getTriangleArea(int a)
{
    return sqrt(3) * a * a / 4;
}

double getSquareArea(int a)
{
    return a * a;
}

int main()
{
    ios::sync_with_stdio(false);
    int a, b, c;
    while (cin >> a >> b >> c)
    {
        // Triangle
        arr[0].area = getTriangleArea(a);
        arr[0].str = "triangle";

        // Circle
        arr[1].area = getCircleArea(b);
        arr[1].str = "circle";

        // Square
        arr[2].area = getSquareArea(c);
        arr[2].str = "square";

        double maxArea = arr[0].area;
        int maxAreaIndex = 0;
        for (int i = 1; i < 3; i++)
        {
            if (arr[i].area > maxArea)
            {
                maxArea = arr[i].area;
                maxAreaIndex = i;
            }
        }

        cout << arr[maxAreaIndex].str << endl;
    }
    return 0;
}

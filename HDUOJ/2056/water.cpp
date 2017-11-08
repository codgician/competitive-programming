#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iomanip>
using namespace std;

typedef struct Node {
    double ax, ay;
    double cx, cy;
} rec;

double getIntersectedSize(rec a, rec b)
{
    double leftx = max(a.ax, b.ax);
    double rightx = min(a.cx, b.cx);
    double lefty = max(a.ay, b.ay);
    double righty = min(a.cy, b.cy);
    if (leftx < rightx && lefty < righty)
        return (rightx - leftx) * (righty - lefty);
    else
        return 0;
}

int main()
{
    ios::sync_with_stdio(false);
    rec a, b;
    while (cin >> a.ax >> a.ay >> a.cx >> a.cy >> b.ax >> b.ay >> b.cx >> b.cy)
    {
        if (a.ax > a.cx)
            swap(a.ax, a.cx);
        if (a.ay > a.cy)
            swap(a.ay, a.cy);
        if (b.ax > b.cx)
            swap(b.ax, b.cx);
        if (b.ay > b.cy)
            swap(b.ay, b.cy);
        printf("%.2lf\n", getIntersectedSize(a, b));
    }
    return 0;
}

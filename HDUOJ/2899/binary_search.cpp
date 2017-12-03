#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <cfloat>
using namespace std;

double y;

double f(double x)
{
    return 6 * pow(x, 7) + 8 * pow(x, 6) + 7 * pow(x, 3) + 5 * pow(x, 2) - y * x;
}

double df(double x)
{
    return 42 * pow(x, 6) + 48 * pow(x, 5) + 21 * pow(x, 2) + 10 * x - y;
}

double work (double left, double right)
{
    double mid = (left + right) / 2;

    if (right - left < 1e-10)
        return mid;

    if (df(mid) > 1e-10)
        return work(left, mid);
    else
        return work(mid, right);
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        cin >> y;
        cout << fixed << setprecision(4) << f(work(0, 100)) << endl;
    }
    return 0;
}

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

double r, R, h, v;

double getVolume(double h1)
{
    double R1 = (R - r) * h1 / h + r;
    double ans = h1 * PI * (R1 * R1 + r * r + R1 * r) / 3;
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        cin >> r >> R >> h >> v;
        double left = 0, right = h;
        double mid = (left + right) / 2;

        while (right - left > 1e-8)
        {
            double midV = getVolume(mid);

            if (midV > v)
                right = mid;
            else
                left = mid;
            mid = (left + right) / 2;
        }

        cout << fixed << setprecision(6) << mid << endl;
    }
    return 0;
}

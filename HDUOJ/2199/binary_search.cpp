#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

double y;

double calc(double x)
{
    return 8 * pow(x, 4) + 7 * pow(x, 3) + 2 * pow(x, 2) + 3 * x + 6;
}

double work(double left, double right)
{
    double mid = (left + right) / 2;
    double result = calc(mid);

    if (fabs(result - y) < 1e-5)
        return mid;

    if (result > y)
        return work(left, mid - 1);
    else if (result < y)
        return work(mid + 1, right);
    else
        return mid;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        cin >> y;
        if (calc(0) > y || calc(100) < y)
            cout << "No solution!" << endl;
        else
            cout << fixed << setprecision(4) << work(1, 100) << endl;

    }
    return 0;
}

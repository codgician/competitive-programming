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
        {
            double left = 0, right = 100;
            double mid = (left + right) / 2;
            double result = calc(mid);

            while (fabs(result - y) > 1e-5)
            {
                if (result > y)
                    right = mid;
                else if (result < y)
                    left = mid;
                else
                    break;
                mid = (left + right) / 2;
                result = calc(mid);
            }
            cout << fixed << setprecision(4) << mid << endl;
        }
    }
    return 0;
}

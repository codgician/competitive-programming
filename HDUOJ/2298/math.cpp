#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

const double g = 9.8;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        double x, y, v;
        cin >> x >> y >> v;

        double delta = 4 * (pow(v, 4) * pow(x, 2) - pow(g, 2) * pow(x, 4) - 2 * g * pow(x, 2) * pow(v, 2) * y);
        if (delta < 0)
            cout << -1 << endl;
        else
        {
            double ans1 = atan((2 * x * pow(v, 2) + sqrt(delta)) / (2 * g * pow(x, 2)));
            double ans2 = atan((2 * x * pow(v, 2) - sqrt(delta)) / (2 * g * pow(x, 2)));
            cout << fixed << setprecision(6) << min(ans1, ans2) << endl;
        }
    }
    return 0;
}

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
        {
            cout << "NO SOLUTION." << endl;
        }
        else
        {
            double ans1 = atan((2 * x * pow(v, 2) - sqrt(delta)) / (2 * g * pow(x, 2)));
            double ans2 = atan((2 * x * pow(v, 2) + sqrt(delta)) / (2 * g * pow(x, 2)));
            if (ans1 > ans2)
                swap(ans1, ans2);

            char tmp1[100], tmp2[100];
            sprintf(tmp1, "%.5lf", ans1);
            sprintf(tmp2, "%.5lf", ans2);

            if (!strcmp(tmp1, tmp2))
                cout << tmp1 << endl;
            else
                cout << tmp1 << " " << tmp2 << endl;
        }
    }
    return 0;
}

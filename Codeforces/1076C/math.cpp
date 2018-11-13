#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
#include <cassert>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int d;
        cin >> d;

        int delta = d * d - 4 * d;
        if (delta < 0)
        {
            cout << "N" << endl;
            continue;
        }

        double a1 = (d + sqrt(delta)) / 2, a2 = (d - sqrt(delta)) / 2;
        double b1 = d - a1, b2 = d - a2;

        if (a1 < b1)
            swap(a1, b1);
        if (a2 < b2)
            swap(a2, b2);

        if (a1 >= 0 && b1 >= 0)
        {
            cout << "Y" << endl;
            cout << fixed << setprecision(10) << a1 << " " << b1 << endl;
            continue;
        }

        if (a2 >= 0 && b2 >= 0)
        {
            cout << "Y" << endl;
            cout << fixed << setprecision(10) << a2 << " " << b2 << endl;
            continue;
        }

        cout << "N" << endl;
    }

    return 0;
}
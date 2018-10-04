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
using namespace std;

const long double eps = 1e-10;

long double va, vs, frozeTime;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        cin >> frozeTime >> va >> vs;

        bool ans;
        if (va >= vs)
        {
            // Same speed
            ans = true;
        }
        else if (va * va * 2 >= vs * vs)
        {
            // Meet before post #3
            long double leftPt = 0.0, rightPt = 300.0;
            while (rightPt - leftPt >= eps)
            {
                long double midPt = (leftPt + rightPt) / 2;

                long double ta = (sqrt(300 * 300 + midPt * midPt)) / va;
                long double ts = (300 + midPt) / vs;

                if (ta > ts)
                    leftPt = midPt;
                else
                    rightPt = midPt;
            }

            // Head for post #4
            long double ta = (sqrt(300 * 300 + rightPt * rightPt) + rightPt + 600) / va;
            long double ts = 900 / vs + frozeTime;

            if (ta <= ts)
                ans = true;
            else
                ans = false;
        }
        else if (va * 3 > vs)
        {
            // Meet before post #4
            long double leftPt = 0.0, rightPt = 300.0;
            while (rightPt - leftPt >= eps)
            {
                long double midPt = (leftPt + rightPt) / 2;

                long double ta = (sqrt(300 * 300 + midPt * midPt)) / va;
                long double ts = (900 - midPt) / vs;

                if (ta > ts)
                    rightPt = midPt;
                else
                    leftPt = midPt;
            }

            // Head for post #1
            long double ta = (sqrt(300 * 300 + leftPt * leftPt) + sqrt(300 * 300 + (300 - leftPt) * (300 - leftPt)) + 900) / va;
            long double ts = 1200 / vs + frozeTime;

            if (ta <= ts)
                ans = true;
            else
                ans = false;
        }
        else
        {
            // QAQ
            ans = false;
        }

        cout << "Case #" << t << ": " << (ans ? "Yes" : "No") << endl;
    }

    return 0;
}
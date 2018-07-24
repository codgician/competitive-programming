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

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int hour, min;
        string tz;
        cin >> hour >> min >> tz;

        hour -= 8;
        hour = (hour + 24) % 24;

        int hourDelta = 0, minDelta = 0;

        bool isMin = true;
        int tmp = 1;
        for (int i = (int)tz.size() - 1; i >= 4; i--)
        {
            if (tz[i] == '.')
            {
                isMin = false;
                tmp = 1;
            }
            else if (isMin)
            {
                minDelta += (tz[i] - '0') * tmp;
                tmp *= 10;
            }
            else if (!isMin)
            {
                hourDelta += (tz[i] - '0') * tmp;
                tmp *= 10;
            }
        }

        if (isMin)
        {
            hourDelta = minDelta;
            minDelta = 0;
        }

        minDelta = 6 * minDelta;

        if (tz[3] == '+')
        {
            hour += hourDelta;
            min += minDelta;
        }
        else
        {
            hour -= hourDelta;
            min -= minDelta;
        }

        if (min >= 60)
        {
            hour += min / 60;
            min %= 60;
        }
        if (hour >= 24)
        {
            hour %= 24;
        }

        if (min < 0)
        {
            hour -= (-min) / 60 + 1;
            min = 60 - (-min) % 60;
        }
        if (hour < 0)
        {
            hour = (hour + 24) % 24;
        }

        cout << setfill('0') << setw(2) << hour << ":" << setfill('0') << setw(2) << min << endl;
    }
    return 0;
}
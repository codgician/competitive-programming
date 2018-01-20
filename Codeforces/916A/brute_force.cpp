#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int snoozeInt;
    cin >> snoozeInt;
    int hour, minute;
    cin >> hour >> minute;

    int ans = 0;
    while (true)
    {
        if (minute % 10 == 7 || hour % 10 == 7)
        {
            break;
        }
        minute -= snoozeInt;
        ans++;
        if (minute < 0)
        {
            minute += 60;
            hour--;
        }
        if (hour < 0)
        {
            hour += 24;
        }
    }
    cout << ans << endl;
    return 0;
}

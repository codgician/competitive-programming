#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int dayNum, progTime;
    while (cin >> dayNum >> progTime)
    {
        bool isFinished = false;
        int ans = 0;
        for (int i = 0; i < dayNum; i++)
        {
            int workTime;
            cin >> workTime;
            progTime -= (86400 - workTime);
            if (!isFinished && progTime <= 0)
            {
                ans = i + 1;
                isFinished = true;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

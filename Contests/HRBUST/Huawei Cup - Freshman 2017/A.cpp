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
    int doctorNum;
    while (cin >> doctorNum)
    {
        int cntDay = 0;
        for (int i = 0; i < doctorNum; i++)
        {
            int startDay, interval;
            cin >> startDay >> interval;
            if (cntDay < startDay)
            {
                cntDay = startDay;
            }
            else
            {
                for (int i = 1; ; i++)
                {
                    if (startDay + interval * i > cntDay)
                    {
                        cntDay = startDay + interval * i;
                        break;
                    }
                }
            }
        }
        cout << cntDay << endl;
    }
    return 0;
}

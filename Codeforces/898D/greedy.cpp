#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 9999999
using namespace std;

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    memset(arr, 0, sizeof(arr));
    int alarmNum, consMin, minNum, maxTriggerTime = -1;
    cin >> alarmNum >> consMin >> minNum;
    for (int i = 0; i < alarmNum; i++)
    {
        int triggerTime;
        cin >> triggerTime;
        arr[triggerTime]++;
        maxTriggerTime = max(maxTriggerTime, triggerTime);
    }

    int ans = 0, cntAns = 0;
    for (int i = 0; i <= maxTriggerTime; i++)
    {
        cntAns += arr[i];
        if (i > consMin)
            cntAns -= arr[i - consMin];
        if (cntAns >= minNum)
        {
            arr[i] -= (cntAns - minNum + 1);
            ans += (cntAns - minNum + 1);
            cntAns = minNum - 1;
        }
    }

    cout << ans << endl;
    return 0;
}

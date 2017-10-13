#include <iostream>
#include <cstdio>
#include <algorithm>
#define SIZE 101
using namespace std;

typedef struct Node {
    int startTime;
    int endTime;
} tv;

tv arr[SIZE];

bool cmpRule(tv a, tv b)
{
    return a.endTime < b.endTime;
}

int main()
{
    ios::sync_with_stdio(false);
    int tvNum;
    while (cin >> tvNum)
    {
        if (tvNum == 0)
            break;
        for (int i = 0; i < tvNum; i++)
            cin >> arr[i].startTime >> arr[i].endTime;

        sort(arr, arr + tvNum, cmpRule);

        int prevEndTime = 0, ans = 0;
        for (int i = 0; i < tvNum; i++)
        {
            if (arr[i].startTime >= prevEndTime)
            {
                prevEndTime = arr[i].endTime;
                ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

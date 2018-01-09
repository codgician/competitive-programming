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
#define SIZE 200001
using namespace std;

typedef struct _Problem
{
    int cond;
    int cost;
    int origId;
} problem;

problem arr[SIZE];
int probNum, examLen;

bool cmpRule(problem a, problem b)
{
    return a.cost < b.cost;
}

bool check(int k)
{
    int cntTime = 0, selectedNum = 0;
    for (int i = 0; i < probNum; i++)
    {
        if (arr[i].cond >= k)
        {
            cntTime += arr[i].cost;
            if (cntTime > examLen)
            {
                break;
            }
            selectedNum++;
        }
    }
    if (selectedNum < k)
        return false;
    else
        return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> probNum >> examLen;
    for (int i = 0; i < probNum; i++)
    {
        cin >> arr[i].cond >> arr[i].cost;
        arr[i].origId = i + 1;
    }

    sort(arr + 0, arr + probNum, cmpRule);

    int left = 0, right = probNum;
    while (left <= right)
    {
        int mid = (left + right) >> 1;
        if (check(mid))
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    int ans = 0;
    if (left > 0)
        ans = left - 1;
    cout << ans << endl;
    cout << ans << endl;

    int cntNum = 0;
    if (ans > 0)
    {
        for (int i = 0; i < probNum; i++)
        {
            if (arr[i].cond >= ans)
            {
                cout << arr[i].origId;
                cntNum++;
                if (cntNum < ans)
                {
                    cout << " ";
                }
                else
                {
                    cout << endl;
                    break;
                }
            }
        }
    }
    return 0;
}

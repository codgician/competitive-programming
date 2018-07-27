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

#define SIZE 110

int arr[SIZE];

bool check(int dayNum, int peopleNum)
{
    if (dayNum == 0)
        return true;
    int cntPeopleNum = 0;
    for (int i = 0; i < SIZE; i++)
    {
        cntPeopleNum += arr[i] / dayNum;
        if (cntPeopleNum >= peopleNum)
            return true; 
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    memset(arr, 0, sizeof(arr));
    int expNum, foodNum;
    cin >> expNum >> foodNum;
    for (int i = 0; i < foodNum; i++)
    {
        int cnt;
        cin >> cnt;
        arr[cnt]++;
    }

    sort(arr + 0, arr + SIZE);

    int leftPt = 0, rightPt = 10000;
    int ans = 0;
    while (leftPt <= rightPt)
    {
        int midPt = (leftPt + rightPt) >> 1;
        if (check(midPt, expNum))
        {
            leftPt = midPt + 1;
            ans = midPt;
        }
        else
        {
            rightPt = midPt - 1;
        }
    }

    cout << ans << endl;
    return 0;
}
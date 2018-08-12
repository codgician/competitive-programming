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

#define SIZE 300010

int arr[SIZE], num;

bool check(int cnt)
{
    long long int plusOne = 0, minusTwo = 0;
    for (int i = 0; i < num; i++)
    {
        if (arr[i] >= cnt)
            minusTwo += (arr[i] - cnt) >> 1;
        else
            plusOne += (cnt - arr[i]);
    }

    if (plusOne > minusTwo)
        return false;
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        cin >> num;

        int leftPt = INT_MAX, rightPt = -1;
        for (int i = 0; i < num; i++)
        {
            cin >> arr[i];
            leftPt = min(leftPt, arr[i]);
            rightPt = max(rightPt, arr[i]);
        }

        int ans = -1;
        while (leftPt <= rightPt)
        {
            int midPt = (leftPt + rightPt) >> 1;
            if (check(midPt))
            {
                ans = midPt;
                leftPt = midPt + 1;
            }
            else
            {
                rightPt = midPt - 1;
            }
        }

        cout << ans << endl;
    }
    return 0;
}
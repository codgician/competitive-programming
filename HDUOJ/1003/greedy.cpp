// This is actually an optimized version of dp.cpp
// We can easily figure out its state transition equation:
// dp[i] = max(dp[i - 1] + arr[i], arr[i])
// It means that the only thing that matters is whether dp[i - 1] is positive or not!
// So if the previous sub-sequence has a sum smaller than 0, why need it?
// The sum must be bigger if we abandon them and start a new sub-sequence!

#include <iostream>
#include <cstdio>
#include <climits>
#define MAXN 100001
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int i = 1; i <= caseNum; i++)
    {
        int eleNum, maxSum, sum, tStartPt = 0, startPt = 0, endPt = 0;
        cin >> eleNum;
        cin >> sum;
        maxSum = sum;
        for (int t = 1; t < eleNum; t++)
        {
            int tmp;
            cin >> tmp;

            // if dp[i - 1] < 0
            if (sum < 0)
            {
                tStartPt = t;
                sum = tmp;
            }
            else
                sum += tmp;

            if (sum > maxSum)
            {
                maxSum = sum;
                endPt = t;
                startPt = tStartPt;
            }
        }

        cout << "Case " << i << ":" << endl;
        cout << maxSum << " " << startPt + 1 << " " << endPt + 1 << endl;
        if (i < caseNum)
            cout << endl;
    }
    return 0;
}

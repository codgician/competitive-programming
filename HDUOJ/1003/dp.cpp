#include <iostream>
#include <cstdio>
#include <cmath>
#define SIZE 100001
using namespace std;

int arr[SIZE], dp[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        int eleNum;
        cin >> eleNum;
        for (int i = 0; i < eleNum; i++)
            cin >> arr[i];

        dp[0] = arr[0];
        int maxSum = dp[0], startPt = 0, tStartPt = 0, endPt = 0;
        for (int i = 1; i < eleNum; i++)
        {
            // dp[i] = max(dp[i - 1] + arr[i], arr[i]);
            if (dp[i - 1] < 0)
            {
                dp[i] = arr[i];
                // Update temporary startPt.
                tStartPt = i;
            }
            else
                dp[i] = dp[i - 1] + arr[i];

            if (dp[i] > maxSum)
            {
                maxSum = dp[i];
                endPt = i;
                startPt = tStartPt;
            }
        }

        cout << "Case " << t << ":" << endl;
        cout << maxSum << " " << startPt + 1 << " " << endPt + 1 << endl;
        if (t < caseNum)
            cout << endl;
    }

    return 0;
}

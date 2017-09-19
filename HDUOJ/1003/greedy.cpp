// Greedy algorithm.
// f stands for final. t stands for temporary.

#include <iostream>
#define MAXN 1000010
using namespace std;

int arr[MAXN];

int main()
{
    ios::sync_with_stdio(false);

    int caseCount;
    cin >> caseCount;
    for (int i = 1; i <= caseCount; i++)
    {
        int n;
        int sum = 0, maxSum = -100000, fStart, fEnd, tStart = 0;
        cin >> n;
        for (int tEnd = 0; tEnd < n; tEnd++)
        {
            cin >> arr[tEnd];
            sum += arr[tEnd];
            if (sum > maxSum)
            {
                maxSum = sum;
                fStart = tStart + 1;
                fEnd = tEnd + 1;
            }

            // If the sum is even smaller than zero, move on to the next.
            // The sub-sequence would be bigger without them.
            if (sum < 0)
            {
                sum = 0;
                tStart = tEnd + 1;
            }
        }

        cout << "Case " << i << ":" << endl;
        cout << maxSum << " " << fStart << " " << fEnd << endl;
        if (i < caseCount)
            cout << endl;
    }
    return 0;
}

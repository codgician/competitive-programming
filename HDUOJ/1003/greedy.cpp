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

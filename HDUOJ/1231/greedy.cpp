#include <iostream>
#include <cstdio>
#include <climits>
#define MAXN 10001
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int eleNum;
    while (cin >> eleNum)
    {
        if (eleNum == 0)
            break;
        int maxSum, sum, tmp;
        cin >> sum;
        maxSum = sum;
        int tStartEle = sum, startEle = sum, origStartEle = sum, endEle = sum;
        for (int t = 1; t < eleNum; t++)
        {
            cin >> tmp;

            // if dp[i - 1] < 0
            if (sum < 0)
            {
                tStartEle = tmp;
                sum = tmp;
            }
            else
                sum += tmp;

            if (sum > maxSum)
            {
                maxSum = sum;
                endEle = tmp;
                startEle = tStartEle;
            }
        }

        if (maxSum < 0)
            cout << 0 << " " << origStartEle << " " << tmp << endl;
        else
            cout << maxSum << " " << startEle << " " << endEle << endl;
    }
    return 0;
}

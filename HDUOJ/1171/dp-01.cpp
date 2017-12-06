#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 5001
using namespace std;

int arr[SIZE], dp[SIZE * SIZE / 2];

int main()
{
    ios::sync_with_stdio(false);
    int facType;
    while (cin >> facType)
    {
        if (facType < 0)
            break;

        int valSum = 0, arrPt = 0;
        for (int i = 0; i < facType; i++)
        {
            int value, num;
            cin >> value >> num;
            for (int i = 0; i < num; i++)
            {
                arr[arrPt + i] = value;
                valSum += value;
            }
            arrPt += num;
        }

        int bagSize = valSum / 2;
        for (int i = 0; i <= bagSize; i++)
            dp[i] = 0;
        for (int i = 0; i < arrPt; i++)
        {
            for (int j = bagSize; j >= arr[i]; j--)
            {
                dp[j] = max(dp[j], dp[j - arr[i]] + arr[i]);
            }
        }

        cout << valSum - dp[bagSize] << " " << dp[bagSize] << endl;
    }
    return 0;
}

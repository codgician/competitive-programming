// NEVER EVER USE CIN AND SCANF TOGETHER!
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#define BILL_SIZE 35
#define DP_SIZE 5000050
using namespace std;

int arr[BILL_SIZE], dp[DP_SIZE];

int main()
{
    ios::sync_with_stdio(false);
    double tmpMaxMoney;
    int billNum, maxMoney;
    while (scanf("%lf%d", &tmpMaxMoney, &billNum) != EOF)
    {
        if (billNum == 0)
            break;
        maxMoney = (int)(tmpMaxMoney * 100);
        int cnt = 0;
        for (int i = 0; i < billNum; i++)
        {
            bool isValid = true;
            int sumA = 0, sumB = 0, sumC = 0, itemNum;
            scanf("%d", &itemNum);
            for (int j = 0; j < itemNum; j++)
            {
                char itemType;
                double itemValue;
                scanf(" %c:%lf", &itemType, &itemValue);
                if (isValid)
                {
                    if (itemType == 'A')
                        sumA += (int)(itemValue * 100);
                    else if (itemType == 'B')
                        sumB += (int)(itemValue * 100);
                    else if (itemType == 'C')
                        sumC += (int)(itemValue * 100);
                    else
                        isValid = false;
                }
            }
            if (!isValid || sumA > 60000 || sumB > 60000 || sumC > 60000 || sumA + sumB + sumC > 100000)
                continue;
            else
            {
                arr[cnt] = sumA + sumB + sumC;
                cnt++;
            }
        }

        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < cnt; i++)
        {
            for (int j = maxMoney; j >= arr[i]; j--)
            {
                dp[j] = max(dp[j], dp[j - arr[i]] + arr[i]);
            }
        }

        printf("%.2lf\n", (double)(dp[maxMoney] / 100.00));
    }
    return 0;
}

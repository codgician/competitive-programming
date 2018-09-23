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
#include <cassert>
using namespace std;

#define BAG_SIZE 10010
#define ITEM_SIZE 410
#define TYPE_SIZE 21

long long int arr[ITEM_SIZE];
long long int dp[BAG_SIZE];

int twoPow[TYPE_SIZE];

const long long int mod = 1e9 + 7;

void initTwoPow()
{
    twoPow[0] = 1;
    for (int i = 1; i < TYPE_SIZE; i++)
    {
        twoPow[i] = twoPow[i - 1] << 1;
    }
}

int main()
{
    initTwoPow();
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        int itemNum, qNum;
        scanf("%d%d", &itemNum, &qNum);

        int arrPt = 0;
        for (int i = 0; i < itemNum; i++)
        {
            int weight, num;
            scanf("%d%d", &weight, &num);

            for (int j = 0; j < num; j++)
            {
                arr[arrPt++] = weight * twoPow[j];
            }
        }

        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for (int i = 0; i < arrPt; i++)
        {
            for (int j = BAG_SIZE - 1; j >= arr[i]; j--)
            {
                dp[j] += dp[j - arr[i]];
                if (dp[j] >= mod)
                    dp[j] %= mod;
            }
        }

        while (qNum--)
        {
            int bagSize;
            scanf("%d", &bagSize);
            printf("%lld\n", dp[bagSize]);
        }
    }

    return 0;
}
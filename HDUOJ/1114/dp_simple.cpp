#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define INF 0x7FFFFFF
#define PIG_WEIGHT 10001
#define SIZE 501
using namespace std;

typedef struct Node {
    int value;
    int weight;
} coin;

coin arr[SIZE];

int dp[PIG_WEIGHT];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int emptyPigWeight, pigWeight;
        cin >> emptyPigWeight >> pigWeight;
        pigWeight -= emptyPigWeight;

        int coinNum;
        cin >> coinNum;
        for (int i = 0; i < coinNum; i++)
        {
            cin >> arr[i].value >> arr[i].weight;

            // Abandon if weight larger than piggy.
            if (arr[i].weight > pigWeight)
            {
                i--;
                coinNum--;
                continue;
            }
        }

        dp[0] = 0;
        for (int j = 1; j <= pigWeight; j++)
            dp[j] = INF;

        for (int i = 0; i < coinNum; i++)
        {
            for (int j = pigWeight; j >= arr[i].weight; j--)
            {
                for (int k = 0; j - k * arr[i].weight >= 0; k++)
                {
                    dp[j] = min(dp[j], dp[j - k * arr[i].weight] + k * arr[i].value);
                }
            }
        }

        if (dp[pigWeight] == INF)
        {
            cout << "This is impossible." << endl;
        }
        else
        {
            cout << "The minimum amount of money in the piggy-bank is " << dp[pigWeight] << "." << endl;
        }
    }
    return 0;
}
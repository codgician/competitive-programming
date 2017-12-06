#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 101
using namespace std;

typedef struct _Rice {
    int price;
    int weight;
    int num;
} rice;

rice arr[SIZE];
int dp[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int money, riceType;
        cin >> money >> riceType;
        for (int i = 0; i < riceType; i++)
        {
            cin >> arr[i].price >> arr[i].weight >> arr[i].num;
        }

        for (int i = 0; i <= money; i++)
            dp[i] = 0;
        for (int i = 0; i < riceType; i++)
        {
            for (int j = money; j >= arr[i].price; j--)
            {
                for (int k = 1; j - k * arr[i].price >= 0 && k <= arr[i].num; k++)
                {
                    dp[j] = max(dp[j], dp[j - k * arr[i].price] + k * arr[i].weight);
                }
            }
        }

        cout << dp[money] << endl;
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 2001
using namespace std;

typedef struct _Rice {
    int price;
    int weight;
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
        int arrPt = 0;
        for (int i = 0; i < riceType; i++)
        {
            cin >> arr[arrPt].price >> arr[arrPt].weight;
            int num;
            cin >> num;
            for (int j = 1; j < num; j++)
            {
                arr[arrPt + j] = arr[arrPt];
            }
            arrPt += num;
        }

        for (int i = 0; i <= money; i++)
            dp[i] = 0;

        for (int i = 0; i < arrPt; i++)
        {
            for (int j = money; j >= arr[i].price; j--)
            {
                dp[j] = max(dp[j], dp[j - arr[i].price] + arr[i].weight);
            }
        }

        cout << dp[money] << endl;
    }
    return 0;
}

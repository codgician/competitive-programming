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
            int price, weight;
            cin >> price >> weight;
            arr[arrPt].price = price;
            arr[arrPt].weight = weight;
            arrPt++;

            int num;
            cin >> num;

            int tmp = 1, sum = 1;
            while (num - sum > (tmp << 1))
            {
                tmp <<= 1;
                arr[arrPt].price = price * tmp;
                arr[arrPt].weight = weight * tmp;
                arrPt++;
                sum += tmp;
            }
            arr[arrPt].price = price * (num - sum);
            arr[arrPt].weight = weight * (num - sum);
            arrPt++;
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

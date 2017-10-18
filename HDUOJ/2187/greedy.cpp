#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define SIZE 1001
using namespace std;

typedef struct Node {
    int price;
    int weight;
} rice;

rice arr[SIZE];

bool cmpRule(rice a, rice b)
{
    return a.price < b.price;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int money, riceType;
        double ans = 0;
        cin >> money >> riceType;
        for (int i = 0; i < riceType; i++)
        {
            cin >> arr[i].price >> arr[i].weight;
        }
        sort(arr, arr + riceType, cmpRule);

        for (int i = 0; i < riceType; i++)
        {
            if (money >= arr[i].price * arr[i].weight)
            {
                ans += arr[i].weight;
                money -= arr[i].price * arr[i].weight;
            }
            else
            {
                if (arr[i].price == 0)
                {
                    ans += arr[i].weight;
                }
                else
                {
                    ans += (double)money / arr[i].price;
                }
                money = 0;
            }
        }
        printf("%.2lf\n", ans);
    }
    return 0;
}

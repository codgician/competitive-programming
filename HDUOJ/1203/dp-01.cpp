#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 10001
using namespace std;

typedef struct _School {
    int fee;
    double notPos;
} school;

school arr[SIZE];
double dp[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int money, schoolNum;
    while (cin >> money >> schoolNum)
    {
        if (money == 0 && schoolNum == 0)
            break;

        for (int i = 0; i < schoolNum; i++)
        {
            cin >> arr[i].fee;
            double pos;
            cin >> pos;
            arr[i].notPos = 1 - pos;
        }

        for (int i = 0; i <= money; i++)
            dp[i] = 1;
        for (int i = 0; i < schoolNum; i++)
        {
            for (int j = money; j >= arr[i].fee; j--)
            {
                dp[j] = min(dp[j], dp[j - arr[i].fee] * arr[i].notPos);
            }
        }

        cout << fixed << setprecision(1) << (1 - dp[money]) * 100 << "%" << endl;
    }
    return 0;
}


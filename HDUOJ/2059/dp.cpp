#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#define INF 9999999
#define SIZE 101
using namespace std;

int plant[SIZE];
double dp[SIZE];

int length;
int plantNum, batteryLife, chargeTime, rabbitSpeed, bikeSpeed, paddleSpeed;

double getMin(double a, double b)
{
    return a < b ? a : b;
}

double getTime(int startPt, int endPt)
{
    double ans;
    if (plant[endPt] - plant[startPt] <= batteryLife)
    {
        ans = (double)(plant[endPt] - plant[startPt]) / bikeSpeed;
    }
    else
    {
        ans = (double)batteryLife / bikeSpeed + (double)(plant[endPt] - plant[startPt] - batteryLife) / paddleSpeed;
    }
    if (startPt != 0)
        ans += chargeTime;
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> length)
    {
        cin >> plantNum >> batteryLife >> chargeTime >> rabbitSpeed >> bikeSpeed >> paddleSpeed;

        plant[0] = 0;
        for (int i = 1; i <= plantNum; i++)
        {
            cin >> plant[i];
        }
        plant[plantNum + 1] = length + 1;

        double rabbitTime = (double)length / rabbitSpeed;

        for (int i = 1; i <= plantNum + 1; i++)
        {
            dp[i] = INF;
        }
        dp[0] = 0;

        for (int i = 1; i <= plantNum + 1; i++)
        {
            for (int j = 0; j < i; j++)
            {
                dp[i] = getMin(dp[i], dp[j] + getTime(j, i));
            }
        }

        if (rabbitTime < dp[plantNum + 1])
            cout << "Good job,rabbit!";
        else
            cout << "What a pity rabbit!";
        cout << endl;
    }
    return 0;
}

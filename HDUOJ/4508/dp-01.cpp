#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define FOOD_SIZE 101
#define CAL_SIZE 100001
using namespace std;

typedef struct _Food {
    int happiness;
    int calorie;
} food;

food arr[FOOD_SIZE];
int dp[CAL_SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int foodType;
    while (cin >> foodType)
    {
        for (int i = 0; i < foodType; i++)
        {
            cin >> arr[i].happiness >> arr[i].calorie;
        }

        int maxCalorie;
        cin >> maxCalorie;

        for (int i = 0; i <= maxCalorie; i++)
            dp[i] = 0;
        for (int i = 0; i < foodType; i++)
        {
            for (int j = arr[i].calorie; j <= maxCalorie; j++)
            {
                dp[j] = max(dp[j], dp[j - arr[i].calorie] + arr[i].happiness);
            }
        }

        cout << dp[maxCalorie] << endl;
    }
    return 0;
}


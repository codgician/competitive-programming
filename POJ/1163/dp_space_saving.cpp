#include <iostream>
#include <cstdio>
#include <cmath>
#define SIZE 101
using namespace std;

int arr[SIZE][SIZE], dp[2][SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int height;
    cin >> height;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            int tmp;
            cin >> tmp;
            arr[i][j] = tmp;
            if (i == height - 1)
                dp[1][j] = tmp;
        }
    }

    for (int i = height - 2; i >= 0; i--)
    {
        for (int j = 0; j <= i; j++)
        {
            dp[0][j] = max(dp[1][j], dp[1][j + 1]) + arr[i][j];
        }
        for (int j = 0; j <= i; j++)
        {
            dp[1][j] = dp[0][j];
        }
    }

    cout << dp[0][0] << endl;

    return 0;
}

#include <iostream>
#include <cstdio>
#include <cmath>
#define SIZE 101
using namespace std;

int arr[SIZE][SIZE], dp[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int height;
    cin >> height;

    for (int i = 0; i < height; i++)
        for (int j = 0; j <= i; j++)
            cin >> arr[i][j];

	for (int j = 0; j < height; j++)
		dp[j] = arr[height - 1][j];

    for (int i = height - 2; i >= 0; i--)
        for (int j = 0; j <= i; j++)
            dp[j] = max(dp[j], dp[j + 1]) + arr[i][j];

    cout << dp[0] << endl;
    return 0;
}

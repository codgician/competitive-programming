#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iomanip>
#define SIZE 1001
using namespace std;

int arr[SIZE], dp[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int nodeNum;
    while (cin >> nodeNum)
    {
        if (nodeNum == 0)
            break;
        for (int i = 0; i < nodeNum; i++)
        {
            cin >> arr[i];
            dp[i] = arr[i];
        }

        int ans = dp[0];
        for (int i = 0; i < nodeNum; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (arr[i] > arr[j])
                    dp[i] = max(dp[i], dp[j] + arr[i]);
            }
            if (dp[i] > ans)
                ans = dp[i];
        }
        cout << ans << endl;
    }
    return 0;
}

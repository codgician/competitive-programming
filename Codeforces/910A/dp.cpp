#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 201
#define INF 999999
using namespace std;

int dp[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int home, maxDistance;
    cin >> home >> maxDistance;
    string path;
    cin >> path;

    dp[0] = 0;
    for (int i = 1; i < SIZE; i++)
        dp[i] = INF;

    for (int i = 0; i < path.length(); i++)
    {
        for (int j = 1; j <= maxDistance && j <= i; j++)
        {
            if (path[i - j] == '1')
                dp[i] = min(dp[i], dp[i - j] + 1);
        }
    }

    if (dp[home - 1] == INF)
        cout << -1 << endl;
    else
        cout << dp[home - 1] << endl;
    return 0;
}

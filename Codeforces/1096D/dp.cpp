#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
#include <cassert>
using namespace std;

#define SIZE 100010

long long int arr[SIZE], dp[5][SIZE];
char ch[4] = {'h', 'a', 'r', 'd'};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int len;
    cin >> len;
    string str;
    cin >> str;
    for (int i = 0; i < len; i++)
        cin >> arr[i];

    dp[0][0] = 0;
    for (int i = 1; i < 4; i++)
        dp[i][0] = LLONG_MAX;

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < 5; j++)
            dp[j][i + 1] = dp[j][i];

        for (int k = 0; k < 4; k++)
        {
            if (str[i] == ch[k])
            {
                if (k < 3)
                    dp[k + 1][i + 1] = min(dp[k + 1][i + 1], dp[k][i + 1]);
                if (dp[k][i + 1] != LLONG_MAX)
                    dp[k][i + 1] += arr[i];
            }
        }
    }

    long long int ans = LLONG_MAX;
    for (int i = 0; i < 4; i++)
        ans = min(ans, dp[i][len]);
    cout << ans << endl;

    return 0;
}
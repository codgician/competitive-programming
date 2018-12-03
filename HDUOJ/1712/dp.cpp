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

#define SIZE 105

int arr[SIZE][SIZE], dp[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int courseNum, dayNum;
    while (cin >> courseNum >> dayNum)
    {
        if (courseNum == 0 && dayNum == 0)
            break;

        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < courseNum; i++)
        {
            for (int j = 0; j < dayNum; j++)
            {
                cin >> arr[i][j];
            }
        }

        for (int i = 0; i < courseNum; i++)
        {
            for (int j = dayNum; j > 0; j--)
            {
                for (int k = 0; k < j; k++)
                {
                    dp[j] = max(dp[j], dp[j - k - 1] + arr[i][k]);
                }
            }
        }

        cout << dp[dayNum] << endl;
    }

    return 0;
}
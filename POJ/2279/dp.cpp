#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
#define SIZE 5
#define DP_SIZE 28629200
using namespace std;

unsigned int arr[SIZE];
map<unsigned int, unsigned int> dp;

unsigned int getId(int i, int j, int k, int m, int n)
{
    unsigned int ans = i + j * 31 + k * 31 * 31 + m * 31 * 31 * 31 + n * 31 * 31 * 31 * 31;
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int rowNum;
    while (cin >> rowNum)
    {
        if (rowNum == 0)
            break;

        memset(arr, 0, sizeof(arr));
        for (int i = 0; i < rowNum; i++)
        {
            cin >> arr[i];
        }

        dp.clear();
        dp[0] = 1;

        for (unsigned int i = 0; i <= arr[0]; i++)
        {
            for (unsigned int j = 0; j <= arr[1]; j++)
            {
                for (unsigned int k = 0; k <= arr[2]; k++)
                {
                    for (unsigned int m = 0; m <= arr[3]; m++)
                    {
                        for (unsigned int n = 0; n <= arr[4]; n++)
                        {
                            unsigned int cntId = getId(i, j, k, m, n);

                            if (i < arr[0])
                                dp[getId(i + 1, j, k, m, n)] += dp[cntId];
                            if (j < arr[1] && i > j)
                                dp[getId(i, j + 1, k, m, n)] += dp[cntId];
                            if (k < arr[2] && j > k)
                                dp[getId(i, j, k + 1, m, n)] += dp[cntId];
                            if (m < arr[3] && k > m)
                                dp[getId(i, j, k, m + 1, n)] += dp[cntId];
                            if (n < arr[4] && m > n)
                                dp[getId(i, j, k, m, n + 1)] += dp[cntId];
                        }
                    }
                }
            }
        }

        cout << dp[getId(arr[0], arr[1], arr[2], arr[3], arr[4])] << endl;
    }
    return 0;
}
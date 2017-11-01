#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <iomanip>
#define SIZE 10010
using namespace std;

int dp[SIZE][SIZE];

int main()
{
    ios::sync_with_stdio(false);
    string a, b;
    while (cin >> a >> b)
    {
        for (int i = 0; i <= a.length(); i++)
            dp[i][0] = 0;
        for (int j = 0; j <= b.length(); j++)
            dp[0][j] = 0;

        for (int i = 1; i <= a.length(); i++)
        {
            for (int j = 1; j <= b.length(); j++)
            {
                if (a[i - 1] == b[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        cout << dp[a.length()][b.length()] << endl;
    }
    return 0;
}

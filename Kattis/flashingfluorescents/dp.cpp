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
using namespace std;

#define STATE_SIZE 65550
#define STEP_SIZE 40

bool dp[STEP_SIZE][STATE_SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string str;
    while (cin >> str)
    {
        memset(dp, false, sizeof(dp));
        int startState = 0, len = str.size();
        for (int i = 0; i < len; i++)
        {
            if (str[i] == '0')
                startState ^= (1 << i);
        }

        dp[0][startState] = true;
        int step = 0;
        while (!dp[step][0])
        {
            for (int i = 0; i < (1 << len); i++)
                dp[step + 1][i] = dp[step][i];

            for (int i = 0; i < len; i++)   // startPt of triggering
            {
                int trans = 0;
                for (int j = 0; j <= step && i + j < len; j++)  // len (time elapsed)
                {
                    trans |= (1 << (i + j));
                }
                for (int j = 0; j < (1 << len); j++)
                {
                    if (dp[step][j])
                        dp[step + 1][j ^ trans] = 1;
                }
            }
            step++;
        }

        cout << step << endl;
    }
    return 0;
}
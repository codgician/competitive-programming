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
#define SIZE 2510
using namespace std;

bool dp[SIZE][SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        string fst, snd;
        cin >> fst >> snd;

        int fstLen = fst.length();
        int sndLen = snd.length();

        memset(dp, false, sizeof(dp));
        dp[0][0] = true;
        for (int i = 1; i <= sndLen; i++)
        {
            if (i >= 2 && snd[i - 1] == '*')
            {
                dp[i][0] = dp[i - 2][0];
            }

            for (int j = 1; j <= fstLen; j++)
            {
                if (snd[i - 1] == '.' || fst[j - 1] == snd[i - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else if (snd[i - 1] == '*')
                {
                    dp[i][j] = dp[i - 2][j] | dp[i - 1][j];
                    if ((dp[i - 1][j - 1] || dp[i][j - 1]) && fst[j - 2] == fst[j - 1])
                    {
                        dp[i][j] = true;
                    }
                }
            }
        }

        if (dp[sndLen][fstLen])
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
    return 0;
}
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
#include <set>
#include <map>
#define SIZE 200010
using namespace std;

int nextArr[SIZE];
int dp[SIZE];

const int mod = 10007;

void initNext(string &str, int len)
{
    nextArr[0] = 0;
    for (int i = 1, matchNum = 0; i < len; i++)
    {
        while (matchNum > 0 && str[i] != str[matchNum])
            matchNum = nextArr[matchNum - 1];
        if (str[i] == str[matchNum])
            matchNum++;
        nextArr[i] = matchNum;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int len;
        string str;
        cin >> len >> str;
        initNext(str, len);

        int ans = 0;
        dp[0] = 0;
        for (int i = 1; i <= len; i++)
            dp[i] = 1;
        for (int i = 1; i <= len; i++)
        {
            dp[i] = dp[nextArr[i - 1]] + 1;
            if (dp[i] >= mod)
                dp[i] %= mod;
            ans += dp[i];
            if (ans >= mod)
                ans %= mod;
        }

        cout << ans << endl;
    }
    return 0;
}

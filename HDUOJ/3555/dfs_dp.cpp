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
#define SIZE 25
using namespace std;

long long int dp[SIZE][2];
int cntArr[SIZE];

long long int dfs(int cntLen, bool hasFour, bool hasLimit)
{
    if (cntLen == 0)
        return 1;
    if (!hasLimit && dp[cntLen][hasFour])
        return dp[cntLen][hasFour];

    long long int ans = 0;
    int lim = (hasLimit ? cntArr[cntLen - 1] : 9);
    for (int i = 0; i <= lim; i++)
    {
        if (hasFour && i == 9)
            continue;

        ans += dfs(cntLen - 1, i == 4, hasLimit && i == lim);
    }

    if (!hasLimit)
        dp[cntLen][hasFour] = ans;
    return ans; 
}

inline long long int work(long long int cnt)
{
    int len = 0;
    while (cnt)
    {
        cntArr[len++] = cnt % 10;
        cnt /= 10;
    }
    cntArr[len] = 0;
    return dfs(len, false, true);
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        long long int num;
        cin >> num;
        cout << num + 1 - work(num) << endl;
    }
    return 0;
}
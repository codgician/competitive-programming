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
using namespace std;

#define SIZE 510

int fstArr[SIZE], sndArr[SIZE];
int dp[SIZE], path[SIZE];

void print(int cntPt)
{
    if (cntPt == 0)
        return;
    print(path[cntPt]);
    cout << sndArr[cntPt] << " ";
}

int main()
{
    ios::sync_with_stdio(false);
    int fstLen, sndLen;
    cin >> fstLen;
    for (int i = 1; i <= fstLen; i++)
    {
        cin >> fstArr[i];
    }
    cin >> sndLen;
    for (int i = 1; i <= sndLen; i++)
    {
        cin >> sndArr[i];
    }

    memset(dp, 0, sizeof(dp));
    memset(path, 0, sizeof(path));
    for (int i = 1; i <= fstLen; i++)
    {
        int pos = 0;
        for (int j = 1; j <= sndLen; j++)
        {
            if (fstArr[i] == sndArr[j])
            {
                dp[j] = dp[pos] + 1;
                path[j] = pos;
            }
            if (fstArr[i] > sndArr[j] && dp[pos] < dp[j])
            {
                pos = j;
            }
        }
    }

    int ans = 0, endPt = 0;
    for (int j = 1; j <= sndLen; j++)
    {
        if (ans < dp[j])
        {
            ans = dp[j];
            endPt = j;
        }
    }

    cout << ans << endl;
    print(endPt);
    cout << endl;
    return 0;
}
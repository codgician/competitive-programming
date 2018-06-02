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

long long int dp[SIZE][SIZE];
int cntArr[SIZE];

inline void init()
{
    dp[0][0] = 1;
    for (int i = 1; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            dp[i][j] = 0;
            for (int k = 0; k < 10; k++)
            {
                if (j == 4 && k == 9)
                    continue;
                dp[i][j] += dp[i - 1][k];
            }
        }
    }
}

inline long long int work(long long int cnt)
{
    long long int ans = 0;
    int len = 0;
    while (cnt)
    {
        cntArr[len++] = cnt % 10;
        cnt /= 10;
    }
    cntArr[len] = 0;

    for (int i = len - 1; i >= 0; i--)
    {
        for (int j = 0; j < cntArr[i]; j++)
        {
            if (cntArr[i + 1] == 4 && j == 9)
                continue;
            ans += dp[i + 1][j];
        }

        if (cntArr[i + 1] == 4 && cntArr[i] == 9)
            break;
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    init();
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        long long int num;
        cin >> num;
        cout << num + 1 - work(num + 1) << endl;
    }
    return 0;
}
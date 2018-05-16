#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 10001
using namespace std;

int dp[SIZE], item[3] = {150, 200, 350};

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int money;
        cin >> money;

        for (int i = 0; i <= money; i++)
            dp[i] = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = item[i]; j <= money; j++)
            {
                dp[j] = max(dp[j], dp[j - item[i]] + item[i]);
            }
        }

        cout << money - dp[money] << endl;
    }
    return 0;
}

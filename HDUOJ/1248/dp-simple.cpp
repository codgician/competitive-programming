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
            for (int j = money; j >= item[i]; j--)
            {
                for (int k = 1; j - k * item[i] >= 0; k++)
                {
                    dp[j] = max(dp[j], dp[j - k * item[i]] + k * item[i]);
                }
            }
        }

        cout << money - dp[money] << endl;
    }
    return 0;
}

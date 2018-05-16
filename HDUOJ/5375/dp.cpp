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
#define SIZE 200010
using namespace std;

long long int arr[SIZE];
long long int dp[SIZE][2];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        string str;
        cin >> str;

        int strLen = str.size();
        for (int i = 0; i < strLen; i++)
        {
            cin >> arr[i];
        }

        dp[0][0] = INT_MIN;
        dp[0][1] = INT_MIN;
        if (str[0] != '1')
            dp[0][0] = 0;
        if (str[0] != '0')
            dp[0][1] = arr[0];
        
        for (int i = 1; i < strLen; i++)
        {
            dp[i][0] = INT_MIN;
            dp[i][1] = INT_MIN;

            if (str[i] != '1')
                dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + arr[i]);
            if (str[i] != '0')
                dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + arr[i]);
        }

        cout << "Case #" << t << ": " << max(dp[strLen - 1][0], dp[strLen - 1][1]) << endl;
    }
    return 0;
}

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
#define LEFT 0
#define RIGHT 1
#define SIZE 1010
using namespace std;

typedef struct _Node
{
    bool typeId;
    int val;
} Node;

Node arr[SIZE];
int leftId[SIZE], leftRightId[SIZE];
long long int rightSum[SIZE];
long long int dp[SIZE][SIZE];

int main()
{
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int len;
        cin >> len;

        int leftNum = 0, rightNum = 0;
        for (int i = 1; i <= len; i++)
        {
            char ch;
            cin >> ch;
            if (ch == '(')
            {
                arr[i].typeId = LEFT;
                leftNum++;
                leftId[leftNum] = i;
                leftRightId[leftNum] = rightNum;
            }
            else
            {
                arr[i].typeId = RIGHT;
                rightNum++;
            }
        }

        rightSum[0] = 0;
        rightNum = 0;
        for (int i = 1; i <= len; i++)
        {
            cin >> arr[i].val;
            if (arr[i].typeId == RIGHT)
            {
                rightNum++;
                rightSum[rightNum] = rightSum[rightNum - 1] + arr[i].val;
            }
        }

        for (int i = 0; i <= leftNum; i++)
        {
            for (int j = 0; j <= rightNum; j++)
            {
                dp[i][j] = LLONG_MIN;
            }
        }
        for (int j = 0; j <= rightNum; j++)
        {
            dp[leftNum + 1][j] = 0;
        }

        long long int ans = 0;
        for (int i = leftNum; i >= 1; i--)
        {
            for (int j = rightNum; j >= leftRightId[i]; j--)
            {
                for (int k = j; k <= rightNum; k++)
                {
                    if (dp[i + 1][k] != LLONG_MIN)
                        dp[i][j] = max(dp[i][j], dp[i + 1][k] + (rightSum[j] - rightSum[leftRightId[i]]) * arr[leftId[i]].val);
                }
                ans = max(ans, dp[i][j]);
            }
        }

        cout << ans << endl;
    }
    return 0;
}
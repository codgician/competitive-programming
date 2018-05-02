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

        int leftPt = 0, rightPt = 0;
        for (int i = 1; i <= len; i++)
        {
            char ch;
            cin >> ch;
            if (ch == '(')
            {
                arr[i].typeId = LEFT;
                leftPt++;
                leftId[leftPt] = i;
                leftRightId[leftPt] = rightPt;
            }
            else
            {
                arr[i].typeId = RIGHT;
                rightPt++;
            }
        }

        rightSum[0] = 0;
        rightPt = 0;
        for (int i = 1; i <= len; i++)
        {
            cin >> arr[i].val;
            if (arr[i].typeId == RIGHT)
            {
                rightPt++;
                rightSum[rightPt] = rightSum[rightPt - 1] + arr[i].val;
            }
        }

        memset(dp, 0, sizeof(dp));
        long long int ans = 0;
        for (int i = leftPt; i >= 1; i--)
        {
            int cntFinishedLeft = leftPt - i;
            for (int j = len - cntFinishedLeft; j >= leftId[i]; j--)
            {
                int cntFinishedRight = len - j - cntFinishedLeft;
                if (j == len - cntFinishedLeft)
                {
                    dp[i][j] = dp[i + 1][j + 1] + arr[leftId[i]].val * (rightSum[rightPt - cntFinishedRight] - rightSum[leftRightId[i]]);
                }
                else
                {
                    dp[i][j] = max(dp[i + 1][j + 1] + arr[leftId[i]].val * (rightSum[rightPt - cntFinishedRight] - rightSum[leftRightId[i]]), dp[i][j + 1]);
                }

                if (i == 1)
                {
                    ans = max(ans, dp[i][j]);
                }
            }

            for (int j = leftId[i] - 1; j >= leftId[i - 1]; j--)
            {
                dp[i][j] = dp[i][j + 1];

                if (i == 1)
                {
                    ans = max(ans, dp[i][j]);
                }
            }
        }

        cout << ans << endl;
    }
    return 0;
}
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

#define TIME_SIZE 2010
#define STAGE_SIZE 1024
#define SHOW_SIZE 1010

typedef struct _Show
{
    int startPt, endPt;
    int val, stage;

    bool operator < (const struct _Show & snd) const
    {
        return startPt < snd.startPt;
    }
} Show;

Show showArr[SHOW_SIZE];
int showPt;

int dp[TIME_SIZE][STAGE_SIZE], maxArr[STAGE_SIZE];
int dscArr[TIME_SIZE], dscPt;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int stageNum;
    while (cin >> stageNum)
    {
        dscPt = 0, showPt = 0;
        for (int i = 0; i < stageNum; i++)
        {
            int cntNum;
            cin >> cntNum;
            for (int j = 0; j < cntNum; j++)
            {
                int startPt, endPt, val;
                cin >> startPt >> endPt >> val;
                showArr[showPt++] = {startPt, endPt, val, i}; 
                dscArr[dscPt++] = startPt;
                dscArr[dscPt++] = endPt;
            }
        }

        sort(dscArr + 0, dscArr + dscPt);
        dscPt = unique(dscArr + 0, dscArr + dscPt) - dscArr;

        for (int i = 0; i < showPt; i++)
        {
            showArr[i].startPt = lower_bound(dscArr + 0, dscArr + dscPt, showArr[i].startPt) - dscArr + 1;
            showArr[i].endPt = lower_bound(dscArr + 0, dscArr + dscPt, showArr[i].endPt) - dscArr + 1;
        }

        sort(showArr + 0, showArr + showPt);

        for (int i = 0; i <= dscPt; i++)
            for (int j = 0; j < (1 << stageNum); j++)
                dp[i][j] = INT_MIN;
        for (int i = 0; i < (1 << stageNum); i++)
            maxArr[i] = INT_MIN;
        dp[0][0] = 0;
        maxArr[0] = 0;

        for (int i = 0; i <= dscPt; i++)
        {
            for (int j = 0; j < (1 << stageNum); j++)
            { 
                dp[i][j] = max(maxArr[j], dp[i][j]);
                maxArr[j] = dp[i][j];
                if (maxArr[j] == INT_MIN)
                    continue;

                int pos = lower_bound(showArr + 0, showArr + showPt, Show{i}) - showArr;

                // Update all values with the same startPt
                for (int k = pos; k < showPt && showArr[k].startPt == showArr[pos].startPt; k++)
                {
                    int nextPt = showArr[k].endPt;
                    int nextState = j | (1 << showArr[k].stage);
                    dp[nextPt][nextState] = max(dp[nextPt][nextState], dp[i][j] + showArr[k].val);
                }
            }
        }

        if (maxArr[(1 << stageNum) - 1] == INT_MIN)
            cout << -1 << endl;
        else
            cout << maxArr[(1 << stageNum) - 1] << endl;
    }

    return 0;
}
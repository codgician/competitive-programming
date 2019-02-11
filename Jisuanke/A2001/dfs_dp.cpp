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

#define SIZE 1010

#define GOOD 0
#define NORMAL 1
#define BAD 2

int arr[SIZE][3];
int dp[SIZE][210];
int num, score, goodLim, badLim;
const int upperLim = 100, lowerLim = -100;

int inBound(int score)
{
	return max(min(score, upperLim), lowerLim);
}

int getNextScore(int cntRound, int type, int cntScore)
{
	if (type == 0)
		return inBound(cntScore + arr[cntRound][type]);
	if (type == 1)
		return inBound(cntScore - arr[cntRound][type]);
	return inBound(-cntScore);
}

int dfs(int cntRound, int cntScore)
{
	if (cntRound == num)
	{
		if (cntScore >= goodLim)
			return GOOD;
		if (cntScore <= badLim)
			return BAD;
		return NORMAL;
	}

	if (dp[cntRound][cntScore + 100] != -1)
		return dp[cntRound][cntScore + 100];

	int res;
	if (cntRound & 1)
	{
		// Sena: Wanna Bad
		res = GOOD;
		for (int i = 0; i < 3; i++)
		{
			if (arr[cntRound][i] != 0)
				res = max(res, dfs(cntRound + 1, getNextScore(cntRound, i, cntScore)));
		}
	}
	else
	{
		// Koutarou: Wanna Good
		res = BAD;
		for (int i = 0; i < 3; i++)
		{
			if (arr[cntRound][i] != 0)
				res = min(res, dfs(cntRound + 1, getNextScore(cntRound, i, cntScore)));
		}
	}

	dp[cntRound][cntScore + 100] = res;
	return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> num >> score >> goodLim >> badLim)
    {
    	memset(dp, -1, sizeof(dp));
        for (int i = 0; i < num; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cin >> arr[i][j];
            }
        }

        int ans = dfs(0, score);
        if (ans == GOOD)
            cout << "Good Ending" << endl;
        else if (ans == BAD)
            cout << "Bad Ending" << endl;
        else
            cout << "Normal Ending" << endl;
    }
    return 0;
}
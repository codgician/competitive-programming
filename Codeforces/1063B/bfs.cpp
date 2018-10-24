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

#define SIZE 2010

typedef struct _Node
{
    int x, y;
} Node;

typedef struct _State
{
    Node pt;
    int leftNum;
} State;

char arr[SIZE][SIZE];
int row, column;
int leftLim, rightLim;

int dir[2][4] = {1, -1, 0, 0, 0, 0, 1, -1};
int dp[SIZE][SIZE];

bool canReach(Node & nextPt)
{
    return nextPt.x >= 0 && nextPt.y >= 0 && nextPt.x < row && nextPt.y < column && arr[nextPt.x][nextPt.y] == '.';
}

void bfs(Node & startPt)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            dp[i][j] = INT_MAX;
        }
    }

    queue<State> q;
    q.push(State{startPt, 0});
    dp[startPt.x][startPt.y] = 0;

    while (!q.empty())
    {
        State cntState = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            Node nextPt = {cntState.pt.x + dir[0][i], cntState.pt.y + dir[1][i]};
            if (!canReach(nextPt))
                continue;

            State nextState = {nextPt, cntState.leftNum};

            if (i == 3)
            {
                // Left
                nextState.leftNum++;
            }
            else if (i == 4)
            {
                // Right
                int rightNum = nextState.leftNum - startPt.y + nextPt.y;
                if (rightNum > rightLim)
                    continue;
            }

            if (nextState.leftNum >= dp[nextPt.x][nextPt.y])
                continue;
            dp[nextPt.x][nextPt.y] = nextState.leftNum;
            q.push(nextState);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (cin >> row >> column)
    {
        Node startPt;
        cin >> startPt.x >> startPt.y;
        startPt.x--, startPt.y--;

        cin >> leftLim >> rightLim;

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                cin >> arr[i][j];
            }

        }
        bfs(startPt);

        int ans = 0;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                if (dp[i][j] <= leftLim && dp[i][j] - startPt.y + j <= rightLim)
                {
                    ans++;
                }
            }
        }
        cout << ans << endl;
    }

    return 0;
}
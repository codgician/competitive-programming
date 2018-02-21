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
#include <set>
#include <map>
#define SIZE 10
using namespace std;

typedef struct _Node
{
    int x, y;
} Node;

int arr[SIZE][SIZE], step[SIZE][SIZE], remTime[SIZE][SIZE];
int dir[2][4] = {1, -1, 0, 0, 0, 0, 1, -1};
int row, column, minStep;

Node startPt, endPt;

bool canMove(Node cntPt)
{
    if (cntPt.x < 0 || cntPt.x >= row || cntPt.y < 0 || cntPt.y >= column || arr[cntPt.x][cntPt.y] == 0)
        return false;
    else
        return true;
}

void dfs(Node cntPt, int cntStep, int cntRemTime)
{
    if (cntStep >= minStep || cntRemTime <= 0)
        return;

    if (cntPt.x == endPt.x && cntPt.y == endPt.y)
    {
        minStep = cntStep;
        return;
    }

    if (cntStep >= step[cntPt.x][cntPt.y] && remTime[cntPt.x][cntPt.y] >= cntRemTime)
        return;

    step[cntPt.x][cntPt.y] = cntStep;
    remTime[cntPt.x][cntPt.y] = cntRemTime;

    for (int i = 0; i < 4; i++)
    {
        Node nextPt;
        nextPt.x = cntPt.x + dir[0][i];
        nextPt.y = cntPt.y + dir[1][i];

        if (canMove(nextPt))
        {
            if (cntRemTime > 1 && arr[nextPt.x][nextPt.y] == 4)
            {
                dfs(nextPt, cntStep + 1, 6);
            }
            else
            {
                dfs(nextPt, cntStep + 1, cntRemTime - 1);
            }
        }
    }

    return;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        minStep = INT_MAX;
        cin >> row >> column;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                cin >> arr[i][j];
                step[i][j] = INT_MAX;
                remTime[i][j] = 0;
                if (arr[i][j] == 2)
                {
                    startPt.x = i;
                    startPt.y = j;
                }

                else if (arr[i][j] == 3)
                {
                    endPt.x = i;
                    endPt.y = j;
                }
            }
        }

        dfs(startPt, 0, 6);

        if (minStep == INT_MAX)
        {
            cout << -1 << endl;
        }
        else
        {
            cout << minStep << endl;
        }
    }
    return 0;
}

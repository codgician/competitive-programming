#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SIZE 8
using namespace std;

typedef struct _Node
{
    int x, y;
    int bx, by;
    int boxStep;

    bool onBox()
    {
        return x == bx && y == by;
    }
    bool operator < (const struct _Node b) const
    {
        return boxStep > b.boxStep;
    }
    bool operator == (const struct _Node b) const
    {
        return bx == b.bx && by == b.by;
    }
} Node;

int arr[SIZE][SIZE], dp[SIZE][SIZE][SIZE][SIZE], dir[2][4] = {1, -1, 0, 0, 0, 0, 1, -1};
int row, column;

bool canMove(Node &nextPt)
{
    if (nextPt.x < 0 || nextPt.x >= row || nextPt.y < 0 || nextPt.y >= column || arr[nextPt.x][nextPt.y] == 1)
        return false;
    if (nextPt.bx < 0 || nextPt.bx >= row || nextPt.by < 0 || nextPt.by >= column || arr[nextPt.bx][nextPt.by] == 1)
        return false;
    if (nextPt.boxStep >= dp[nextPt.x][nextPt.y][nextPt.bx][nextPt.by])
        return false;
    return true;
}

int bfs(Node &startPt)
{
    priority_queue<Node> pq;
    startPt.boxStep = 0;
    pq.push(startPt);

    while (!pq.empty())
    {
        Node cntPt = pq.top();
        pq.pop();

        for (int i = 0; i < 4; i++)
        {
            Node nextPt;
            nextPt.x = cntPt.x + dir[0][i];
            nextPt.y = cntPt.y + dir[1][i];
            nextPt.bx = cntPt.bx;
            nextPt.by = cntPt.by;
            nextPt.boxStep = cntPt.boxStep;

            if (nextPt.onBox())
            {
                nextPt.bx += dir[0][i];
                nextPt.by += dir[1][i];
                nextPt.boxStep++;
            }

            if (!canMove(nextPt))
                continue;

            dp[nextPt.x][nextPt.y][nextPt.bx][nextPt.by] = nextPt.boxStep;

            if (arr[nextPt.bx][nextPt.by] == 3)
                return nextPt.boxStep;

            pq.push(nextPt);
        }
    }
    return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        cin >> row >> column;
        Node startPt;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                cin >> arr[i][j];
                if (arr[i][j] == 4)
                {
                    startPt.x = i;
                    startPt.y = j;
                }
                else if (arr[i][j] == 2)
                {
                    startPt.bx = i;
                    startPt.by = j;
                }

                for (int k = 0; k < row; k++)
                {
                    for (int l = 0; l < column; l++)
                    {
                        dp[i][j][k][l] = INT_MAX;
                    }
                }
            }
        }
        cout << bfs(startPt) << endl;
    }
    return 0;
}

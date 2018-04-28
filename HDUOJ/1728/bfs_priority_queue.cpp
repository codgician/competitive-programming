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
#define SIZE 101
using namespace std;

typedef struct _Node
{
    int x, y;
    int dir;
    int turnNum;

    bool operator < (const struct _Node &b) const
    {
        return turnNum > b.turnNum;
    }
    bool operator == (const struct _Node &b) const
    {
        return x == b.x && y == b.y;
    }
} Node;

bool arr[SIZE][SIZE];
int dp[SIZE][SIZE], dir[2][4] = {1, -1, 0, 0, 0, 0, 1, -1};

int row, column, maxTurn;

bool canMove(Node nextPt)
{
    if (nextPt.x < 0 || nextPt.x >= row || nextPt.y < 0 || nextPt.y >= column || arr[nextPt.x][nextPt.y])
        return false;
    if (nextPt.turnNum > dp[nextPt.x][nextPt.y] || nextPt.turnNum > maxTurn)
        return false;
    return true;
}

bool bfs(Node startPt, Node endPt)
{
    priority_queue<Node> pq;
    startPt.dir = -1;
    startPt.turnNum = -1;
    pq.push(startPt);
    dp[startPt.x][startPt.y] = 0;

    while (!pq.empty())
    {
        Node cntPt = pq.top();
        pq.pop();

        for (int i = 0; i < 4; i++)
        {
            Node nextPt;
            nextPt.x = cntPt.x + dir[0][i];
            nextPt.y = cntPt.y + dir[1][i];
            nextPt.dir = i;
            nextPt.turnNum = cntPt.turnNum;
            if (cntPt.dir != nextPt.dir)
                nextPt.turnNum++;

            if (!canMove(nextPt))
                continue;

            dp[nextPt.x][nextPt.y] = min(dp[nextPt.x][nextPt.y], nextPt.turnNum);
            pq.push(nextPt);
        }
    }

    if (dp[endPt.x][endPt.y] <= maxTurn)
        return true;
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        cin >> row >> column;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                char ch;
                cin >> ch;
                if (ch == '.')
                    arr[i][j] = false;
                else
                    arr[i][j] = true;
                dp[i][j] = INT_MAX;
            }
        }

        Node startPt, endPt;
        cin >> maxTurn >> startPt.y >> startPt.x >> endPt.y >> endPt.x;
        startPt.x--;
        startPt.y--;
        endPt.x--;
        endPt.y--;

        if (bfs(startPt, endPt))
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
    return 0;
}

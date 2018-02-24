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
#define SIZE 21
using namespace std;

typedef struct _Node
{
    int x, y;
    int step;

    bool operator < (const struct _Node b) const
    {
        return step > b.step;
    }
    bool operator == (const struct _Node b) const
    {
        return x == b.x && y == b.y;
    }
} Node;

char arr[SIZE][SIZE];
int dp[SIZE][SIZE], dir[2][4] = {1, -1, 0, 0, 0, 0, 1, -1};
int row, column;

bool canMove(Node &nextPt)
{
    if (nextPt.x < 0 || nextPt.x >= row || nextPt.y < 0 || nextPt.y >= column || arr[nextPt.x][nextPt.y] == '*' || nextPt.step >= dp[nextPt.x][nextPt.y])
        return false;
    return true;
}

int bfs(Node &startPt, Node &endPt)
{
    priority_queue<Node> q;

    startPt.step = 0;
    q.push(startPt);

    while (!q.empty())
    {
        Node cntPt = q.top();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            Node nextPt;
            nextPt.x = cntPt.x + dir[0][i];
            nextPt.y = cntPt.y + dir[1][i];
            nextPt.step = cntPt.step + 1;

            if (!canMove(nextPt))
                continue;

            if (arr[nextPt.x][nextPt.y] == '|')
            {
                nextPt.x += dir[0][i];
                nextPt.y += dir[1][i];
                if (((cntPt.step & 1) == 0 && i > 1) || ((cntPt.step & 1) == 1 && i < 2))
                    nextPt.step++;
            }
            else if (arr[nextPt.x][nextPt.y] == '-')
            {
                nextPt.x += dir[0][i];
                nextPt.y += dir[1][i];
                if (((cntPt.step & 1) == 0 && i < 2) || ((cntPt.step & 1) == 1 && i > 1))
                    nextPt.step++;
            }

            if (!canMove(nextPt))
                continue;

            if (nextPt == endPt)
            {
                return nextPt.step;
            }
            dp[nextPt.x][nextPt.y] = nextPt.step;
            q.push(nextPt);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> row >> column)
    {
        Node startPt, endPt;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                cin >> arr[i][j];
                dp[i][j] = INT_MAX;
                if (arr[i][j] == 'S')
                {
                    startPt.x = i;
                    startPt.y = j;
                }
                else if (arr[i][j] == 'T')
                {
                    endPt.x = i;
                    endPt.y = j;
                }
            }
        }
        cout << bfs(startPt, endPt) << endl;
    }
    return 0;
}

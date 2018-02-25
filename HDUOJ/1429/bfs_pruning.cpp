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
#define KEY_SIZE 1024
using namespace std;

typedef struct _Node
{
    int x, y;
    int keyState;
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
int dp[SIZE][SIZE][KEY_SIZE], dir[2][4] = {1, -1, 0, 0, 0, 0, 1, -1};
int row, column, timeLimit;

bool canMove(Node &nextPt)
{
    if (nextPt.x < 0 || nextPt.x >= row || nextPt.y < 0 || nextPt.y >= column || arr[nextPt.x][nextPt.y] == '*')
        return false;
    if (arr[nextPt.x][nextPt.y] >= 'A' && arr[nextPt.x][nextPt.y] <= 'J' && !(nextPt.keyState & (1 << (arr[nextPt.x][nextPt.y] - 'A'))))
        return false;
    if (nextPt.step >= min(dp[nextPt.x][nextPt.y][nextPt.keyState], timeLimit))
        return false;
    return true;
}

int bfs(Node &startPt)
{
    priority_queue<Node> pq;
    startPt.step = 0;
    startPt.keyState = 0;
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
            nextPt.keyState = cntPt.keyState;
            nextPt.step = cntPt.step + 1;

            if (!canMove(nextPt))
                continue;

            if (arr[nextPt.x][nextPt.y] >= 'a' && arr[nextPt.x][nextPt.y] <= 'j' && !(nextPt.keyState & (1 << (arr[nextPt.x][nextPt.y] - 'a'))))
            {
                nextPt.keyState += (1 << (arr[nextPt.x][nextPt.y] - 'a'));
            }

            if (arr[nextPt.x][nextPt.y] == '^')
            {
                return nextPt.step;
            }

            dp[nextPt.x][nextPt.y][nextPt.keyState] = nextPt.step;
            pq.push(nextPt);
        }
    }
    return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    Node startPt;
    while (cin >> row >> column >> timeLimit)
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                cin >> arr[i][j];
                if (arr[i][j] == '@')
                {
                    startPt.x = i;
                    startPt.y = j;
                }
                for (int k = 0; k < KEY_SIZE; k++)
                {
                    dp[i][j][k] = INT_MAX;
                }
            }
        }

        cout << bfs(startPt) << endl;
    }
    return 0;
}

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
#define SIZE 1001
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

int arr[SIZE][SIZE], dir[2][4] = {1, -1, 0, 0, 0, 0, 1, -1};
bool hasVisited[SIZE][SIZE];
int row, column;

bool canMove(Node &nextPt, Node &endPt)
{
    if (nextPt.x < 0 || nextPt.x >= row || nextPt.y < 0 || nextPt.y >= column || hasVisited[nextPt.x][nextPt.y] || nextPt.turnNum > 2)
        return false;
    else if (arr[nextPt.x][nextPt.y] != 0 && !(nextPt == endPt))
        return false;
    return true;
}

bool bfs(Node &startPt, Node &endPt)
{
    memset(hasVisited, false, sizeof(hasVisited));

    priority_queue<Node> q;
    q.push(startPt);
    hasVisited[startPt.x][startPt.y] = true;

    while (!q.empty())
    {
        Node cntPt;
        cntPt = q.top();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            Node nextPt;
            nextPt.x = cntPt.x + dir[0][i];
            nextPt.y = cntPt.y + dir[1][i];
            nextPt.dir = i;
            nextPt.turnNum = cntPt.turnNum;
            if (cntPt.dir != nextPt.dir)
            {
                // A turn has been made
                nextPt.turnNum++;
            }

            if (canMove(nextPt, endPt))
            {
                hasVisited[nextPt.x][nextPt.y] = true;
                if (nextPt == endPt)
                {
                    return true;
                }
                q.push(nextPt);
            }
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> row >> column)
    {
        if (row == 0 && column == 0)
            break;

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                cin >> arr[i][j];
            }
        }

        int queryNum;
        cin >> queryNum;
        while (queryNum--)
        {
            Node startPt, endPt;
            cin >> startPt.x >> startPt.y >> endPt.x >> endPt.y;
            startPt.x--;
            startPt.y--;
            endPt.x--;
            endPt.y--;
            if (arr[startPt.x][startPt.y] != arr[endPt.x][endPt.y] || arr[startPt.x][startPt.y] == 0 || arr[endPt.x][endPt.y] == 0 || (startPt == endPt))
            {
                cout << "NO" << endl;
                continue;
            }
            startPt.dir = -1;
            startPt.turnNum = -1;

            if (bfs(startPt, endPt))
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}

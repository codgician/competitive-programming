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
#define SIZE 51
using namespace std;

typedef struct _Node
{
    int x, y, z;
    int step;

    bool operator < (const struct _Node b) const
    {
        return step > b.step;
    }
    bool operator == (const struct _Node b) const
    {
        return x == b.x && y == b.y && z == b.z;
    }
} Node;

bool arr[SIZE][SIZE][SIZE], hasVisited[SIZE][SIZE][SIZE];
int dir[3][6] = {1, -1, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 1, -1};
int row, height, column, timeLimit;

bool canMove(Node &nextPt)
{
    if (nextPt.x < 0 || nextPt.x >= row || nextPt.y < 0 || nextPt.y >= height || nextPt.z < 0 || nextPt.z >= column || arr[nextPt.x][nextPt.y][nextPt.z] || hasVisited[nextPt.x][nextPt.y][nextPt.z] || nextPt.step >= timeLimit)
        return false;
    return true;
}

int bfs(Node &startPt, Node &endPt)
{
    memset(hasVisited, false, sizeof(hasVisited));
    priority_queue<Node> pq;
    startPt.step = 0;
    pq.push(startPt);

    while (!pq.empty())
    {
        Node cntPt = pq.top();
        pq.pop();

        for (int i = 0; i < 6; i++)
        {
            Node nextPt = {cntPt.x + dir[0][i], cntPt.y + dir[1][i], cntPt.z + dir[2][i], cntPt.step + 1};
            if (!canMove(nextPt))
                continue;

            if (abs(endPt.x - nextPt.x) + abs(endPt.y - nextPt.y) + abs(endPt.z - nextPt.z) > timeLimit - nextPt.step)
                continue;

            if (nextPt == endPt)
            {
                return nextPt.step;
            }
            hasVisited[nextPt.x][nextPt.y][nextPt.z] = true;
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
        cin >> row >> height >> column >> timeLimit;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < height; j++)
            {
                for (int k = 0; k < column; k++)
                {
                    cin >> arr[i][j][k];
                }
            }
        }

        Node startPt = {0, 0, 0, 0}, endPt = {row - 1, height - 1, column - 1};
        if (abs(endPt.x - startPt.x) + abs(endPt.y - startPt.y) + abs(endPt.z - startPt.z) > timeLimit)
            cout << -1 << endl;
        else
            cout << bfs(startPt, endPt) << endl;
    }
    return 0;
}

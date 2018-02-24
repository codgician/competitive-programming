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
#define SIZE 201
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
bool hasVisited[SIZE][SIZE];
int dir[2][4] = {1, -1, 0, 0, 0, 0, 1, -1};
int row, column;

bool canMove(Node &nextPt)
{
    if (nextPt.x < 0 || nextPt.x >= row || nextPt.y < 0 || nextPt.y >= column || arr[nextPt.x][nextPt.y] == '#' || hasVisited[nextPt.x][nextPt.y])
        return false;
    return true;
}

int bfs(Node &startPt)
{
    int ans = INT_MAX;

    memset(hasVisited, false, sizeof(hasVisited));
    priority_queue<Node> pq;
    startPt.step = 0;
    pq.push(startPt);
    hasVisited[startPt.x][startPt.y] = true;

    while (!pq.empty())
    {
        Node cntPt = pq.top();
        pq.pop();

        for (int i = 0; i < 4; i++)
        {
            Node nextPt;
            nextPt.x = cntPt.x + dir[0][i];
            nextPt.y = cntPt.y + dir[1][i];
            nextPt.step = cntPt.step + 1;

            if (!canMove(nextPt))
                continue;

            if (arr[nextPt.x][nextPt.y] == 'x')
            {
                nextPt.step++;
            }

            if (arr[nextPt.x][nextPt.y] == 'r')
            {
                ans = min(ans, nextPt.step);
            }
            hasVisited[nextPt.x][nextPt.y] = true;
            pq.push(nextPt);
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> row >> column)
    {
        Node startPt;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                cin >> arr[i][j];
                if (arr[i][j] == 'a')
                {
                    startPt.x = i;
                    startPt.y = j;
                }
            }
        }

        int ans = bfs(startPt);
        if (ans == INT_MAX)
        {
            cout << "Poor ANGEL has to stay in the prison all his life." << endl;
        }
        else
        {
            cout << ans << endl;
        }
    }
    return 0;
}

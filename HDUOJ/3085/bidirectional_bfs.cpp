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
#include <stack>
#include <iterator>
#include <functional>
#define SIZE 810
using namespace std;

typedef struct _Node
{
    int x, y;
} Node;

Node ghostArr[2];

char arr[SIZE][SIZE];
bool hasVisited[2][SIZE][SIZE];
int dir[2][4] = {1, -1, 0, 0, 0, 0, 1, -1};
queue<Node> q[2];

int row, column;

int getManhattanDis(Node &a, Node &b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

bool canMove(Node &cntPt, int cntStep)
{
    if (cntPt.x < 0 || cntPt.y < 0 || cntPt.x >= row || cntPt.y >= column || arr[cntPt.x][cntPt.y] == 'X')
        return false;

    for (int i = 0; i < 2; i++)
    {
        if (getManhattanDis(cntPt, ghostArr[i]) <= (cntStep << 1))
        {
            return false;
        }
    }

    return true;
}

bool bfs(bool qId, int cntStep)
{
    int stateNum = q[qId].size();
    while (stateNum--)
    {
        Node cntPt = q[qId].front();
        q[qId].pop();

        if (!canMove(cntPt, cntStep))
            continue;
        
        for (int i = 0; i < 4; i++)
        {
            Node nextPt;
            nextPt.x = cntPt.x + dir[0][i];
            nextPt.y = cntPt.y + dir[1][i];

            if (!canMove(nextPt, cntStep) || hasVisited[qId][nextPt.x][nextPt.y])
                continue;

            if (hasVisited[qId ^ 1][nextPt.x][nextPt.y])
                return true;

            hasVisited[qId][nextPt.x][nextPt.y] = true;
            q[qId].push(nextPt);
        }
    }

    return false;
}

int bibfs(Node &startPt, Node &endPt)
{
    memset(hasVisited, false, sizeof(hasVisited));

    q[0] = queue<Node>();
    q[1] = queue<Node>();

    q[0].push(startPt);
    hasVisited[0][startPt.x][startPt.y] = true;
    q[1].push(endPt);
    hasVisited[1][endPt.x][endPt.y] = true;

    int step = 0;
    while (!q[0].empty() || !q[1].empty())
    {
        step++;
        for (int i = 0; i < 3; i++)
        {
            if (bfs(0, step))
            {
                return step;
            }
        }
        if (bfs(1, step))
        {
            return step;
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

        Node boyStartPt, girlStartPt;
        int ghostPt = 0;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                cin >> arr[i][j];

                if (arr[i][j] == 'M')
                {
                    boyStartPt.x = i;
                    boyStartPt.y = j;
                }
                else if (arr[i][j] == 'G')
                {
                    girlStartPt.x = i;
                    girlStartPt.y = j;
                }
                else if (arr[i][j] == 'Z')
                {
                    ghostArr[ghostPt].x = i;
                    ghostArr[ghostPt].y = j;
                    ghostPt++;
                }
            }
        }

        int ans = bibfs(boyStartPt, girlStartPt);
        cout << ans << endl;
    }
    return 0;
}
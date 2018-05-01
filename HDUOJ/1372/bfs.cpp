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
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
#define SIZE 8
using namespace std;

typedef struct _Node
{
    int x, y;
    int step;
} Node;

bool hasVisited[SIZE][SIZE];
int dir[2][8] = {1, 1, -1, -1, 2, 2, -2, -2, 2, -2, 2, -2, 1, -1, 1, -1};

bool canMove(Node &pt)
{
    if (pt.x < 0 || pt.x >= 8 || pt.y < 0 || pt.y >= 8 || hasVisited[pt.x][pt.y])
        return false;
    return true;
}

int bfs(Node &startPt, Node &endPt)
{
    memset(hasVisited, false, sizeof(hasVisited));
    queue<Node> q;
    startPt.step = 0;
    q.push(startPt);
    hasVisited[startPt.x][startPt.y] = true;

    while (!q.empty())
    {
        Node cntPt = q.front();
        q.pop();

        if (cntPt.x == endPt.x && cntPt.y == endPt.y)
            return cntPt.step;

        for (int i = 0; i < 8; i++)
        {
            Node nextPt;
            nextPt.x = cntPt.x + dir[0][i];
            nextPt.y = cntPt.y + dir[1][i];
            nextPt.step = cntPt.step + 1;

            if (!canMove(nextPt))
                continue;

            hasVisited[nextPt.x][nextPt.y] = true;
            q.push(nextPt);
        }
    }

    return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    string startStr, endStr;
    while (cin >> startStr >> endStr)
    {
        Node startPt, endPt;
        startPt.x = startStr[0] - 'a';
        startPt.y = startStr[1] - '1';
        endPt.x = endStr[0] - 'a';
        endPt.y = endStr[1] - '1';

        int ans = bfs(startPt, endPt);
    
        cout << "To get from " << startStr << " to " << endStr << " takes " << ans << " knight moves." << endl;
    }
    return 0;
}
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
#define SIZE 21
using namespace std;

typedef struct _Node
{
    int x, y;
} Node;

char arr[SIZE][SIZE];
bool hasVisited[SIZE][SIZE];
int dir[2][4] = {1, -1, 0, 0, 0, 0, 1, -1};
int row, column;

bool canMove(Node &pt)
{
    if (pt.x < 0 || pt.x >= row || pt.y < 0 || pt.y >= column || arr[pt.x][pt.y] == '#' || hasVisited[pt.x][pt.y])
        return false;
    return true;
}

int bfs(Node &startPt)
{
    memset(hasVisited, false, sizeof(hasVisited));
    queue<Node> q;
    q.push(startPt);
    hasVisited[startPt.x][startPt.y] = true;

    int ans = 1;
    while (!q.empty())
    {
        Node cntPt = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            Node nextPt;
            nextPt.x = cntPt.x + dir[0][i];
            nextPt.y = cntPt.y + dir[1][i];

            if (!canMove(nextPt))
                continue;

            ans++;
            hasVisited[nextPt.x][nextPt.y] = true;
            q.push(nextPt);
        }
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> column >> row)
    {
        if (row == 0 && column == 0)
            break;

        Node startPt;
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
            }
        }

        int ans = bfs(startPt);
        cout << ans << endl;
    }
    return 0;
}
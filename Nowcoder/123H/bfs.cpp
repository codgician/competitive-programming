#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

typedef struct _Node
{
    int x, y;
} Node;

#define ROW_SIZE 10
#define COLUMN_SIZE 100010

const long long int mod = 1000000009;

int arr[ROW_SIZE][COLUMN_SIZE];
bool hasVisited[ROW_SIZE][COLUMN_SIZE];

int dir[2][4] = {1, -1, 0, 0, 0, 0, 1, -1};
int row, column, num;
int domId;

bool canMove(Node & cntPt)
{
    return cntPt.x >= 0 && cntPt.x < row && cntPt.y >= 0 && cntPt.y < column;
}

int bfs(Node & startPt)
{
    int ans = 0;
    memset(hasVisited, false, sizeof(hasVisited));
    queue<Node> q;
    q.push(startPt);
    hasVisited[startPt.x][startPt.y] = true;

    while (!q.empty())
    {
        Node cntPt = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            Node nextFstPt = {cntPt.x + dir[0][i], cntPt.y + dir[1][i]};
            Node nextSndPt = {cntPt.x + (dir[0][i] << 1), cntPt.y + (dir[1][i] << 1)};
            if (!canMove(nextSndPt))
                continue;
            if (arr[nextFstPt.x][nextFstPt.y] != arr[nextSndPt.x][nextSndPt.y])
                continue;
            if (hasVisited[nextSndPt.x][nextSndPt.y])
                continue;
            hasVisited[nextSndPt.x][nextSndPt.y] = true;

            ans++;
            if (ans >= mod)
                ans %= mod;
            q.push(nextSndPt);
        }
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> row >> column >> num)
    {
        domId = 0;
        memset(arr, -1, sizeof(arr));
        for (int i = 0; i < num; i++)
        {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            arr[--x1][--y1] = domId;
            arr[--x2][--y2] = domId;
            domId++;
        }

        Node startPt;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                if (arr[i][j] == -1)
                {
                    startPt = {i, j};
                    break;
                }
            }
        }

        int ans = bfs(startPt);
        cout << ans << endl;
    }
    return 0;
}
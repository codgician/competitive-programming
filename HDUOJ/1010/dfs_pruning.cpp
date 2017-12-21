#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#define SIZE 51
using namespace std;

bool matrix[SIZE][SIZE], hasVisited[SIZE][SIZE], hasFound = false;
short move_x[4] = {1, -1, 0, 0}, move_y[4] = {0, 0, 1, -1};
int n, m, t;

struct Node {
    int i;
    int j;
    bool type;
} door, startPt;

bool getBlockType(int i, int j)
{
    return (i + j) & 1;
}

bool dfsCut(int i, int j, int t)
{
    int ansType = !(getBlockType(i, j) == door.type);
    if (t & 1 != ansType)
        return false;
    return true;
}

bool canMove(int i, int j)
{
    return i >= 0 && i < n && j >= 0 && j < m && !hasVisited[i][j] && !matrix[i][j];
}

void dfs(int i, int j, int step)
{
    if (i == door.i && j == door.j)
    {
        if (step == t)
            hasFound = true;
        return;
    }

    if (step == t)
        return;

    if (!dfsCut(i, j, t - step))
        return;

    hasVisited[i][j] = true;

    for (int t = 0; t < 4; t++)
    {
        if (hasFound)
            return;
        int next_i = i + move_x[t];
        int next_j = j + move_y[t];
        if (canMove(next_i, next_j))
            dfs(next_i, next_j, step + 1);
    }

    hasVisited[i][j] = false;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> n >> m >> t)
    {
        hasFound = false;
        memset(hasVisited, false, sizeof(hasVisited));
        if (n == 0 && m == 0 && t == 0)
            break;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                char a;
                cin >> a;
                if (a == 'X')
                    matrix[i][j] = true;
                else
                {
                    matrix[i][j] = false;
                    if (a == 'D')
                    {
                        door.i = i;
                        door.j = j;
                        door.type = getBlockType(i, j);
                    }
                    else if (a == 'S')
                    {
                        startPt.i = i;
                        startPt.j = j;
                        startPt.type = getBlockType(i, j);
                    }
                }
            }
        }
        dfs(startPt.i, startPt.j, 0);
        if (hasFound)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}

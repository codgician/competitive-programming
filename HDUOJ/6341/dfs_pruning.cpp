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

#define SIZE 16

int arr[SIZE][SIZE], tmp[4][4];
bool hasVisited[SIZE];
int ans;

void rotate(int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tmp[j][3 - i] = arr[(x << 2) + i][(y << 2) + j];
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            arr[(x << 2) + i][(y << 2) + j] = tmp[i][j]; 
        }
    }
}

bool check(int x, int y)
{
    // Row
    for (int i = (x << 2); i < (x << 2) + 4; i++)
    {
        memset(hasVisited, false, sizeof(hasVisited));
        for (int j = 0; j < (y << 2) + 4; j++)
        {
            if (hasVisited[arr[i][j]])
                return false;
            hasVisited[arr[i][j]] = true;
        }
    }

    // Column
    for (int j = (y << 2); j < (y << 2) + 4; j++)
    {
        memset(hasVisited, false, sizeof(hasVisited));
        for (int i = 0; i < (x << 2) + 4; i++)
        {
            if (hasVisited[arr[i][j]])
                return false;
            hasVisited[arr[i][j]] = true;
        }
    }

    return true;
}

void dfs(int x, int y, int cntSum)
{
    if (cntSum >= ans)
        return;

    if (x == 4)
    {
        ans = min(ans, cntSum);
        return;
    }

    if (y == 4)
    {
        dfs(x + 1, 0, cntSum);
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        if (check(x, y))
            dfs(x, y + 1, cntSum + i);
        rotate(x, y);
    }
}

int main()
{
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                char ch;
                cin >> ch;

                if (ch >= '0' && ch <= '9')
                    arr[i][j] = ch - '0';
                else
                    arr[i][j] = ch - 'A' + 10;
            }
        }

        ans = INT_MAX;
        dfs(0, 0, 0);
        cout << ans << endl;
    }
    return 0;
}
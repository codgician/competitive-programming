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

#define SIZE 50

typedef struct _Node
{
    int x, y;
} Node;

long long int arr[SIZE][SIZE];
int row, column;
long long int k;

unordered_map<long long int, long long int> rowMp[SIZE];

int dir[2][2] = {1, 0, 0, 1};

Node startPt, endPt;

long long int ans;

long long int getMax(long long int n)
{
    int step = 0;
    while (n)
    {
        n >>= 1;
        step++;
    }
    return 1ll << step;
}

bool canMove(Node & cntPt)
{
    if (cntPt.x < 0 || cntPt.x >= row || cntPt.y < 0 || cntPt.y >= column)
        return false;
    return true;
}

void dfs1(Node & cntPt, long long int cntSum)
{
    cntSum ^= arr[cntPt.x][cntPt.y];
    if (cntPt.x + cntPt.y == (row + column - 2) >> 1)
    {
        rowMp[cntPt.x][cntSum]++;
        return;
    }

    for (int i = 0; i < 2; i++)
    {
        Node nextPt = {cntPt.x + dir[0][i], cntPt.y + dir[1][i]};
        if (canMove(nextPt))
            dfs1(nextPt, cntSum);
    }   
}

void dfs2(Node & cntPt, long long int cntSum)
{
    if (cntPt.x + cntPt.y == (row + column - 2) >> 1)
    {
        auto it = rowMp[cntPt.x].find(cntSum ^ k);
        if (it != rowMp[cntPt.x].end())
            ans += it -> second;
        return;
    }

    for (int i = 0; i < 2; i++)
    {
        Node nextPt = {cntPt.x - dir[0][i], cntPt.y - dir[1][i]};
        if (canMove(nextPt))
            dfs2(nextPt, cntSum ^ arr[cntPt.x][cntPt.y]);
    }   
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> row >> column >> k;

    long long int maxVal = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            cin >> arr[i][j];
            maxVal = max(maxVal, arr[i][j]);
        }
    }

    if (k > getMax(maxVal))
    {
        cout << 0 << endl;
        return 0;
    }

    ans = 0;
    startPt.x = 0;
    startPt.y = 0;
    endPt.x = row - 1;
    endPt.y =  column - 1;

    dfs1(startPt, 0);
    dfs2(endPt, 0);
    cout << ans << endl;
    return 0;
}
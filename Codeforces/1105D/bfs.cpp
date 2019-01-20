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
#include <cassert>
using namespace std;

#define SIZE 1010

char arr[SIZE][SIZE];
int vArr[SIZE];
int ans[9];

int dir[2][4] = {1, -1, 0, 0, 0, 0, -1, 1};
int row, column, num;
vector<pair<int, int> > startArr[SIZE];

typedef struct _State
{
    pair<int, int> pt;
    int step;
} State;

queue<State> q[10];

bool canMove(pair<int, int> & cntPt)
{
    return cntPt.first >= 0 && cntPt.first < row && cntPt.second >= 0 && cntPt.second < column;
}

bool bfs(int who)
{
    bool res = false;
    int stepLim = q[who].front().step + vArr[who];
    while (!q[who].empty())
    {
        State cntState = q[who].front();
        pair<int, int> cntPt = cntState.pt;
        int cntStep = cntState.step;

        if (cntStep >= stepLim)
            return res;

        q[who].pop();

        for (int i = 0; i < 4; i++)
        {
            pair<int, int> nextPt = make_pair(cntPt.first + dir[0][i], cntPt.second + dir[1][i]);
            if (!canMove(nextPt))
                continue;
            if (arr[nextPt.first][nextPt.second] != '.')
                continue;
            arr[nextPt.first][nextPt.second] = '1' + who;
            res = true;
            q[who].push(State{nextPt, cntStep + 1});
        }
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> row >> column >> num;
    for (int i = 0; i < num; i++)
        cin >> vArr[i];

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            cin >> arr[i][j];
            if (arr[i][j] > '0' && arr[i][j] <= '9')
            {
                startArr[arr[i][j] - '1'].push_back(make_pair(i, j));
            }
        }
    }

    for (int i = 0; i < num; i++)
    {
        for (auto it = startArr[i].begin(); it != startArr[i].end(); ++it)
            q[i].push(State{*it, 0});
    }

    // Multiple BFS
    bool chk = true;
    while (chk)
    {
        int cntChk = false;
        for (int i = 0; i < num; i++)
        {
            if (bfs(i))
                cntChk = true;
        }
        chk = cntChk;
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (arr[i][j] == '#' || arr[i][j] == '.')
                continue;
            ans[arr[i][j] - '1']++;
        }
    }

    for (int i = 0; i < num; i++)
    {
        cout << ans[i];
        if (i < num - 1)
            cout << " ";
        else
            cout << endl;
    }

    return 0;
}
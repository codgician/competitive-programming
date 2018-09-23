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

#define SIZE 110

typedef struct _State
{
    int x, y;
    int step;

    int oxyNum;

    bool operator < (const struct _State & snd) const
    {
        return step > snd.step;
    }
} State;

char arr[SIZE][SIZE];
int dp[SIZE][SIZE][7];
int dir[2][4] = {1, -1, 0, 0, 0, 0, 1, -1};

int row, column;

int bfs(int startPtx, int startPty)
{
    priority_queue<State> pq;
    pq.push(State{startPtx, startPty, 0, 0});

    while (!pq.empty())
    {
        State cntState = pq.top();
        pq.pop();

        if (arr[cntState.x][cntState.y] == 'T')
            return cntState.step;

        if (dp[cntState.x][cntState.y][cntState.oxyNum] != -1 && dp[cntState.x][cntState.y][cntState.oxyNum] <= cntState.step)
            continue;
        dp[cntState.x][cntState.y][cntState.oxyNum] = cntState.step;

        for (int i = 0; i < 4; i++)
        {
            State nextState;
            nextState.x = cntState.x + dir[0][i];
            nextState.y = cntState.y + dir[1][i];
            nextState.oxyNum = cntState.oxyNum;
            nextState.step = cntState.step + 1;

            if (nextState.x < 0 || nextState.x >= row || nextState.y < 0 || nextState.y >= column)
                continue;

            if (arr[nextState.x][nextState.y] == '#')
            {
                // Gas room
                if (cntState.oxyNum == 0)
                    continue;

                nextState.oxyNum -= 1;
                nextState.step += 1;
            }
            else if (arr[nextState.x][nextState.y] == 'P')
            {
                // Pill room
                nextState.step -= 1;
            }
            else if (arr[nextState.x][nextState.y] == 'B')
            {
                // Oxygen room
                if (nextState.oxyNum < 5)
                    nextState.oxyNum += 1;
            }

            pq.push(nextState);
        }
    }

    return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (cin >> row >> column)
    {
        if (row == 0 && column == 0)
            break;

        int startPtx = -1, startPty = -1;

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                cin >> arr[i][j];
                if (arr[i][j] == 'S')
                {
                    startPtx = i;
                    startPty = j;
                }

            }
        }

        memset(dp, -1, sizeof(dp));
        int ans = bfs(startPtx, startPty);
        cout << ans << endl;
    }

    return 0;
}
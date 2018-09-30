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

#define EDGE_SIZE 12110
#define VERTEX_SIZE 110

typedef struct _State
{
    int bobPt, alicePt;
    bool whoseTurn;
} State;

typedef struct _Edge
{
    int to;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;

int outDeg[VERTEX_SIZE];
bool dp[VERTEX_SIZE][VERTEX_SIZE][2];
// 0: Bob wins, 1: Alice wins
// 0: Bob's turn, 1: Alice's turn

int loseNum[VERTEX_SIZE][VERTEX_SIZE];  // As for Bob

int vertexNum, edgeNum;

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void bfs()
{
    // Push states for Bob to lose (0) into queue
    queue<State> q;
    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            dp[i][i][j] = true;
            q.push(State{i, i, j});
        }
    }

    for (int i = 0; i < vertexNum; i++)
    {
        if (outDeg[i] != 0)
            continue;
        for (int j = 0; j < vertexNum; j++)
        {
            if (dp[i][j][0] == false)
            {
                dp[i][j][0] = true;
                q.push(State{i, j, 0});
            }
        }
    }

    while (!q.empty())
    {
        State cntState = q.front();
        q.pop();

        if (cntState.whoseTurn == 1)
        {
            // Previous move is Bob's
            for (int i = head[cntState.bobPt]; i != -1; i = arr[i].next)
            {
                int nextPt = arr[i].to;
                if (dp[nextPt][cntState.alicePt][0] == false)
                {
                    loseNum[nextPt][cntState.alicePt]++;
                    if (loseNum[nextPt][cntState.alicePt] == outDeg[nextPt])
                    {
                        dp[nextPt][cntState.alicePt][0] = true;
                        q.push(State{nextPt, cntState.alicePt, 0});
                    }
                }
            }
        }
        else
        {
            // Previous move is Alice's
            for (int i = head[cntState.alicePt]; i != -1; i = arr[i].next)
            {
                int nextPt = arr[i].to;
                if (dp[cntState.bobPt][nextPt][1] == false)
                {
                    dp[cntState.bobPt][nextPt][1] = true;
                    q.push(State{cntState.bobPt, nextPt, 1});
                }
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        memset(head, -1, sizeof(head));
        memset(outDeg, 0, sizeof(outDeg));
        memset(loseNum, 0, sizeof(loseNum));
        memset(dp, false, sizeof(dp));
        arrPt = 0;

        cin >> vertexNum >> edgeNum;
        for (int i = 0; i < edgeNum; i++)
        {
            int from, to;
            cin >> from >> to;
            from--;
            to--;

            // Reverse
            addEdge(to, from);
            outDeg[from]++;
        }

        int bobPt, alicePt;
        cin >> bobPt >> alicePt;
        bobPt--;
        alicePt--;

        bfs();

        cout << "Case #" << t << ": ";
        if (dp[bobPt][alicePt][0])
            cout << "No" << endl;
        else
            cout << "Yes" << endl;
    }
    return 0;
}
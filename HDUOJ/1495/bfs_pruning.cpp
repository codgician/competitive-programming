#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SIZE 101
using namespace std;

typedef struct _Node
{
    int cup[3];
    int step;

    bool operator < (const struct _Node b) const
    {
        return step > b.step;
    }
    bool operator == (const struct _Node b) const
    {
        for (int i = 0; i < 3; i++)
        {
            if (cup[i] != b.cup[i])
                return false;
        }
        return true;
    }
} Node;

bool hasVisited[SIZE][SIZE][SIZE];
int cupSize[3];

int bfs(Node &startPt)
{
    memset(hasVisited, false, sizeof(hasVisited));
    priority_queue<Node> pq;
    startPt.step = 0;
    pq.push(startPt);
    hasVisited[startPt.cup[0]][startPt.cup[1]][startPt.cup[2]] = true;
    while (!pq.empty())
    {
        Node cntPt = pq.top();
        pq.pop();
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (i == j)
                    continue;

                Node nextPt = cntPt;
                nextPt.step++;
                if (nextPt.cup[i] + nextPt.cup[j] > cupSize[j])
                {
                    nextPt.cup[i] = cntPt.cup[i] + cntPt.cup[j] - cupSize[j];
                    nextPt.cup[j] = cupSize[j];
                }
                else
                {
                    nextPt.cup[i] = 0;
                    nextPt.cup[j] += cntPt.cup[i];
                }

                if (hasVisited[nextPt.cup[0]][nextPt.cup[1]][nextPt.cup[2]])
                    continue;

                for (int i = 0; i < 3; i++)
                {
                    if (nextPt.cup[i] == (cupSize[0] >> 1))
                    {
                        if (nextPt.cup[(i - 1 < 0 ? 2 : i - 1)] == 0)
                            return nextPt.step;
                        else
                            return nextPt.step + 1;
                    }
                }
                hasVisited[nextPt.cup[0]][nextPt.cup[1]][nextPt.cup[2]] = true;
                pq.push(nextPt);
            }
        }
    }
    return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> cupSize[0] >> cupSize[1] >> cupSize[2])
    {
        if (cupSize[0] == 0 && cupSize[1] == 0 && cupSize[2] == 0)
            break;

        if (cupSize[0] & 1)
        {
            cout << "NO" << endl;
            continue;
        }

        Node startPt = {cupSize[0], 0, 0, 0};
        int ans = bfs(startPt);
        if (ans == -1)
        {
            cout << "NO" << endl;
        }
        else
        {
            cout << ans << endl;
        }
    }

    return 0;
}

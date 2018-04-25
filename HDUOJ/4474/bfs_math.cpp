#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <functional>
#include <iterator>
#define SIZE 10010
using namespace std;

int path[SIZE], pre[SIZE];
int ansArr[SIZE];
bool isBanned[10], hasVisited[SIZE];

bool bfs(int n)
{
    memset(hasVisited, false, sizeof(hasVisited));

    queue<int> q;
    q.push(0);

    while (!q.empty())
    {
        int cntRemainder = q.front();
        q.pop();

        for (int i = 0; i < 10; i++)
        {
            if (isBanned[i] || (cntRemainder == 0 && i == 0))
                continue;

            int nextRemainder = (cntRemainder * 10 + i) % n;

            if (hasVisited[nextRemainder])
                continue;
            hasVisited[nextRemainder] = true;

            path[nextRemainder] = i;
            pre[nextRemainder] = cntRemainder;

            if (nextRemainder == 0)
                return true;

            q.push(nextRemainder);
        }
    }

    return false;
}

void printAns()
{
    int ansPt = 0;
    for (int i = 0; (ansPt == 0 || i != 0); i = pre[i])
    {
        ansArr[ansPt++] = path[i];
    }

    for (int i = ansPt - 1; i >= 0; i--)
    {
        cout << ansArr[i];
    }
    cout << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    int n, m, casePt = 0;
    while (cin >> n >> m)
    {
        memset(isBanned, false, sizeof(isBanned));
        for (int i = 0; i < m; i++)
        {
            int cnt;
            cin >> cnt;
            isBanned[cnt] = true;
        }

        cout << "Case " << ++casePt << ": ";
        if (!bfs(n))
            cout << -1 << endl;
        else
            printAns();
    }
    return 0;
}
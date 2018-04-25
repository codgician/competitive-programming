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
#define SIZE 1001
using namespace std;

char oprArr[4] = {'+', '-', '*', '%'};
int path[SIZE], pre[SIZE];
int ansArr[3][SIZE];
bool hasVisited[SIZE];

int n, k, m;

int getMod(int a, int b)
{
    if (a < 0)
        return b - (-a) % b;
    else
        return a % b;
}

int getNextRemainder(int oprType, int cnt)
{
    if (oprType == 0)
    {
        return (getMod(cnt, k) + getMod(m, k)) % k;
    }
    else if (oprType == 1)
    {
        int tmp = getMod(cnt, k) - getMod(m, k);
        return getMod(tmp, k);
    }
    else if (oprType == 2)
    {
        return (getMod(cnt, k) * getMod(m, k)) % k;
    }
    else
    {
        return getMod(cnt, m) % k;
    }
}

bool bfs(int startRemainder)
{
    memset(hasVisited, false, sizeof(hasVisited));
    queue<int> q;
    int endRemainder = getMod(n + 1, k);
    if (startRemainder == endRemainder)
        return true;

    q.push(startRemainder);
    hasVisited[startRemainder] = true;

    while (!q.empty())
    {
        int cntRemainder = q.front();
        q.pop();

        for (int i = 0; i < 3; i++)
        {
            int nextRemainder = getNextRemainder(i, cntRemainder);

            if (hasVisited[nextRemainder])
                continue;
            hasVisited[nextRemainder] = true;

            path[nextRemainder] = i;
            pre[nextRemainder] = cntRemainder;

            if (nextRemainder == endRemainder)
            {
                return true;
            }

            q.push(nextRemainder);
        }
    }

    return false;
}

int storeAns(int ansId, int startRemainder)
{
    int ansPt = 0;
    for (int i = getMod(n + 1, k); i != startRemainder; i = pre[i])
    {
        ansArr[ansId][ansPt++] = path[i];
    }

    if (ansId == 1)
    {
        ansArr[ansId][ansPt++] = 3;
    }
    else if (ansId == 2)
    {
        ansArr[ansId][ansPt++] = 3;
        ansArr[ansId][ansPt++] = 2;
    }

    return ansPt;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> n >> k >> m)
    {
        if (n == 0 && k == 0 && m == 0)
            break;

        int ans = INT_MAX, ansId = -1;
        int startRemainder = getMod(n, k);
        if (bfs(startRemainder))
        {
            int cntAns = storeAns(0, startRemainder);
            if (cntAns < ans)
            {
                ans = cntAns;
                ansId = 0;
            }
        }

        startRemainder = getMod(n, m) % k;
        if (bfs(startRemainder))
        {
            int cntAns = storeAns(1, startRemainder);
            if (cntAns < ans)
            {
                ans = cntAns;
                ansId = 1;
            }
        }

        startRemainder = 0;
        if (bfs(startRemainder))
        {
            int cntAns = storeAns(2, startRemainder);
            if (cntAns < ans)
            {
                ans = cntAns;
                ansId = 2;
            }
        }

        if (ansId == -1)
        {
            cout << 0 << endl;
        }
        else
        {
            cout << ans << endl;
            for (int i = ans - 1; i >= 0; i--)
            {
                cout << oprArr[ansArr[ansId][i]];
            }
            cout << endl;
        }

    }
    return 0;
}
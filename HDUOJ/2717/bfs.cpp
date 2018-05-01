#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
#define SIZE 100001
using namespace std;

bool hasVisited[SIZE];

bool canMove(int pt)
{
    if (pt < 0 || pt >= SIZE || hasVisited[pt])
        return false;
    return true;
}

int bfs(int startPt, int endPt)
{
    memset(hasVisited, false, sizeof(hasVisited));
    queue<pair<int, int> > q;
    q.push(make_pair(startPt, 0));
    hasVisited[startPt] = true;

    while (!q.empty())
    {
        pair<int, int> cntNode = q.front();
        q.pop();

        if (cntNode.first == endPt)
            return cntNode.second;

        for (int i = 0; i < 3; i++)
        {
            pair<int, int> nextNode;
            nextNode.second = cntNode.second + 1;

            if (i == 0)
                nextNode.first = cntNode.first - 1;
            else if (i == 1)
                nextNode.first = cntNode.first + 1;
            else if (i == 2)
                nextNode.first = cntNode.first << 1;

            if (!canMove(nextNode.first))
                continue;

            hasVisited[nextNode.first] = true;
            q.push(nextNode);
        }
    }

    return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    int startPt, endPt;
    while (cin >> startPt >> endPt)
    {
        int ans = bfs(startPt, endPt);
        cout << ans << endl;
    }
    return 0;
}
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
#define SIZE 201
using namespace std;

typedef struct _Node
{
    int pt;
    int step;
} Node;

int arr[SIZE];
bool hasVisited[SIZE];

int floorNum;

int bfs(int startPt, int endPt)
{
    memset(hasVisited, false, sizeof(hasVisited));
    queue<Node> q;

    Node startNode;
    startNode.pt = startPt;
    startNode.step = 0;
    q.push(startNode);
    hasVisited[startPt] = true;

    while (!q.empty())
    {
        Node cntNode = q.front();
        q.pop();

        if (cntNode.pt == endPt)
            return cntNode.step;

        for (int i = -1; i < 2; i += 2)
        {
            Node nextNode;
            nextNode.pt = cntNode.pt + arr[cntNode.pt] * i;
            nextNode.step = cntNode.step + 1;

            if (nextNode.pt < 0 || nextNode.pt >= floorNum || hasVisited[nextNode.pt])
                continue;

            hasVisited[nextNode.pt] = true;
            q.push(nextNode);
        }
    }

    return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> floorNum)
    {
        if (floorNum == 0)
            break;

        int startPt, endPt;
        cin >> startPt >> endPt;
        startPt--;
        endPt--;
        for (int i = 0; i < floorNum; i++)
        {
            cin >> arr[i];
        }

        int ans = bfs(startPt, endPt);
        cout << ans << endl;
    }
    return 0;
}
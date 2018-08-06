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

#define SIZE 101 

typedef struct _Edge
{
    int from;
    int to;
    int len;
    char color;
} Edge;

Edge arr[SIZE];
bool hasVisited[SIZE];

int parent[SIZE];

int redGreen[SIZE], blueGreen[SIZE];

int vertexNum, edgeNum;

void init()
{
    for (int i = 0; i < vertexNum; i++)
    {
        parent[i] = i;
    }
}

int getParent(int n)
{
    if (parent[n] == n)
        return n;
    else
    {
        parent[n] = getParent(parent[n]);
        return parent[n];
    }
}

bool mergeNode(int fst, int snd)
{
    int fstParent = getParent(fst);
    int sndParent = getParent(snd);

    if (fstParent > sndParent)
        swap(fstParent, sndParent);

    if (fstParent != sndParent)
    {
        parent[sndParent] = fstParent;
        return true;
    }

    return false;
}

bool check()
{
    for (int i = 1; i < vertexNum; i++)
    {
        if (getParent(i) != getParent(0))
        {
            return false;
        }
    }
    return true;
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
        cin >> vertexNum >> edgeNum;
        for (int i = 0; i < edgeNum; i++)
        {
            cin >> arr[i].from >> arr[i].to >> arr[i].len >> arr[i].color;
            arr[i].from--;
            arr[i].to--;
            redGreen[i] = INT_MAX;
            blueGreen[i] = INT_MAX;
        }

        sort(arr + 0, arr + edgeNum, [](Edge & fst, Edge & snd) {
            return fst.len < snd.len;
        });

        int ans;

        // Red-Green
        memset(hasVisited, false, sizeof(hasVisited));
        ans = 0;
        init();
        for (int i = 0; i < edgeNum; i++)
        {
            if (arr[i].color == 'B')
                continue;

            if (mergeNode(arr[i].from, arr[i].to))
            {
                hasVisited[i] = true;
                ans += arr[i].len;
            }
        }

        if (check())
        {
            redGreen[vertexNum - 2] = ans;

            int cntNum = vertexNum - 1;

            for (int i = 0; i < edgeNum; i++)
            {
                if (hasVisited[i])
                    continue;
                redGreen[cntNum] = redGreen[cntNum - 1] + arr[i].len;
                cntNum++;
            }
        }

        // Blue-Green
        memset(hasVisited, false, sizeof(hasVisited));
        ans = 0;
        init();
        for (int i = 0; i < edgeNum; i++)
        {
            if (arr[i].color == 'R')
                continue;

            if (mergeNode(arr[i].from, arr[i].to))
            {
                hasVisited[i] = true;
                ans += arr[i].len;
            }
        }

        if (check())
        {
            blueGreen[vertexNum - 2] = ans;

            int cntNum = vertexNum - 1;

            for (int i = 0; i < edgeNum; i++)
            {
                if (hasVisited[i])
                    continue;
                blueGreen[cntNum] = blueGreen[cntNum - 1] + arr[i].len;
                cntNum++;
            }
        }

        cout << "Case #" << t << ":" << endl;
        for (int i = 0; i < edgeNum; i++)
        {
            int cnt = min(redGreen[i], blueGreen[i]);
            if (cnt == INT_MAX)
                cout << -1 << endl;
            else
                cout << cnt << endl;
        }
    }
    return 0;
}
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

#define SIZE 200100

int deg[SIZE];
int parent[SIZE];
bool hasVisited[SIZE];

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

void mergeNode(int fst, int snd)
{
    int fstParent = getParent(fst);
    int sndParent = getParent(snd);

    if (fstParent != sndParent)
    {
        parent[sndParent] = fstParent;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int vertexNum, edgeNum, k;
        cin >> vertexNum >> edgeNum >> k;

        for (int i = 0; i < vertexNum; i++)
        {
            deg[i] = 0;
            parent[i] = i;
            hasVisited[i] = false;
        }

        int maxDeg = 0, maxDegPt = 0;
        for (int i = 0; i < edgeNum; i++)
        {
            int from, to;
            cin >> from >> to;
            mergeNode(from, to);
            deg[from]++;
            deg[to]++;

            if (deg[from] > maxDeg)
            {
                maxDeg = deg[from];
                maxDegPt = from;
            }
            if (deg[to] > maxDeg)
            {
                maxDeg = deg[to];
                maxDegPt = to;
            }
        }

        int sccNum = 0, maxDegSccSize = 0;
        for (int i = 0; i < vertexNum; i++)
        {
            int cntParent = getParent(i);

            if (!hasVisited[cntParent])
            {
                sccNum++;
                hasVisited[cntParent] = true;
            }

            if (cntParent == getParent(maxDegPt))
                maxDegSccSize++;
        }

        int ans = maxDeg + sccNum - 1;
        int maxAvailable = vertexNum - ans - 1;

        ans += min(maxAvailable, k);
        cout << ans << endl;
    }
    return 0;
}
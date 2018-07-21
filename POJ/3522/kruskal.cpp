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

#define VERTEX_SIZE 110
#define EDGE_SIZE 12100

typedef struct _Edge
{
    int from;
    int to;
    int len;
} Edge;

Edge arr[EDGE_SIZE];
int parent[VERTEX_SIZE];
int vertexNum, edgeNum;

bool cmp(Edge fst, Edge snd)
{
    return fst.len < snd.len;
}

int getParent(int n)
{
    if (parent[n] == n)
    {
        return n;
    }
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

    if (fstParent != sndParent)
    {
        parent[sndParent] = fstParent;
        return true;
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> vertexNum >> edgeNum)
    {
        if (vertexNum == 0 && edgeNum == 0)
            break;

        for (int i = 0; i < edgeNum; i++)
        {
            cin >> arr[i].from >> arr[i].to >> arr[i].len;
            arr[i].from--;
            arr[i].to--;
        }
        
        sort(arr + 0, arr + edgeNum, cmp);

        int ans = INT_MAX;
        for (int startPt = 0; startPt < edgeNum; startPt++)
        {
            for (int i = 0; i < vertexNum; i++)
                parent[i] = i;

            int num = 0, minLen = INT_MAX, maxLen = -1;
            for (int i = startPt; i < edgeNum && num < vertexNum; i++)
            {
                if (mergeNode(arr[i].from, arr[i].to))
                {
                    num++;
                    minLen = min(minLen, arr[i].len);
                    maxLen = max(maxLen, arr[i].len);
                }
            }

            if (num < vertexNum - 1)
                break;
            ans = min(ans, maxLen - minLen);
        }

        if (ans == INT_MAX)
            cout << -1 << endl;
        else
            cout << ans << endl;
    }
    return 0;
}

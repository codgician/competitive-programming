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
#define EDGE_SIZE 100100
#define VERTEX_SIZE 50010
using namespace std;

typedef struct _Edge
{
    int to;
    int cost;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;

int dfn[VERTEX_SIZE], low[VERTEX_SIZE], cntTime;
bool isInStack[VERTEX_SIZE];
stack<int> st;

int sccId[VERTEX_SIZE];
int sccNum;

int minInCost[VERTEX_SIZE];

void addEdge(int from, int to, int cost)
{
    arr[arrPt] = {to, cost, head[from]};
    head[from] = arrPt++;
}

void tarjan(int cntPt)
{
    dfn[cntPt] = cntTime;
    low[cntPt] = cntTime;
    cntTime++;

    st.push(cntPt);
    isInStack[cntPt] = true;

    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;

        if (dfn[nextPt] == -1)
        {
            tarjan(nextPt);
            low[cntPt] = min(low[cntPt], low[nextPt]);
        }
        else if (isInStack[nextPt])
        {
            low[cntPt] = min(low[cntPt], dfn[nextPt]);
        }
    }

    if (dfn[cntPt] == low[cntPt])
    {
        while (true)
        {
            int cntTop = st.top();
            sccId[cntTop] = sccNum;
            st.pop();
            isInStack[cntTop] = false;

            if (cntTop == cntPt)
                break;
        }
        sccNum++;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int vertexNum, edgeNum;
    while (cin >> vertexNum >> edgeNum)
    {
        memset(head, -1, sizeof(head));
        memset(dfn, -1, sizeof(dfn));
        memset(isInStack, false, sizeof(isInStack));
        arrPt = 0;
        cntTime = 0;
        sccNum = 0;

        for (int i = 0; i < edgeNum; i++)
        {
            int from, to, cost;
            cin >> from >> to >> cost;
            addEdge(from, to, cost);
        }

        for (int i = 0; i < vertexNum; i++)
        {
            if (dfn[i] == -1)
            {
                tarjan(i);
            }
        }

        for (int i = 0; i < sccNum; i++)
        {
            minInCost[i] = INT_MAX;
        }

        for (int i = 0; i < vertexNum; i++)
        {
            for (int j = head[i]; j != -1; j = arr[j].next)
            {
                int nextPt = arr[j].to;
                if (sccId[i] != sccId[nextPt])
                {
                    minInCost[sccId[nextPt]] = min(minInCost[sccId[nextPt]], arr[j].cost); 
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < sccNum; i++)
        {
            if (minInCost[i] != INT_MAX)
            {
                ans += minInCost[i];
            }
        }
        cout << ans << endl;
    }
    return 0;
}
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
#define EDGE_SIZE 4010
#define VERTEX_SIZE 2010
using namespace std;

typedef struct _Edge
{
    int to;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt, compArrPt;
int dfn[VERTEX_SIZE], low[VERTEX_SIZE], sccId[VERTEX_SIZE], cntTime;
bool inStack[VERTEX_SIZE];
int costArr[VERTEX_SIZE], sccMinCost[VERTEX_SIZE];

int compInDegree[VERTEX_SIZE];

vector<int> sccArr[VERTEX_SIZE];
stack<int> st;

int sccNum, costVal;

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void addCompEdge(int from, int to)
{
    compInDegree[to]++;
}

void tarjan(int cntPt)
{
    dfn[cntPt] = cntTime;
    low[cntPt] = cntTime;
    cntTime++;

    st.push(cntPt);
    inStack[cntPt] = true;

    int edgePt = head[cntPt];
    while (edgePt != -1)
    {
        if (dfn[arr[edgePt].to] == -1)
        {
            tarjan(arr[edgePt].to);
            low[cntPt] = min(low[cntPt], low[arr[edgePt].to]);
        }
        else if (inStack[arr[edgePt].to])
        {
            low[cntPt] = min(low[cntPt], dfn[arr[edgePt].to]);
        }
        edgePt = arr[edgePt].next;
    }

    if (dfn[cntPt] == low[cntPt])
    {
        sccMinCost[sccNum] = INT_MAX;
        while (true)
        {
            int cntTop = st.top();
            st.pop();
            sccMinCost[sccNum] = min(sccMinCost[sccNum], costArr[cntTop]);
            inStack[cntTop] = false;
            sccArr[sccNum].push_back(cntTop);
            sccId[cntTop] = sccNum;
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
        memset(inStack, false, sizeof(inStack));
        memset(compInDegree, 0, sizeof(compInDegree));
        arrPt = 0;
        sccNum = 0;

        for (int i = 0; i < vertexNum; i++)
        {
            cin >> costArr[i];
            sccArr[i].clear();
        }
        for (int i = 0; i < edgeNum; i++)
        {
            int from, to;
            cin >> from >> to;
            from--;
            to--;
            addEdge(from, to);
        }

        for (int i = 0; i < vertexNum; i++)
        {
            if (dfn[i] == -1)
            {
                tarjan(i);
            }
        }

        for (int i = 0; i < vertexNum; i++)
        {
            int edgePt = head[i];
            while (edgePt != -1)
            {
                if (sccId[i] != sccId[arr[edgePt].to])
                    addCompEdge(sccId[i], sccId[arr[edgePt].to]);
                edgePt = arr[edgePt].next;
            }
        }

        int ans = 0, costAns = 0;
        for (int i = 0; i < sccNum; i++)
        {
            if (compInDegree[i] == 0)
            {
                ans++;
                costAns += sccMinCost[i];
            }
        }

        cout << ans << " " << costAns << endl;
    }
    return 0;
}

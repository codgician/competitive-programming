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

#define VERTEX_SIZE 100010
#define EDGE_SIZE 200020

typedef struct _Edge
{
    int to;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;

int dfn[VERTEX_SIZE], low[VERTEX_SIZE], cntTime;
bool inStack[VERTEX_SIZE];
stack<int> st;

int sccId[VERTEX_SIZE];
int sccNum;

int vertexNum, edgeNum;
int goldArr[VERTEX_SIZE];
int sccMinGold[VERTEX_SIZE];

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void tarjan(int cntPt)
{
    dfn[cntPt] = cntTime;
    low[cntPt] = cntTime;
    cntTime++;

    st.push(cntPt);
    inStack[cntPt] = true;

    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;

        if (dfn[nextPt] == -1)
        {
            tarjan(nextPt);
            low[cntPt] = min(low[cntPt], low[nextPt]);
        }
        else if (inStack[nextPt])
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
            inStack[cntTop] = false;

            if (cntTop == cntPt)
                break;
        }
        sccNum++;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    memset(dfn, -1, sizeof(dfn));
    memset(inStack, false, sizeof(inStack));
    arrPt = 0;
    cntTime = 0;
    sccNum = 0;

    cin >> vertexNum >> edgeNum;
    for (int i = 0; i < vertexNum; i++)
    {
        cin >> goldArr[i]; 
    }
    for (int i = 0; i < edgeNum; i++)
    {
        int from, to;
        cin >> from >> to;
        from--;
        to--;
        addEdge(from, to);
        addEdge(to, from);
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
        sccMinGold[i] = INT_MAX;
    }
    for (int i = 0; i < vertexNum; i++)
    {
        sccMinGold[sccId[i]] = min(sccMinGold[sccId[i]], goldArr[i]);
    }

    long long int ans = 0;
    for (int i = 0; i < sccNum; i++)
    {
        ans += sccMinGold[i];
    }
    cout << ans << endl;

    return 0;
}
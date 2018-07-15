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

#define VERTEX_SIZE 100100
#define EDGE_SIZE 200200

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

int sccId[VERTEX_SIZE], sccSize[VERTEX_SIZE];
int sccNum;

bool outDegNonZero[VERTEX_SIZE];

int updArr[VERTEX_SIZE];

int vertexNum;

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
            sccSize[sccNum]++;
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

    int serverNum, clientNum, hour;
    cin >> serverNum >> clientNum >> hour;
    for (int i = 0; i < serverNum; i++)
    {
        cin >> updArr[i];
    }

    vertexNum = serverNum;
    for (int i = 0; i < clientNum; i++)
    {
        int from, to;
        cin >> from >> to;
        from--;
        to--;

        if ((updArr[from] + 1) % hour == updArr[to])
            addEdge(from, to);
        if ((updArr[to] + 1) % hour == updArr[from])
            addEdge(to, from);
    }

    memset(sccSize, 0, sizeof(sccSize));
    for (int i = 0; i < vertexNum; i++)
    {
        if (dfn[i] == -1)
            tarjan(i);
    }

    memset(outDegNonZero, false, sizeof(outDegNonZero));
    for (int cntPt = 0; cntPt < vertexNum; cntPt++)
    {
        for (int i = head[cntPt]; i != -1; i = arr[i].next)
        {
            int nextPt = arr[i].to;
            if (sccId[cntPt] != sccId[nextPt])
            {
                outDegNonZero[sccId[cntPt]] = true;
                break;
            }
        }
    }

    int minSccSize = INT_MAX, minSccPt = -1;
    for (int i = 0; i < sccNum; i++)
    {
        if (!outDegNonZero[i] && sccSize[i] < minSccSize)
        {
            minSccSize = sccSize[i];
            minSccPt = i;
        }
    }

    cout << minSccSize << endl;
    bool isFirst = true;
    for (int i = 0; i < vertexNum; i++)
    {
        if (sccId[i] == minSccPt)
        {
            if (isFirst)
                isFirst = false;
            else
                cout << " ";
            cout << i + 1;
        }
    }
    cout << endl;
    return 0;
}
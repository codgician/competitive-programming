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
#define EDGE_SIZE 30100
#define VERTEX_SIZE 5010
using namespace std;

typedef struct
{
    int to;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;

int dfn[VERTEX_SIZE], low[VERTEX_SIZE], cntTime;
bool inStack[VERTEX_SIZE];

vector<int> sccArr[VERTEX_SIZE];
int sccId[VERTEX_SIZE], sccSize[VERTEX_SIZE];
stack<int> st;

Edge compArr[EDGE_SIZE];
int compHead[VERTEX_SIZE], compArrPt;

int inDegree[VERTEX_SIZE];
bool hasVisited[VERTEX_SIZE];

int ansArr[VERTEX_SIZE], ansPt;
int sccNum, maxNum;

map<pair<int, int>, bool> mp;

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void addCompEdge(int from, int to)
{
    if (mp.find(make_pair(from, to)) != mp.end())
        return;
    mp[make_pair(from, to)] = true;
    inDegree[to]++;
    compArr[compArrPt] = {to, compHead[from]};
    compHead[from] = compArrPt++;
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
        sccSize[sccNum] = 0;
        sccArr[sccNum].clear();
        while (true)
        {
            int stTop = st.top();
            st.pop();
            inStack[stTop] = false;
            sccSize[sccNum]++;

            sccArr[sccNum].push_back(stTop);
            sccId[stTop] = sccNum;

            if (stTop == cntPt)
                break;
        }
        sccNum++;
    }
}

void bfs(int startPt)
{
    memset(hasVisited, false, sizeof(hasVisited));
    queue<int> q;
    q.push(startPt);
    hasVisited[startPt] = true;
    int cntNum = sccSize[startPt] - 1;

    while (!q.empty())
    {
        int cntPt = q.front();
        q.pop();

        for (int i = compHead[cntPt]; i != -1 ; i = compArr[i].next)
        {
            int nextPt = compArr[i].to;

            if (hasVisited[nextPt])
                continue;

            cntNum += sccSize[nextPt];
            q.push(nextPt);
            hasVisited[nextPt] = true;
        }
    }

    if (cntNum > maxNum)
    {
        ansPt = 0;
        maxNum = cntNum;
        for (int i = 0; i < (int)sccArr[startPt].size(); i++)
        {
            ansArr[ansPt++] = sccArr[startPt][i];
        }
    }
    else if (cntNum == maxNum)
    {
        for (int i = 0; i < (int)sccArr[startPt].size(); i++)
        {
            ansArr[ansPt++] = sccArr[startPt][i];
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        mp.clear();
        while (!st.empty())
            st.pop();
        memset(head, -1, sizeof(head));
        memset(compHead, -1, sizeof(compHead));
        memset(dfn, -1, sizeof(dfn));
        memset(inStack, false, sizeof(inStack));
        memset(inDegree, 0, sizeof(inDegree));
        arrPt = 0;
        compArrPt = 0;
        cntTime = 0;
        maxNum = -1;
        sccNum = 0;

        int vertexNum, edgeNum;
        cin >> vertexNum >> edgeNum;
        for (int i = 0; i < edgeNum; i++)
        {
            int from, to;
            cin >> from >> to;
            addEdge(from, to);
        }

        for (int i = 0; i < vertexNum; i++)
        {
            if (dfn[i] == -1)
            {
                tarjan(i);
            }
        }

        cout << "Case " << t << ": ";
        if (sccNum == 1)
        {
            cout << vertexNum - 1 << endl;
            for (int i = 0; i < vertexNum; i++)
            {
                cout << i;
                if (i < vertexNum - 1)
                    cout << " ";
                else
                    cout << endl;
            }
            continue;
        }

        for (int i = 0; i < vertexNum; i++)
        {
            for (int j = head[i]; j != -1; j = arr[j].next)
            {
                int nextPt = arr[j].to;
                if (sccId[i] != sccId[nextPt])
                {
                    addCompEdge(sccId[nextPt], sccId[i]);        // Reverse!
                }
            }
        }

        for (int i = 0; i < sccNum; i++)
        {
            if (inDegree[i] == 0)
            {
                bfs(i);
            }
        }

        cout << maxNum << endl;
        sort(ansArr + 0, ansArr + ansPt);
        for (int i = 0; i < ansPt; i++)
        {
            cout << ansArr[i];
            if (i < ansPt - 1)
                cout << " ";
            else
                cout << endl;
        }
    }
    return 0;
}
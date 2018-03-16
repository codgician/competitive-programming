#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <functional>
#include <iterator>
#define VERTEX_SIZE 610
#define EDGE_SIZE 165000
using namespace std;

typedef struct _Edge
{
    int to;
    int capacity;
    int next;
} Edge;

typedef struct _Task
{
    int startTime;
    int endTime;
} Task;

Edge arr[EDGE_SIZE];
Task taskArr[VERTEX_SIZE];
int head[VERTEX_SIZE], arrPt;
int depth[VERTEX_SIZE], lastVisitedEdge[VERTEX_SIZE];
int vertexNum;

set<int, less<int> > st;

void addEdge(int from, int to, int capacity)
{
    arr[arrPt] = {to, capacity, head[from]};
    head[from] = arrPt++;
    arr[arrPt] = {from, 0, head[to]};
    head[to] = arrPt++;
}

bool updateDepth(int startPt, int endPt)
{
    memset(depth, -1, sizeof(depth));
    queue<int> q;

    depth[startPt] = 0;
    q.push(startPt);

    while (!q.empty())
    {
        int cntPt = q.front();
        q.pop();

        int edgePt = head[cntPt];
        while (edgePt != -1)
        {
            if (depth[arr[edgePt].to] == -1 && arr[edgePt].capacity > 0)
            {
                depth[arr[edgePt].to] = depth[cntPt] + 1;
                if (arr[edgePt].to == endPt)
                    return true;
                q.push(arr[edgePt].to);
            }
            edgePt = arr[edgePt].next;
        }
    }
    return false;
}

int findAguPath(int cntPt, int endPt, int minCapacity)
{
    if (cntPt == endPt)
        return minCapacity;

    int cntFlow = 0;
    int &edgePt = lastVisitedEdge[cntPt];
    while (edgePt != -1)
    {
        if (depth[arr[edgePt].to] == depth[cntPt] + 1 && arr[edgePt].capacity > 0)
        {
            int flowInc = findAguPath(arr[edgePt].to, endPt, min(minCapacity - cntFlow, arr[edgePt].capacity));
            if (flowInc == 0)
            {
                depth[arr[edgePt].to] = -1;
            }
            else
            {
                arr[edgePt].capacity -= flowInc;
                arr[edgePt ^ 1].capacity += flowInc;
                cntFlow += flowInc;
                if (cntFlow == minCapacity)
                    break;
            }
        }
        edgePt = arr[edgePt].next;
    }
    return cntFlow;
}

int dinic(int startPt, int endPt)
{
    int ans = 0;
    while (updateDepth(startPt, endPt))
    {
        for (int i = 0; i < vertexNum; i++)
        {
            lastVisitedEdge[i] = head[i];
        }
        int flowInc = findAguPath(startPt, endPt, INT_MAX);
        if (flowInc == 0)
            break;
        ans += flowInc;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int customerNum, kebabProc;
    while (cin >> customerNum >> kebabProc)
    {
        arrPt = 0;
        memset(head, -1, sizeof(head));
        st.clear();

        int startPt = 0;
        int fullFlow = 0;
        for (int i = 0; i < customerNum; i++)
        {
            int startTime, demandNum, endTime, roastTime;
            cin >> startTime >> demandNum >> endTime >> roastTime;

            addEdge(startPt, i + 1, roastTime * demandNum);

            st.insert(startTime);
            st.insert(endTime);

            taskArr[i] = {startTime, endTime};

            fullFlow += roastTime * demandNum;
        }

        int endPt = customerNum + st.size();
        vertexNum = endPt + 1;

        set<int, less<int> >::iterator it = st.begin();
        for (int i = 0; i < st.size() - 1; i++)
        {
            int startTime = *(it++);
            int endTime = *it;

            for (int j = 0; j < customerNum; j++)
            {
                if (taskArr[j].startTime <= startTime && taskArr[j].endTime >= endTime)
                {
                    addEdge(j + 1, customerNum + i + 1, INT_MAX);
                }
            }

            addEdge(customerNum + i + 1, endPt, (endTime - startTime) * kebabProc);
        }

        int ans = dinic(startPt, endPt);
        if (ans == fullFlow)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}

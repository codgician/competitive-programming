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
#define EDGE_SIZE 200200
#define VERTEX_SIZE 10010
using namespace std;

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

int sccNum;

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
		sccNum++;
		while (true)
		{
			int cntTop = st.top();
			st.pop();
			inStack[cntTop] = false;
			if (cntTop == cntPt)
				break;
		}
	}
}

int main()
{
    ios::sync_with_stdio(false);
    int vertexNum, edgeNum;
    while (cin >> vertexNum >> edgeNum)
    {

    	if (vertexNum == 0 && edgeNum == 0)
    	{
    		break;
    	}

    	memset(head, -1, sizeof(head));
    	memset(dfn, -1, sizeof(dfn));
    	memset(inStack, false, sizeof(inStack));
    	arrPt = 0;
    	cntTime = 0;
    	sccNum = 0;

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

    	if (sccNum == 1)
    		cout << "Yes" << endl;
    	else
    		cout << "No" << endl;
    }
    return 0;
}

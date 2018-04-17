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
#define EDGE_SIZE 50100
#define VERTEX_SIZE 10010
using namespace std;

typedef struct
{
	int to;
	int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;

int dfn[VERTEX_SIZE], low[VERTEX_SIZE], cntTime;
bool isInStack[VERTEX_SIZE];
stack<int> st;

int sccId[VERTEX_SIZE], sccSize[VERTEX_SIZE];
int sccNum;

int outDeg[VERTEX_SIZE], compEdgeNum;

void addEdge(int from, int to)
{
	arr[arrPt] = {to, head[from]};
	head[from] = arrPt++;
}

void addCompEdge(int from, int to)
{
	outDeg[from]++;
	compEdgeNum++;
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
			sccSize[sccNum]++;
			isInStack[cntTop] = false;
			st.pop();

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
		while (!st.empty())
			st.pop();
		memset(head, -1, sizeof(head));
		memset(dfn, -1, sizeof(dfn));
		memset(isInStack, false, sizeof(isInStack));
		memset(outDeg, 0, sizeof(outDeg));
		memset(sccSize, 0, sizeof(sccSize));
		arrPt = 0;
		cntTime = 0;
		sccNum = 0;
		compEdgeNum = 0;

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
		{
			cout << vertexNum << endl;
			continue;
		}

		for (int i = 0; i < vertexNum; i++)
		{
			for (int j = head[i]; j != -1; j = arr[j].next)
			{
				int nextPt = arr[j].to;

				if (sccId[i] != sccId[nextPt])
				{
					addCompEdge(sccId[i], sccId[nextPt]);
				}
			}
		}

		int zeroOutDegNum = 0, lastZeroOutDegId = -1;
		for (int i = 0; i < sccNum; i++)
		{
			if (outDeg[i] == 0)
			{
				zeroOutDegNum++;
				lastZeroOutDegId = i;
			}
		}

		int ans;
		if (zeroOutDegNum == 1)
		{
			if (compEdgeNum < sccNum - 1)
			{
				ans = 0;
			}
			else
			{
				ans = sccSize[lastZeroOutDegId];
			}
		}
		else
		{
			ans = 0;
		}
		cout << ans << endl;
	}
	return 0;
}

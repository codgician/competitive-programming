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
#define VERTEX_SIZE 20010
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
stack<int> st;

int sccId[VERTEX_SIZE];

int sccNum;
bool hasInDeg[VERTEX_SIZE], hasOutDeg[VERTEX_SIZE];
int zeroInDegNum, zeroOutDegNum;

void addEdge(int from, int to)
{
	arr[arrPt] = {to, head[from]};
	head[from] = arrPt++;
}

void addCompEdge(int from, int to)
{
	if (!hasOutDeg[from])
	{
		zeroOutDegNum--;
		hasOutDeg[from] = true;
	}

	if (!hasInDeg[to])
	{
		zeroInDegNum--;
		hasInDeg[to] = true;
	}
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
	int caseNum;
	cin >> caseNum;
	while (caseNum--)
	{
		while (!st.empty())
			st.pop();
		memset(head, -1, sizeof(head));
		memset(dfn, -1, sizeof(dfn));
		memset(inStack, false, sizeof(inStack));
		arrPt = 0;
		cntTime = 0;
		sccNum = 0;

		int vertexNum, edgeNum;
		cin >> vertexNum >> edgeNum;
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
			cout << 0 << endl;
			continue;
		}

		memset(hasInDeg, false, sizeof(hasInDeg));
		memset(hasOutDeg, false, sizeof(hasOutDeg));
		zeroInDegNum = sccNum;
		zeroOutDegNum = sccNum;

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

		cout << max(zeroInDegNum, zeroOutDegNum) << endl;

	}
	return 0;
}
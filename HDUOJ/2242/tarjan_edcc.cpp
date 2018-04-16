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
#define EDGE_SIZE 40100
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

int edccId[VERTEX_SIZE], edccSize[VERTEX_SIZE], edccNum;

int roomCap[VERTEX_SIZE];
bool isBridge[EDGE_SIZE];
int bridgeNum;

Edge compArr[EDGE_SIZE];
int compHead[VERTEX_SIZE], compArrPt;

bool hasVisited[VERTEX_SIZE];
int capSum, ans;

void addEdge(int from, int to)
{
	arr[arrPt] = {to, head[from]};
	head[from] = arrPt++;
}

void addCompEdge(int from, int to)
{
	compArr[compArrPt] = {to, compHead[from]};
	compHead[from] = compArrPt++;
}

void tarjan(int cntPt, int edgeId)
{
	dfn[cntPt] = cntTime;
	low[cntPt] = cntTime;
	cntTime++;

	for (int i = head[cntPt]; i != -1; i = arr[i].next)
	{
		int nextPt = arr[i].to;
		if (dfn[nextPt] == -1)
		{
			tarjan(nextPt, i);
			low[cntPt] = min(low[cntPt], low[nextPt]);

			if (low[nextPt] > dfn[cntPt])
			{
				bridgeNum++;
				isBridge[i] = true;
				isBridge[i ^ 1] = true;
			}
		}
		else if (i != (edgeId ^ 1))
		{
			low[cntPt] = min(low[cntPt], dfn[nextPt]);
		}
	}
}

void dfs(int cntPt)
{
	edccId[cntPt] = edccNum;
	edccSize[edccNum] += roomCap[cntPt];
	for (int i = head[cntPt]; i != -1; i = arr[i].next)
	{
		int nextPt = arr[i].to;
		if (edccId[nextPt] > -1 || isBridge[i])
			continue;
		dfs(nextPt);
	}
}

int dfs2(int cntPt)
{
	hasVisited[cntPt] = true;
	int nowSum = edccSize[cntPt];
	for (int i = compHead[cntPt]; i != -1; i = compArr[i].next)
	{
		int nextPt = compArr[i].to;

		if (hasVisited[nextPt])
			continue;

		nowSum += dfs2(nextPt);
	}
	ans = min(ans, abs(capSum - (nowSum << 1)));
	return nowSum;
}

int main()
{
	int vertexNum, edgeNum;
	while (cin >> vertexNum >> edgeNum)
	{
		memset(head, -1, sizeof(head));
		memset(compHead, -1, sizeof(compHead));
		memset(dfn, -1, sizeof(dfn));
		memset(edccId, -1, sizeof(edccId));
		memset(edccSize, 0, sizeof(edccSize));
		memset(isBridge, false, sizeof(isBridge));
		memset(hasVisited, false, sizeof(hasVisited));
		arrPt = 0;
		compArrPt = 0;
		cntTime = 0;
		edccNum = 0;
		bridgeNum = 0;
		ans = INT_MAX;

		capSum = 0;
		for (int i = 0; i < vertexNum; i++)
		{
			cin >> roomCap[i];
			capSum += roomCap[i];
		}

		for (int i = 0; i < edgeNum; i++)
		{
			int from, to;
			cin >> from >> to;
			addEdge(from, to);
			addEdge(to, from);
		}

		for (int i = 0; i < vertexNum; i++)
		{
			if (dfn[i] == -1)
			{
				tarjan(i, 0);
			}
		}

		if (bridgeNum == 0)
		{
			cout << "impossible" << endl;
			continue;
		}

		for (int i = 0; i < vertexNum; i++)
		{
			if (edccId[i] == -1)
			{
				dfs(i);
				edccNum++;
			}
		}

		for (int i = 0; i < arrPt; i += 2)
		{
			int from = arr[i ^ 1].to;
			int to = arr[i].to;

			if (edccId[from] == edccId[to])
				continue;
			addCompEdge(edccId[from], edccId[to]);
			addCompEdge(edccId[to], edccId[from]);
		}

		dfs2(0);
		cout << ans << endl;
	}
	return 0;
}
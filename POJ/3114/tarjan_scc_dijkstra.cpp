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
#define VERTEX_SIZE 550
#define EDGE_SIZE 302501
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

int sccId[VERTEX_SIZE], sccNum;

Edge compArr[EDGE_SIZE];
int compHead[VERTEX_SIZE], compArrPt;

int dis[VERTEX_SIZE][VERTEX_SIZE];
bool isShortest[VERTEX_SIZE];

void addEdge(int from, int to, int cost)
{
	arr[arrPt] = {to, cost, head[from]};
	head[from] = arrPt++;
}

void addCompEdge(int from, int to, int cost)
{
	compArr[compArrPt] = {to, cost, compHead[from]};
	compHead[from] = compArrPt++;
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
			isInStack[cntTop] = false;
			st.pop();

			if (cntTop == cntPt)
				break;
		}
		sccNum++;
	}
}

void dijkstra(int startPt)
{
	memset(isShortest, false, sizeof(isShortest));
	for (int i = 0; i < sccNum; i++)
		dis[startPt][i] = INT_MAX;
	dis[startPt][startPt] = 0;

	priority_queue<pair<int, int> > pq;
	pq.push(make_pair(0, startPt));

	while (!pq.empty())
	{
		int cntPt = pq.top().second;
		pq.pop();

		if (isShortest[cntPt])
			continue;
		isShortest[cntPt] = true;

		for (int i = compHead[cntPt]; i != -1; i = compArr[i].next)
		{
			int nextPt = compArr[i].to;
			if (dis[startPt][cntPt] != INT_MAX && dis[startPt][nextPt] > dis[startPt][cntPt] + compArr[i].cost)
			{
				dis[startPt][nextPt] = dis[startPt][cntPt] + compArr[i].cost;
				pq.push(make_pair(-dis[startPt][nextPt], nextPt));
			}
		}
	}
}

int main()
{
	int vertexNum, edgeNum;
	while (scanf("%d%d", &vertexNum, &edgeNum) != EOF)
	{
		if (vertexNum == 0)
			break;

		while (!st.empty())
			st.pop();
		memset(head, -1, sizeof(head));
		memset(compHead, -1, sizeof(compHead));
		memset(dfn, -1, sizeof(dfn));
		memset(isInStack, false, sizeof(isInStack));
		arrPt = 0;
		compArrPt = 0;
		cntTime = 0;
		sccNum = 0;

		for (int i = 0; i < edgeNum; i++)
		{
			int from, to, cost;
			scanf("%d%d%d", &from, &to, &cost);
			from--;
			to--;
			addEdge(from, to, cost);
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
			for (int j = head[i]; j != -1; j = arr[j].next)
			{
				int nextPt = arr[j].to;

				if (sccId[i] != sccId[nextPt])
				{
					addCompEdge(sccId[i], sccId[nextPt], arr[j].cost);
				}
			}
		}

		for (int i = 0; i < sccNum; i++)
		{
			dijkstra(i);
		}

		int qNum;
		scanf("%d", &qNum);
		while (qNum--)
		{
			int from, to;
			scanf("%d%d", &from, &to);
			from--;
			to--;

			if (sccId[from] == sccId[to])
			{
				printf("0\n");
			}
			else
			{
				int fst = sccId[from];
				int snd = sccId[to];

				if (dis[fst][snd] == INT_MAX)
				{
					printf("Nao e possivel entregar a carta\n");
				}
				else
				{
					printf("%d\n", dis[fst][snd]);
				}
			}
		}
		printf("\n");
	}
	return 0;
}

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

#define VERTEX_SIZE 1010
#define EDGE_SIZE 10010

typedef struct _Edge
{
	int to;
	int len;
	int next;
} Edge;

Edge arr[2][EDGE_SIZE];
int head[2][VERTEX_SIZE], arrPt[2];

int dis[VERTEX_SIZE];
bool isShortest[VERTEX_SIZE];

typedef struct _Node
{
	int pt;
	int dis;

	bool operator < (const struct _Node & snd) const
	{
		return dis > snd.dis;
	}
} Node;

int vertexNum, edgeNum;
int disLim;

void addEdge(int id, int from, int to, int len)
{
	arr[id][arrPt[id]] = {to, len, head[id][from]};
	head[id][from] = arrPt[id]++;
}

void dijkstra(int startPt)
{
	for (int i = 0; i < vertexNum; i++)
	{
		dis[i] = INT_MAX;
		isShortest[i] = false; 
	}

	priority_queue<Node> pq;
	dis[startPt] = 0;
	pq.push(Node{startPt, 0});

	while (!pq.empty())
	{
		Node cntNode = pq.top();
		pq.pop();
		isShortest[cntNode.pt] = true;

		for (int i = head[0][cntNode.pt]; i != -1; i = arr[0][i].next)
		{
			int nextPt = arr[0][i].to;
			int len = arr[0][i].len;
			if (isShortest[nextPt])
				continue;

			if (dis[cntNode.pt] != INT_MAX && dis[nextPt] >= dis[cntNode.pt] + len)
			{
				dis[nextPt] = dis[cntNode.pt] + len;
				pq.push(Node{nextPt, dis[nextPt]});
			}
		}
	}
}

int AStar(int startPt, int endPt, int k)
{
	if (dis[startPt] == INT_MAX)
		return -1;

	priority_queue<Node> pq;
	pq.push(Node{startPt, 0 + dis[startPt]});

	int cntTimes = 0;
	while (!pq.empty())
	{
		Node cntNode = pq.top();
		pq.pop();

		if (cntNode.pt == endPt)
		{
			cntTimes++;
			if (cntNode.dis > disLim)
				return -1;
			if (cntTimes == k)
				return cntNode.dis;
		}

		for (int i = head[1][cntNode.pt]; i != -1; i = arr[1][i].next)
		{
			int nextPt = arr[1][i].to;
			int len = arr[1][i].len;
			if (len > disLim)
				continue;
			pq.push(Node{nextPt, cntNode.dis - dis[cntNode.pt] + len + dis[nextPt]});
		}
	}

	return -1;
}

int main()
{
    while (scanf("%d%d", &vertexNum, &edgeNum) != EOF)
    {
    	memset(head, -1, sizeof(head));
    	memset(arrPt, 0, sizeof(arrPt));

    	int startPt, endPt, k;
    	scanf("%d%d%d%d", &startPt, &endPt, &k, &disLim);
    	startPt--;
    	endPt--;

    	for (int i = 0; i < edgeNum; i++)
    	{
    		int from, to, len;
    		scanf("%d%d%d", &from, &to, &len);
    		from--;
    		to--;
    		addEdge(1, from, to, len);
    		addEdge(0, to, from, len);
    	}

    	dijkstra(endPt);

    	int ret = AStar(startPt, endPt, k);
	    if (ret == -1 || ret > disLim)
	    	puts("Whitesnake!");
	    else
	    	puts("yareyaredawa");
    }
    return 0;
}
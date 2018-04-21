#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <functional>
#include <iterator>
#define VERTEX_NUM 101
#define EDGE_NUM 202
using namespace std;

typedef struct _Edge
{
	int to;
	int len;
	int next;
} Edge;

Edge arr[EDGE_NUM];
int head[VERTEX_NUM], arrPt;

int dis[VERTEX_NUM], cnt[VERTEX_NUM];
bool isInQueue[VERTEX_NUM];

int vertexNum;

void addEdge(int from, int to, int len)
{
	arr[arrPt] = {to, len, head[from]};
	head[from] = arrPt++;
}

bool spfa()
{
	memset(isInQueue, false, sizeof(isInQueue));
	for (int i = 0; i < vertexNum; i++)
		dis[i] = INT_MAX;
	
	queue<int> q;
	for (int i = 0; i < vertexNum; i++)
	{
		q.push(i);
		cnt[i] = 0;
		dis[i] = 0;
		isInQueue[i] = true;
	}
	
	while (!q.empty())
	{
		int cntPt = q.front();
		q.pop();
		isInQueue[cntPt] = false;

		for (int i = head[cntPt]; i != -1; i = arr[i].next)
		{
			int nextPt = arr[i].to;
			if (dis[cntPt] != INT_MAX && dis[nextPt] > dis[cntPt] + arr[i].len)
			{
				dis[nextPt] = dis[cntPt] + arr[i].len;
				cnt[nextPt] = cnt[cntPt] + 1;

				if (cnt[nextPt] >= vertexNum)
				{
					return false;
				}

				if (!isInQueue[nextPt])
				{
					q.push(nextPt);
					isInQueue[nextPt] = true;
				}
			}
		}
	}

	return true;
}

int main()
{
	ios::sync_with_stdio(false);
	int edgeNum;
	while (cin >> vertexNum >> edgeNum)
	{
		if (vertexNum == 0 && edgeNum == 0)
			break;

		memset(head, -1, sizeof(head));
		arrPt = 0;
		
		for (int i = 0; i < edgeNum; i++)
		{
			int from, to;
			cin >> from >> to;
			addEdge(from, to, -1);
		}

		if (spfa())
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}
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
#define VERTEX_NUM 50010
#define EDGE_NUM 150030
using namespace std;

typedef struct _Edge
{
	int to;
	int len;
	int next;
} Edge;

Edge arr[EDGE_NUM];
int head[VERTEX_NUM], arrPt;

int dis[VERTEX_NUM];
bool isInQueue[VERTEX_NUM];

int vertexNum;

void addEdge(int from, int to, int len)
{
	arr[arrPt] = {to, len, head[from]};
	head[from] = arrPt++;
}

void spfa(int startPt)
{
	memset(isInQueue, false, sizeof(isInQueue));
	for (int i = 0; i < vertexNum; i++)
		dis[i] = INT_MAX;
	
	queue<int> q;
	q.push(startPt);
	dis[startPt] = 0;
	isInQueue[startPt] = true;

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
				if (!isInQueue[nextPt])
				{
					q.push(nextPt);
					isInQueue[nextPt] = true;
				}
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	int num;
	while (cin >> num)
	{
		memset(head, -1, sizeof(head));
		arrPt = 0;

		int minLeftPt = INT_MAX, maxRightPt = INT_MIN;
		for (int i = 0; i < num; i++)
		{
			int leftPt, rightPt, cntNum;
			cin >> leftPt >> rightPt >> cntNum;
			leftPt++;
			rightPt++;
			minLeftPt = min(minLeftPt, leftPt);
			maxRightPt = max(maxRightPt, rightPt);
			addEdge(rightPt, leftPt - 1, -cntNum);
		}

		for (int i = minLeftPt; i <= maxRightPt; i++)
		{
			addEdge(i, i - 1, 0);
			addEdge(i - 1, i, 1);
		}

		vertexNum = maxRightPt + 1;
		spfa(maxRightPt);

		cout << -dis[minLeftPt - 1] << endl;
	}
	return 0;
}
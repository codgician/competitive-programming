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
#define VERTEX_SIZE 101
#define EDGE_SIZE 10101
using namespace std;

typedef struct _Edge
{
	int to;
	int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int vertexNum;

int dis[VERTEX_SIZE], visitTimes[VERTEX_SIZE];
bool isInQueue[VERTEX_SIZE];

int valueArr[VERTEX_SIZE];

void addEdge(int from, int to)
{
	arr[arrPt] = {to, head[from]};
	head[from] = arrPt++;
}

bool spfa(int startPt, int endPt)
{
	memset(isInQueue, false, sizeof(isInQueue));
	memset(visitTimes, 0, sizeof(visitTimes));
	for (int i = 0; i < vertexNum; i++)
		dis[i] = INT_MAX;
	dis[startPt] = -100;
	visitTimes[startPt] = 0;

	queue<int> q;
	q.push(startPt);
	isInQueue[startPt] = true;

	while (!q.empty())
	{
		int cntPt = q.front();
		q.pop();
		isInQueue[cntPt] = false;
		visitTimes[cntPt]++;

		if (visitTimes[cntPt] >= vertexNum + 1)
		{
			dis[cntPt] = -10201;
		}
		else if (visitTimes[cntPt] >= vertexNum + 2)
		{
			continue;
		}

		for (int i = head[cntPt]; i != -1; i = arr[i].next)
		{
			int nextPt = arr[i].to;

			if (visitTimes[cntPt] >= vertexNum + 2)
			{
				continue;
			}

			if (dis[cntPt] != INT_MAX && dis[cntPt] + valueArr[nextPt] < 0 && dis[nextPt] > dis[cntPt] + valueArr[nextPt])
			{
				dis[nextPt] = dis[cntPt] + valueArr[nextPt];

				if (dis[endPt] < 0)
				{
					return true;
				}

				if (!isInQueue[nextPt])
				{
					q.push(nextPt);
					isInQueue[nextPt] = true;
				}
			}
		} 
	}

	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	while (cin >> vertexNum)
	{
		if (vertexNum < 0)
			break;

		memset(head, -1, sizeof(head));
		arrPt = 0;
		for (int i = 0; i < vertexNum; i++)
		{
			int outNum;
			cin >> valueArr[i] >> outNum;
			valueArr[i] *= -1;
			for (int j = 0; j < outNum; j++)
			{
				int cnt;
				cin >> cnt;
				cnt--;
				addEdge(i, cnt);
			}
		}

		if (spfa(0, vertexNum - 1))
			cout << "winnable" << endl;
		else
			cout << "hopeless" << endl;
	}
	return 0;
}

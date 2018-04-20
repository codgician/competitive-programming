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
#define VERTEX_NUM 25
#define EDGE_NUM 101
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

int needArr[VERTEX_NUM], timeNum[VERTEX_NUM];

int vertexNum;

void addEdge(int from, int to, int len)
{
	arr[arrPt] = {to, len, head[from]};
	head[from] = arrPt++;
}

bool spfa(int startPt)
{
	memset(isInQueue, false, sizeof(isInQueue));
	for (int i = 0; i < vertexNum; i++)
		dis[i] = INT_MAX;
	
	queue<int> q;
	q.push(startPt);
	dis[startPt] = 0;
	cnt[startPt] = 0;
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

bool check(int s24)
{
	memset(head, -1, sizeof(head));
	arrPt = 0;

	for (int i = 1; i <= 8; i++)
	{
		addEdge(i, i + 16, s24 - needArr[i]);
	}
	for (int i = 9; i <= 24; i++)
	{
		addEdge(i, i - 8, -needArr[i]);
	}

	for (int i = 1; i <= 24; i++)
	{
		addEdge(i - 1, i, timeNum[i]);
		addEdge(i, i - 1, 0);
	}

	addEdge(24, 0, -s24);

	vertexNum = 25;
	return spfa(24);
}

int main()
{
	ios::sync_with_stdio(false);
	int caseNum;
	cin >> caseNum;
	while (caseNum--)
	{
		needArr[0] = 0;
		for (int i = 1; i <= 24; i++)
		{
			cin >> needArr[i];
		}

		memset(timeNum, 0, sizeof(timeNum));
		int appNum;
		cin >> appNum;
		timeNum[0] = 0;
		for (int i = 0; i < appNum; i++)
		{
			int cntTime;
			cin >> cntTime;
			cntTime++;
			timeNum[cntTime]++;
		}
		
		int leftPt = 0, rightPt = appNum, ans = -1;
		while (leftPt <= rightPt)
		{
			int midPt = (leftPt + rightPt) >> 1;
			if (check(midPt))
			{
				ans = midPt;
				rightPt = midPt - 1;
			}
			else
			{
				leftPt = midPt + 1;
			}
		}

		if (ans == -1)
		{
			cout << "No Solution" << endl;
		}
		else
		{
			cout << ans << endl;
		}
	}
	return 0;
}
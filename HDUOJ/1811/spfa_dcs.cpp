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
#define VERTEX_SIZE 10010
#define EDGE_SIZE 40040
using namespace std;

typedef struct _Edge
{
	int to;
	int len;
	int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int vertexNum;

int dis[VERTEX_SIZE], cnt[VERTEX_SIZE];
bool isInQueue[VERTEX_SIZE];

map<int, int> mp;
int cntId;

typedef struct _Input
{
	int fst;
	int snd;
	char opr;
} Input;

Input inputArr[EDGE_SIZE];

int parent[VERTEX_SIZE];

void initDisjointSet()
{
	for (int i = 0; i < vertexNum; i++)
	{
		parent[i] = i;
	}
}

int getParent(int n)
{
	if (parent[n] == n)
	{
		return n;
	}
	else
	{
		parent[n] = getParent(parent[n]);
		return parent[n];
	}
}

void mergeNode(int fst, int snd)
{
	int fstParent = getParent(fst);
	int sndParent = getParent(snd);

	if (fstParent != sndParent)
	{
		parent[sndParent] = fstParent;
	}
}

int getId(int realId)
{
	if (mp.find(realId) == mp.end())
	{
		mp[realId] = cntId++;
	}
	return mp[realId];
}

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
	for (int i = 0; i < vertexNum; i++)
	{
		q.push(i);
		isInQueue[i] = true;
		dis[i] = 0;
		cnt[i] = 0;
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
		mp.clear();
		memset(head, -1, sizeof(head));
		arrPt = 0;
		cntId = 0;

		initDisjointSet();
		for (int i = 0; i < edgeNum; i++)
		{
			cin >> inputArr[i].fst >> inputArr[i].opr >> inputArr[i].snd;
			if (inputArr[i].fst != inputArr[i].snd && inputArr[i].opr == '=')
			{
				mergeNode(inputArr[i].fst, inputArr[i].snd);
			}
		}

		for (int i = 0; i < vertexNum; i++)
		{
			parent[i] = getParent(parent[i]);
		}

		for (int i = 0; i < vertexNum; i++)
		{
			parent[i] = getId(parent[i]);
		}

		vertexNum = cntId;

		for (int i = 0; i < edgeNum; i++)
		{
			if (inputArr[i].opr == '<')
			{
				addEdge(parent[inputArr[i].snd], parent[inputArr[i].fst], -1);
			}
			else if (inputArr[i].opr == '>')
			{
				addEdge(parent[inputArr[i].fst], parent[inputArr[i].snd], -1);
			}
		}

		if (spfa(0))
		{
			sort(dis + 0, dis + vertexNum);
			bool isCertain = true;
			for (int i = 0; i < vertexNum; i++)
			{
			    if (i < vertexNum - 1 && dis[i] == dis[i + 1])
			    {
			        isCertain = false;
			        break;
			    }
			}

			if (isCertain)
				cout << "OK" << endl;
			else
				cout << "UNCERTAIN" << endl;
		}
		else
		{
			cout << "CONFLICT" << endl;
		}
	}
	return 0;
}
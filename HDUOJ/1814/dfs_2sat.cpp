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
#define VERTEX_SIZE 16010
#define EDGE_SIZE 40200
using namespace std;

typedef struct _Edge
{
	int to;
	int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
bool hasSelected[VERTEX_SIZE];
stack<int> st;


int vertexNum;

void addEdge(int from, int to)
{
	arr[arrPt] = {to, head[from]};
	head[from] = arrPt++;
}

bool dfs(int cntPt)
{
	if (hasSelected[cntPt ^ 1])
		return false;
	if (hasSelected[cntPt])
		return true;

	hasSelected[cntPt] = true;
	st.push(cntPt);
	for (int i = head[cntPt]; i != -1; i = arr[i].next)
	{
		int nextPt = arr[i].to;
		if (!dfs(nextPt))
		{
			return false;
		}
	}
	return true;
}

bool twoSat()
{
	memset(hasSelected, false, sizeof(hasSelected));
	for (int i = 0; i < vertexNum; i += 2)
	{
		if (!hasSelected[i] && !hasSelected[i ^ 1])
		{
			while (!st.empty())
				st.pop();

			if (!dfs(i))
			{
				while (!st.empty())
				{
					int cntTop = st.top();
					st.pop();
					hasSelected[cntTop] = false;
				}

				if (!dfs(i ^ 1))
				{
					return false;
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
		memset(head, -1, sizeof(head));
		arrPt = 0;
		vertexNum <<= 1;
		for (int i = 0; i < edgeNum; i++)
		{
			int from, to;
			cin >> from >> to;
			from--;
			to--;

			addEdge(from, (to ^ 1));
			addEdge(to, (from ^ 1));
		}

		if (twoSat())
		{
			for (int i = 0; i < vertexNum; i += 2)
			{
				if (hasSelected[i])
					cout << i + 1 << endl;
				else
					cout << (i ^ 1) + 1 << endl;
			}
		}
		else
		{
			cout << "NIE" << endl;
		}
	}
	return 0;
}
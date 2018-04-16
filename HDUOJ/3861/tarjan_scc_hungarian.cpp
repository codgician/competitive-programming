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
#define EDGE_SIZE 100100
#define VERTEX_SIZE 5010
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

bool matchArr[VERTEX_SIZE][VERTEX_SIZE], sndVisited[VERTEX_SIZE];
int sndMatch[VERTEX_SIZE];

void addEdge(int from, int to)
{
	arr[arrPt] = {to, head[from]};
	head[from] = arrPt++;
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

bool canFind(int fstId)
{
    for (int i = 0; i < sccNum; i++)
    {
        if (matchArr[fstId][i] && !sndVisited[i])
        {
            sndVisited[i] = true;
            
            if (sndMatch[i] == -1 || canFind(sndMatch[i]))
            {
                sndMatch[i] = fstId;
                return true;
            }
        }
    }
    return false;
}

int hungarian()
{
	memset(sndMatch, -1, sizeof(sndMatch));
    int ans = 0;
    for (int i = 0; i < sccNum; i++)
    {
        memset(sndVisited, false, sizeof(sndVisited));
        
        if (canFind(i))
        {
            ans++;
        }
    }
    return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	int caseNum;
	cin >> caseNum;
	while (caseNum--)
	{
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
			cout << 1 << endl;
			continue;
		}

		memset(matchArr, false, sizeof(matchArr));
		for (int i = 0; i < vertexNum; i++)
		{
			for (int j = head[i]; j != -1; j = arr[j].next)
			{
				int nextPt = arr[j].to;
				if (sccId[i] != sccId[nextPt])
				{
					matchArr[sccId[i]][sccId[nextPt]] = true;
				}
			}
		}

		int ans = hungarian();
		cout << sccNum - ans << endl;
	}
	return 0;
}


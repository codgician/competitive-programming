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

#define PERSON_SIZE 110
#define VERTEX_SIZE 220
#define EDGE_SIZE 96800

bool isFriend[PERSON_SIZE][PERSON_SIZE];

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
    cin.tie(0);
    cout.tie(0);

    int personNum;
    while (cin >> personNum)
    {
    	memset(head, -1, sizeof(head));
    	memset(isFriend, false, sizeof(isFriend));
    	arrPt = 0;
    	vertexNum = personNum << 1;
    	for (int i = 0; i < personNum; i++)
    	{
    		int cntId;
    		isFriend[i][i] = true;
    		while (true)
    		{
    			cin >> cntId;
    			if (cntId == 0)
    				break;
    			cntId--;
    			isFriend[i][cntId] = true;
    		}

    		for (int j = 0; j < personNum; j++)
    		{
    			if (!isFriend[i][j])
    			{
    				addEdge(i << 1, j << 1 | 1);
    				addEdge(i << 1 | 1, j << 1);

    				addEdge(j << 1, i << 1 | 1);
    				addEdge(j << 1 | 1, i << 1);
    			}
    		}
    	}

    	if (twoSat())
    		cout << "YES" << endl;
    	else
    		cout << "NO" << endl;
    }

    return 0;
}
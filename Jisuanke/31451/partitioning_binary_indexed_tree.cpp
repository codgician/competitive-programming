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

#define SIZE 100010

typedef struct _Edge
{
	int to;
	int next;
} Edge;

Edge arr[SIZE];
int head[SIZE], arrPt;
int inTime[SIZE], outTime[SIZE], cntTime;

vector<int> depthVec[SIZE], largeVec;
long long int lazyArr[SIZE];

long long int bitArr[SIZE];
int vertexNum, qNum;

void addEdge(int from, int to)
{
	arr[arrPt] = {to, head[from]};
	head[from] = arrPt++;
}

int getLowbit(int n)
{
    return n & -n;
}

void add(int pos, int val)
{
    for (int i = pos; i <= vertexNum; i += getLowbit(i))
    {
        bitArr[i] += val;
    }
}

long long int getPrefixSum(int pos)
{
    long long int ans = 0;
    for (int i = pos; i > 0; i -= getLowbit(i))
    {
        ans += bitArr[i];
    }
    return ans;
}

long long int getRangeSum(int qLeftPt, int qRightPt)
{
	return getPrefixSum(qRightPt) - getPrefixSum(qLeftPt - 1);
}

void dfs(int cntPt, int depth)
{
	inTime[cntPt] = ++cntTime;
	depthVec[depth].push_back(cntTime);
	for (int i = head[cntPt]; i != -1; i = arr[i].next)
	{
		int nextPt = arr[i].to;
		dfs(nextPt, depth + 1);
	}
	outTime[cntPt] = cntTime;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (cin >> vertexNum >> qNum)
    {
    	memset(head, -1, sizeof(head));
    	memset(bitArr, 0, sizeof(bitArr));
    	memset(lazyArr, 0, sizeof(lazyArr));
    	arrPt = 0;
    	cntTime = 0;
    	int lim = sqrt(vertexNum);

    	for (int i = 0; i < vertexNum - 1; i++)
    	{
    		int from, to;
    		cin >> from >> to;
    		from--;
    		to--;
    		addEdge(from, to);

    		depthVec[i].clear();
    	}
    	depthVec[vertexNum - 1].clear();
    	largeVec.clear();

    	dfs(0, 0);

    	for (int i = 0; i < vertexNum; i++)
    	{
    		if ((int)depthVec[i].size() >= lim)
    		{
    			largeVec.push_back(i);
    		}
    	}

    	while (qNum--)
    	{
    		int opr;
    		cin >> opr;

    		if (opr == 1)
    		{
    			// increase
    			int depth, val;
    			cin >> depth >> val;

    			if ((int)depthVec[depth].size() >= lim)
    			{
    				// large quantity of vertices
    				// tag it
    				lazyArr[depth] += val;
    			}
    			else
    			{
    				// small quantity of vertices
    				// brute force
    				for (auto it = depthVec[depth].begin(); it != depthVec[depth].end(); ++it)
    				{
    					add(*it, val);
    				}
    			}
    		}
    		else
    		{
    			// query
    			int rootPt;
    			cin >> rootPt;
    			rootPt--;
    			long long int ans = getRangeSum(inTime[rootPt], outTime[rootPt]);

    			for (auto it = largeVec.begin(); it != largeVec.end(); ++it)
    			{
    				int num = upper_bound(depthVec[*it].begin(), depthVec[*it].end(), outTime[rootPt])
    						- lower_bound(depthVec[*it].begin(), depthVec[*it].end(), inTime[rootPt]);
    				ans += num * lazyArr[*it];
    			}

    			cout << ans << endl;
    		}
    	}
    }

    return 0;
}
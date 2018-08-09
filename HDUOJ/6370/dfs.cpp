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

#define SIZE 100100

typedef struct _Edge
{
    int to;
    bool type;
} Edge;

Edge arr[SIZE];
int vertexNum;

bool hasVisited[SIZE];
int ans[SIZE];
int parent[SIZE];

void dfs(int cntPt)
{
    hasVisited[cntPt] = true;
    int nextPt = arr[cntPt].to;
    if (arr[cntPt].type == 1)
    {
        if (!hasVisited[nextPt])
        {
            dfs(nextPt);
            if (ans[nextPt] == -1 || cntPt == ans[nextPt])
                ans[cntPt] = -1;
            else
                ans[cntPt] = ans[nextPt];
        }
        else if (ans[nextPt] == 0)
        {
            ans[nextPt] = INT_MAX;
        }
        else
        {
            ans[cntPt] = ans[nextPt];
            if (ans[cntPt] == cntPt)
                ans[cntPt] = -1;
        }   
    }
    else
    {
        ans[cntPt] = nextPt;
    }
}

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        scanf("%d", &vertexNum);
        for (int i = 0; i < vertexNum; i++)
        {
            parent[i] = i;
        }

        for (int i = 0; i < vertexNum; i++)
        {
            int who;
            char what[20];
            scanf("%d %s", &who, what);
            who--;
            if (what[0] == 'w')
            {
                arr[i] = {who, 0};
            }
            else if (what[0] == 'v')
            {
                arr[i] = {who, 1};
            }
        }

        memset(hasVisited, false, sizeof(hasVisited));
        memset(ans, 0, sizeof(ans));
        for (int i = 0; i < vertexNum; i++)
        {
            if (ans[i] == 0)
                dfs(i);
        }

        int wolfNum = 0;
        for (int i = 0; i < vertexNum; i++)
        {
            if (ans[i] == -1)
                wolfNum++;
        }
        printf("0 %d\n", wolfNum);
    }
    return 0;
}
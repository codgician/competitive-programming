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
#include <cassert>
using namespace std;

#define SIZE 500010

typedef struct _Edge
{
    int to, next;
} Edge;

Edge arr[SIZE << 1];
int head[SIZE], arrPt;
int deg[SIZE], vertexNum;
char buf[SIZE];

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
    arr[arrPt] = {from, head[to]};
    head[to] = arrPt++;
    deg[from]++, deg[to]++;
}

int main()
{
    memset(head, -1, sizeof(head));
    memset(deg, 0, sizeof(deg));
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        arrPt = 0;
        scanf("%d", &vertexNum);
        for (int i = 1; i < vertexNum; i++)
        {
            int from, to;
            scanf("%d%d", &from, &to);
            from--, to--;
            addEdge(from, to);
        }
        scanf("%s", buf);
        for (int i = 0; i < (int)strlen(buf); i++)
        {
            if (buf[i] == 'N')
                continue;
            addEdge(i, vertexNum);
            addEdge(vertexNum, vertexNum + 1);
            addEdge(vertexNum, vertexNum + 2);
            vertexNum += 3;
        }

        bool ans = false;
        int deg3Num = 0;
        for (int i = 0; !ans && i < vertexNum; i++)
        {
            if (deg[i] == 3)
            {
                deg3Num++;
                int notLeafNum = 0;
                for (int j = head[i]; !ans && j != -1; j = arr[j].next)
                {
                    if (deg[arr[j].to] > 1)
                    {
                        notLeafNum++;
                        if (notLeafNum > 1)
                            ans = true;
                    }
                }
            }
            else if (deg[i] > 3)
                ans = true;
        }

        if (!ans && deg3Num == 2 && (vertexNum & 1))
            ans = true;

        if (ans)
            puts("White");
        else
            puts("Draw");

        if (caseNum > 0)
            for (int i = 0; i < vertexNum; i++)
                head[i] = -1, deg[i] = 0;
    }

    return 0;
}
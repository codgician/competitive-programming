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
#include <functional>
#include <iterator>
#define VERTEX_SIZE 100100
#define EDGE_SIZE 400400
#define SIZE 100100
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

int lastArr[SIZE];

void addEdge(int from, int to, int len)
{
    arr[arrPt] = {to, len, head[from]};
    head[from] = arrPt++;
}

bool spfa()
{
    memset(isInQueue, false, sizeof(isInQueue));
    for (int i = 0; i < vertexNum; i++)
        dis[i] = INT_MAX;
    
    queue<int> q;
    for (int i = 0; i < vertexNum; i++)
    {
        q.push(i);
        cnt[i] = 0;
        dis[i] = 0;
        isInQueue[i] = true;
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
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        memset(head, -1, sizeof(head));
        arrPt = 0;

        memset(lastArr, -1, sizeof(lastArr));
        scanf("%d", &vertexNum);
        for (int i = 0; i < vertexNum; i++)
        {
            int cnt;
            scanf("%d", &cnt);

            if (lastArr[cnt - 1] != -1)
                addEdge(i, lastArr[cnt - 1], -1);
            if (lastArr[cnt] != -1)
                addEdge(lastArr[cnt], i, 0);

            lastArr[cnt] = i;
        }

        for (int i = 0; i < vertexNum; i++)
        {
            int lwb, upb;
            scanf("%d%d", &lwb, &upb);
            addEdge(i, vertexNum, -lwb);
            addEdge(vertexNum, i, upb);
        }

        vertexNum++;
        spfa();
        vertexNum--;

        for (int i = 0; i < vertexNum; i++)
        {
            printf("%d", dis[i] - dis[vertexNum]);
            if (i < vertexNum - 1)
                printf(" ");
            else
                printf("\n");
        }
    }
    return 0;
}
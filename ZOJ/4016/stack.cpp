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
#include <set>
#include <map>
#include <functional>
#include <iterator>
#define SIZE 2000100
using namespace std;

typedef struct _Node
{
    int next;
    int val;
} Node;

Node arr[SIZE];
int head[SIZE], tail[SIZE];
int arrPt;

inline bool isEmpty(int stackId)
{
    return tail[stackId] == -1;
}

inline void push(int stackId, int val)
{
    if (isEmpty(stackId))
        tail[stackId] = arrPt;

    arr[arrPt].val = val;
    arr[arrPt].next = head[stackId];
    head[stackId] = arrPt++;
}

inline int pop(int stackId)
{
    if (tail[stackId] == -1)
        return -1;

    int ans = arr[head[stackId]].val;
    head[stackId] = arr[head[stackId]].next;
    if (head[stackId] == -1)
    {
        tail[stackId] = -1;
    }

    return ans;
}

inline void moveStack(int from, int to)
{
    if (isEmpty(from))
        return;

    arr[tail[from]].next = head[to];
    head[to] = head[from];
    if (tail[to] == -1)
    {
        tail[to] = tail[from];
    }
    head[from] = -1;
    tail[from] = -1;
}

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        arrPt = 0;
        int stackNum, oprNum;
        scanf("%d%d", &stackNum, &oprNum);

        for (int i = 0; i < stackNum; i++)
        {
            head[i] = -1;
            tail[i] = -1;
        }
        while (oprNum--)
        {
            int opr;
            scanf("%d", &opr);
            if (opr == 1)
            {
                int stackId, val;
                scanf("%d%d", &stackId, &val);
                stackId--;
                push(stackId, val);

            }
            else if (opr == 2)
            {
                int stackId;
                scanf("%d", &stackId);
                stackId--;
                int ans = pop(stackId);
                if (ans == -1)
                    printf("EMPTY\n");
                else
                    printf("%d\n", ans);
            }
            else if (opr == 3)
            {
                int to, from;
                scanf("%d%d", &to, &from);
                from--;
                to--;
                moveStack(from, to);
            }
        }
    }
    return 0;
}

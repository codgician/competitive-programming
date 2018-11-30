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

#define SIZE 1510

typedef struct _Edge
{
    int to, next;
} Edge;

Edge arr[SIZE << 1];
int head[SIZE], arrPt;

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

bool sndVisited[SIZE];
int sndMatch[SIZE];
int vertexNum;

bool canFind(int fstPt)
{
    for (int i = head[fstPt]; i != -1; i = arr[i].next)
    {
        int sndPt = arr[i].to;
        if (sndVisited[sndPt])
            continue;
        sndVisited[sndPt] = true;
        if (sndMatch[sndPt] == -1 || canFind(sndMatch[sndPt]))
        {
            sndMatch[sndPt] = fstPt;
            return true;
        }
    }
    return false;
}

int hungarian()
{
    int ans = 0;
    memset(sndMatch, -1, sizeof(sndMatch));
    for (int i = 0; i < vertexNum; i++)
    {
        memset(sndVisited, false, sizeof(sndVisited));
        if (canFind(i))
            ans++;
    }
    return ans;
}

int main()
{
    while (scanf("%d", &vertexNum) != EOF)
    {
        memset(head, -1, sizeof(head));
        arrPt = 0;
        for (int i = 0; i < vertexNum; i++)
        {
            int from, cntNum;
            scanf("%d:(%d)", &from, &cntNum);
            while (cntNum--)
            {
                int to;
                scanf("%d", &to);
                addEdge(from, to);
                addEdge(to, from);
            }
        }

        int ans = hungarian();
        cout << (ans >> 1) << endl;
    }

    return 0;
}
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

#define SIZE 200020

typedef struct _Edge
{
    int to;
    int next;
} Edge;

Edge arr[SIZE];
int head[SIZE], arrPt;

bool hasVisited[SIZE];

int inSet[SIZE], inDeg[SIZE], noDeg[SIZE];

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt)
{
    if (hasVisited[cntPt])
        return;

    hasVisited[cntPt] = true;
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;

        if (inSet[cntPt] == 1)
        {
            inSet[nextPt] = 0;
            dfs(nextPt);
        }
        else if (inSet[cntPt] == 0)
        {
            noDeg[nextPt]++;
            if (noDeg[nextPt] == inDeg[nextPt])
            {
                inSet[nextPt] = 1;
                dfs(nextPt);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int num;
    while (cin >> num)
    {
        memset(head, -1, sizeof(head));
        memset(inDeg, 0, sizeof(inDeg));
        memset(noDeg, 0, sizeof(noDeg));
        memset(hasVisited, false, sizeof(hasVisited));
        memset(inSet, -1, sizeof(inSet));
        arrPt = 0;
        num <<= 1;
        for (int i = 0; i < num; i++)
        {
            int cnt;
            cin >> cnt;
            cnt--;
            addEdge(i, cnt);
            inDeg[cnt]++;
        }

        for (int i = 0; i < num; i++)
        {
            if (inDeg[i] == 0)
            {
                inSet[i] = 1;
                dfs(i);
            }
        }
        
        for (int i = 0; i < num; i++)
        {
            if (!hasVisited[i])
            {
                inSet[i] = 1;
                dfs(i);
            }
        }

        bool isFirst = true;
        for (int i = 0; i < num; i++)
        {
            if (inSet[i] == 1)
            {
                if (isFirst)
                    isFirst = false;
                else
                    cout << " ";
                cout << i + 1;
            }
        }
        cout << endl;
    }

    return 0;
}
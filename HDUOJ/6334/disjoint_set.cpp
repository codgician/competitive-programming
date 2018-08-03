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

#define VERTEX_SIZE 300300
#define EDGE_SIZE 600600

typedef struct _Edge
{
    int to;
    int type;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;

int depth[VERTEX_SIZE];
int father[VERTEX_SIZE];

int parent1[VERTEX_SIZE], parent2[VERTEX_SIZE];
int sizeArr1[VERTEX_SIZE], sizeArr2[VERTEX_SIZE];

int vertexNum, dayNum;

void addEdge(int from, int to, int type)
{
    arr[arrPt] = {to, type, head[from]};
    head[from] = arrPt++;
}

int getParent1(int cntPt)
{
    if (parent1[cntPt] == cntPt)
        return cntPt;
    parent1[cntPt] = getParent1(parent1[cntPt]);
    return parent1[cntPt];
}

int getParent2(int cntPt)
{
    if (parent2[cntPt] == cntPt)
        return cntPt;
    parent2[cntPt] = getParent2(parent2[cntPt]);
    return parent2[cntPt];
}

void merge1(int fst, int snd)
{
    if (depth[fst] > depth[snd])
        swap(fst, snd);

    int fstParent = getParent1(fst);
    int sndParent = getParent1(snd);
    parent1[sndParent] = fstParent;
    sizeArr1[fstParent] += sizeArr1[sndParent];
}

void merge2(int fst, int snd)
{
    if (depth[fst] > depth[snd])
        swap(fst, snd);
    
    int fstParent = getParent2(fst);
    int sndParent = getParent2(snd);
    parent2[sndParent] = fstParent;
    sizeArr2[fstParent] += sizeArr2[sndParent];

    if (father[sndParent] != -1)
        sizeArr1[getParent1(father[sndParent])] -= sizeArr2[sndParent];
    if (father[fstParent] != -1)
        sizeArr1[getParent1(father[fstParent])] += sizeArr2[sndParent];
}

void dfs(int cntPt, int fatherPt)
{
    if (fatherPt == -1)
    {
        depth[cntPt] = 0;
        father[cntPt] = -1;
    }
    else
    {
        depth[cntPt] = depth[fatherPt] + 1;  
        father[cntPt] = fatherPt; 
    }

    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == fatherPt)
            continue;
        sizeArr1[cntPt]++;
        dfs(nextPt, cntPt);
    }

    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == fatherPt)
            continue;
        
        if (arr[i].type == 1)
        {
            merge2(cntPt, nextPt);
            merge1(cntPt, nextPt);
        }
        else if (arr[i].type == 2)
        {
            merge2(cntPt, nextPt);
        }
    }
}

void update(int fst, int snd)
{
    if (getParent1(fst) != getParent1(snd))
    {
        if (getParent2(fst) == getParent2(snd))
        {
            merge1(fst, snd);
        }
        else
        {
            merge2(fst, snd);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(head, -1, sizeof(head));
        arrPt = 0;
        cin >> vertexNum >> dayNum;
        for (int i = 0; i < vertexNum; i++)
        {
            parent1[i] = i;
            parent2[i] = i;
            sizeArr1[i] = 0;
            sizeArr2[i] = 1;
        }
        for (int i = 0; i < vertexNum - 1; i++)
        {
            int from, to, type;
            cin >> from >> to >> type;
            from--;
            to--;
            addEdge(from, to, type);
            addEdge(to, from, type);
        }

        dfs(0, -1);

        for (int i = 0; i < dayNum; i++)
        {
            int updFrom, updTo, qFrom, qTo;
            cin >> updFrom >> updTo >> qTo >> qFrom;
            updFrom--;
            updTo--;
            qFrom--;
            qTo--;

            bool canReach = 0;
            update(updFrom, updTo);

            if (getParent2(qFrom) == getParent2(qTo) ||
                (father[getParent2(qFrom)] != -1 && getParent1(father[getParent2(qFrom)]) == getParent1(qTo)) ||
                (father[getParent1(qTo)] != -1 && getParent2(father[getParent1(qTo)]) == getParent2(qFrom))
            )
                canReach = 1; 

            int ans = sizeArr2[getParent2(qTo)] + sizeArr1[getParent1(qTo)];
            if (father[getParent1(qTo)] != -1 && getParent2(qTo) != getParent2(father[getParent1(qTo)]))
                ans += sizeArr2[getParent2(father[getParent1(qTo)])];

            cout << canReach << " " << ans << endl;
        }
    }
    return 0;
}
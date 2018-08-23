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
#include <bitset>
#include <functional>
#include <iterator>
using namespace std;

#define VERTEX_SIZE 100010
#define EDGE_SIZE 100010

typedef struct _Edge
{
    int to;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int vertexNum;

int val[VERTEX_SIZE], ans[VERTEX_SIZE];

vector<int> divisorArr[VERTEX_SIZE];

#define LEFT_SON segTree[segPt].leftSon
#define RIGHT_SON segTree[segPt].rightSon

typedef struct _SegNode
{
    int leftSon, rightSon;
    int maxVal;
} SegNode;

SegNode segTree[VERTEX_SIZE * 400];
int root[VERTEX_SIZE], cntPt;

void pushUp(int segPt)
{
    if (LEFT_SON > 0)
        segTree[segPt].maxVal = max(segTree[segPt].maxVal, segTree[LEFT_SON].maxVal);
    if (RIGHT_SON > 0)
        segTree[segPt].maxVal = max(segTree[segPt].maxVal, segTree[RIGHT_SON].maxVal);
}

void update(int & segPt, int leftPt, int rightPt, int pos)
{
    if (segPt == 0)
        segPt = ++cntPt;

    if (leftPt == rightPt)
    {
        segTree[segPt].leftSon = 0;
        segTree[segPt].rightSon = 0;
        segTree[segPt].maxVal = pos;
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    if (pos <= midPt)
        update(segTree[segPt].leftSon, leftPt, midPt, pos);
    else
        update(segTree[segPt].rightSon, midPt + 1, rightPt, pos);
    pushUp(segPt);
}

int mergeTree(int fstPt, int sndPt, int & ans)
{
    if (fstPt == 0 || sndPt == 0)
        return fstPt ^ sndPt;

    if (segTree[fstPt].maxVal == segTree[sndPt].maxVal)
    {
        ans = max(ans, segTree[fstPt].maxVal);
    }

    if (segTree[fstPt].leftSon | segTree[sndPt].leftSon)
        segTree[fstPt].leftSon = mergeTree(segTree[fstPt].leftSon, segTree[sndPt].leftSon, ans);

    if (segTree[fstPt].rightSon | segTree[sndPt].rightSon)
        segTree[fstPt].rightSon = mergeTree(segTree[fstPt].rightSon, segTree[sndPt].rightSon, ans);

    return fstPt;
}

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt)
{
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        dfs(nextPt);
        root[cntPt] = mergeTree(root[cntPt], root[nextPt], ans[cntPt]);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    for (int i = 1; i < VERTEX_SIZE; i++)
    {
        for (int j = i; j < VERTEX_SIZE; j += i)
        {
            divisorArr[j].push_back(i);
        }
    }

    cin >> vertexNum;

    memset(head, -1, sizeof(head));
    arrPt = 0;
    cntPt = 0;

    for (int i = 1; i < vertexNum; i++)
    {
        int cntFather;
        cin >> cntFather;
        cntFather--;
        addEdge(cntFather, i);
    }

    for (int i = 0; i < vertexNum; i++)
    {
        cin >> val[i];

        ans[i] = -1;
        root[i] = 0;
        for (int j = 0; j < (int)divisorArr[val[i]].size(); j++)
        {
            update(root[i], 1, VERTEX_SIZE - 1, divisorArr[val[i]][j]);
        }
    }

    dfs(0);

    for (int i = 0; i < vertexNum; i++)
    {
        cout << ans[i] << endl;
    }

    return 0;
}
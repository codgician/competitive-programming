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

typedef struct _Query
{
    int id;
    int leftPt, rightPt;
} Query;

vector<Query> qArr[SIZE];
long long int ansArr[SIZE];

typedef struct _Edge
{
    int to;
    long long int len;
    int next;
} Edge;

Edge arr[SIZE << 1];
int head[SIZE], arrPt;
int vertexNum;

int mx[SIZE];
long long int dist[SIZE];

void addEdge(int from, int to, long long int len)
{
    arr[arrPt] = {to, len, head[from]};
    head[from] = arrPt++;
}

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegNode
{
    int leftPt, rightPt;
    long long int minVal, lazy;
} SegNode;

SegNode segTree[SIZE << 2];

void pushUp(int segPt)
{
    segTree[segPt].minVal = min(segTree[LEFT_SON].minVal, segTree[RIGHT_SON].minVal);
}

void pushDown(int segPt)
{
    if (segTree[segPt].lazy != 0) 
    {
        if (segTree[LEFT_SON].minVal != LLONG_MAX)
        {
            segTree[LEFT_SON].minVal += segTree[segPt].lazy;
            segTree[LEFT_SON].lazy += segTree[segPt].lazy;
        }

        if (segTree[RIGHT_SON].minVal != LLONG_MAX)
        {
            segTree[RIGHT_SON].minVal += segTree[segPt].lazy;
            segTree[RIGHT_SON].lazy += segTree[segPt].lazy;
        }

        segTree[segPt].lazy = 0;
    }
}

void build(int segPt, int leftPt, int rightPt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;

    if (leftPt == rightPt)
    {
        segTree[segPt].minVal = leftPt == mx[leftPt] ? dist[leftPt] : LLONG_MAX;
        segTree[segPt].lazy = 0;
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);

    pushUp(segPt);
    segTree[segPt].lazy = 0;
}

void rangeAdd(int segPt, int qLeftPt, int qRightPt, long long int val)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        if (segTree[segPt].minVal != LLONG_MAX)
        {
            segTree[segPt].minVal += val;
            segTree[segPt].lazy += val;
        }
        return;
    }

    pushDown(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        rangeAdd(LEFT_SON, qLeftPt, qRightPt, val);
    if (qRightPt > midPt)
        rangeAdd(RIGHT_SON, qLeftPt, qRightPt, val);
    pushUp(segPt);
}

long long int queryMin(int segPt, int qLeftPt, int qRightPt)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
        return segTree[segPt].minVal;
    
    pushDown(segPt);
    long long int ans = LLONG_MAX;
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans = min(ans, queryMin(LEFT_SON, qLeftPt, qRightPt));
    if (qRightPt > midPt)
        ans = min(ans, queryMin(RIGHT_SON, qLeftPt, qRightPt));
    return ans;
}

void dfs1(int cntPt, int fatherPt)
{
    mx[cntPt] = cntPt;
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == fatherPt)
            continue;
        dist[nextPt] = dist[cntPt] + arr[i].len;
        dfs1(nextPt, cntPt);
        mx[cntPt] = max(mx[cntPt], mx[nextPt]);
    }
}

void dfs2(int cntPt, int fatherPt)
{
    for (auto cnt : qArr[cntPt])
        ansArr[cnt.id] = queryMin(1, cnt.leftPt, cnt.rightPt);
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == fatherPt)
            continue;
        long long int len = arr[i].len;
        rangeAdd(1, 1, vertexNum, len);
        rangeAdd(1, nextPt, mx[nextPt], -(len << 1ll));
        dfs2(nextPt, cntPt);
        rangeAdd(1, nextPt, mx[nextPt], len << 1ll);
        rangeAdd(1, 1, vertexNum, -len);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int qNum;
    cin >> vertexNum >> qNum;
    memset(head, -1, sizeof(head));
    arrPt = 0;
    for (int i = 2; i <= vertexNum; i++)
    {
        int to;
        long long int len;
        cin >> to >> len;
        addEdge(i, to, len);
        addEdge(to, i, len);
    }

    dist[1] = 0;
    dfs1(1, -1);

    build(1, 1, vertexNum);

    for (int i = 0; i < qNum; i++)
    {
        int cntPt, leftPt, rightPt;
        cin >> cntPt >> leftPt >> rightPt;
        qArr[cntPt].push_back(Query{i, leftPt, rightPt});
    }

    dfs2(1, -1);
    
    for (int i = 0; i < qNum; i++)
        cout << ansArr[i] << endl;

    return 0;
}
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

#define SIZE 500010

typedef struct _Node
{
    pair<int, int> minPt;
    int leftSon, rightSon;
} SegNode;

SegNode segTree[SIZE * 60];
int root[SIZE];

int arr[SIZE];
int last[SIZE], pre[SIZE];
int cntPt;

void build(int & segPt, int leftPt, int rightPt)
{
    segPt = ++cntPt;
    segTree[segPt].minPt = make_pair(INT_MAX, 0);
    if (leftPt == rightPt)
    {
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(segTree[segPt].leftSon, leftPt, midPt);
    build(segTree[segPt].rightSon, midPt + 1, rightPt);
}

void update(int & segPt, int prevPt, int leftPt, int rightPt, int pos, int val)
{
    segPt = ++cntPt;
    segTree[segPt].leftSon = segTree[prevPt].leftSon;
    segTree[segPt].rightSon = segTree[prevPt].rightSon;

    if (leftPt == rightPt)
    {
        segTree[segPt].minPt = make_pair(val, pos);
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    if (pos <= midPt)
        update(segTree[segPt].leftSon, segTree[prevPt].leftSon, leftPt, midPt, pos, val);
    else
        update(segTree[segPt].rightSon, segTree[prevPt].rightSon, midPt + 1, rightPt, pos, val);
    segTree[segPt].minPt = min(segTree[segTree[segPt].leftSon].minPt, segTree[segTree[segPt].rightSon].minPt);
}

pair<int, int> query(int segPt, int leftPt, int rightPt, int qLeftPt, int qRightPt)
{
    if (qLeftPt <= leftPt && qRightPt >= rightPt)
    {
        return segTree[segPt].minPt;
    }

    pair<int, int> ans = make_pair(INT_MAX, 0);
    int midPt = (leftPt + rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans = min(ans, query(segTree[segPt].leftSon, leftPt, midPt, qLeftPt, qRightPt));
    if (qRightPt > midPt)
        ans = min(ans, query(segTree[segPt].rightSon, midPt + 1, rightPt, qLeftPt, qRightPt));
    return ans;
}

int main()
{
    cntPt = 0;
    memset(root, 0, sizeof(root));
    memset(last, 0, sizeof(last));

    int len;
    scanf("%d", &len);
    for (int i = 1; i <= len; i++)
    {
        scanf("%d", arr + i);
    }

    for (int i = 1; i <= len; i++)
    {
        last[i] = pre[arr[i]];
        pre[arr[i]] = i;
    }

    build(root[0], 1, len);

    for (int i = 1; i <= len; i++)
    {
        if (last[i] != 0)
        {
            update(root[i], root[i - 1], 1, len, last[i], INT_MAX);
            update(root[i], root[i], 1, len, i, last[i]);
        }
        else
        {
            update(root[i], root[i - 1], 1, len, i, last[i]);
        }
    }

    int qNum;
    scanf("%d", &qNum);
    while (qNum--)
    {
        int qLeftPt, qRightPt;
        scanf("%d%d", &qLeftPt, &qRightPt);
        pair<int, int> cntAns = query(root[qRightPt], 1, len, qLeftPt, qRightPt);
        if (cntAns.first < qLeftPt)
            printf("%d\n", arr[cntAns.second]);
        else
            puts("0");
    }
    return 0;
}
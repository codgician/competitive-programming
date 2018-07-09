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

#define SIZE 100010

typedef struct _Node
{
    int sum;
    int leftSon, rightSon;
} SegNode;

SegNode segTree[SIZE * 20];
int root[SIZE];

int arr[SIZE], dsc[SIZE];
int cntPt;

void build(int & segPt, int leftPt, int rightPt)
{
    segPt = ++cntPt;
    segTree[segPt].sum = 0;
    if (leftPt == rightPt)
    {
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(segTree[segPt].leftSon, leftPt, midPt);
    build(segTree[segPt].rightSon, midPt + 1, rightPt);
}

void add(int & segPt, int prevPt, int leftPt, int rightPt, int pos, int val)
{
    segPt = ++cntPt;
    segTree[segPt].leftSon = segTree[prevPt].leftSon;
    segTree[segPt].rightSon = segTree[prevPt].rightSon;
    segTree[segPt].sum = segTree[prevPt].sum + val;

    if (leftPt == rightPt)
        return;

    int midPt = (leftPt + rightPt) >> 1;
    if (pos <= midPt)
        add(segTree[segPt].leftSon, segTree[prevPt].leftSon, leftPt, midPt, pos, val);
    else
        add(segTree[segPt].rightSon, segTree[prevPt].rightSon, midPt + 1, rightPt, pos, val);
}

int query(int leftPt, int rightPt, int qLeftPt, int qRightPt, int k)
{
    if (leftPt == rightPt)
        return leftPt;

    int midPt = (leftPt + rightPt) >> 1;
    int leftDelta = segTree[segTree[qRightPt].leftSon].sum - segTree[segTree[qLeftPt].leftSon].sum;
    if (k <= leftDelta)
        return query(leftPt, midPt, segTree[qLeftPt].leftSon, segTree[qRightPt].leftSon, k);
    return query(midPt + 1, rightPt, segTree[qLeftPt].rightSon, segTree[qRightPt].rightSon, k - leftDelta);
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        cntPt = 0;
        memset(root, 0, sizeof(root));

        int len, qNum;
        cin >> len >> qNum;
        for (int i = 1; i <= len; i++)
        {
            cin >> arr[i];
            dsc[i] = arr[i];
        }

        sort(dsc + 1, dsc + len + 1);
        int dscLen = unique(dsc + 1, dsc + len + 1) - dsc - 1;
        build(root[0], 1, dscLen);

        for (int i = 1; i <= len; i++)
        {
            int cnt = lower_bound(dsc + 1, dsc + dscLen + 1, arr[i]) - dsc;
            add(root[i], root[i - 1], 1, dscLen, cnt, 1);
        }

        while (qNum--)
        {
            int qLeftPt, qRightPt, k;
            cin >> qLeftPt >> qRightPt >> k;
            int pos = query(1, dscLen, root[qLeftPt - 1], root[qRightPt], k);
            cout << dsc[pos] << endl;
        }
    }
    return 0;
}

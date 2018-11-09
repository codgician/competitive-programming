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

#define SIZE 200010

int arr[SIZE];

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegNode
{
    int leftPt, rightPt;
    int andSum, orSum, maxVal;
    int andLazy, orLazy;
} SegNode;

SegNode segTree[SIZE << 2];

void pushUp(int segPt)
{
    segTree[segPt].maxVal = max(segTree[LEFT_SON].maxVal, segTree[RIGHT_SON].maxVal);
    segTree[segPt].andSum = segTree[LEFT_SON].andSum & segTree[RIGHT_SON].andSum;
    segTree[segPt].orSum = segTree[LEFT_SON].orSum | segTree[RIGHT_SON].orSum;
}

void pushDown(int segPt)
{
    if (segTree[segPt].andLazy != (1 << 21) - 1)
    {
        segTree[LEFT_SON].maxVal &= segTree[segPt].andLazy;
        segTree[LEFT_SON].andSum &= segTree[segPt].andLazy;
        segTree[LEFT_SON].orSum &= segTree[segPt].andLazy;
        segTree[RIGHT_SON].maxVal &= segTree[segPt].andLazy;
        segTree[RIGHT_SON].andSum &= segTree[segPt].andLazy;
        segTree[RIGHT_SON].orSum &= segTree[segPt].andLazy;

        segTree[LEFT_SON].andLazy &= segTree[segPt].andLazy;
        segTree[LEFT_SON].orLazy &= segTree[segPt].andLazy;
        segTree[RIGHT_SON].andLazy &= segTree[segPt].andLazy;
        segTree[RIGHT_SON].orLazy &= segTree[segPt].andLazy;

        segTree[segPt].andLazy = (1 << 21) - 1;
    }

    if (segTree[segPt].orLazy != 0)
    {
        segTree[LEFT_SON].maxVal |= segTree[segPt].orLazy;
        segTree[LEFT_SON].andSum |= segTree[segPt].orLazy;
        segTree[LEFT_SON].orSum |= segTree[segPt].orLazy;
        segTree[RIGHT_SON].maxVal |= segTree[segPt].orLazy;
        segTree[RIGHT_SON].andSum |= segTree[segPt].orLazy;
        segTree[RIGHT_SON].orSum |= segTree[segPt].orLazy;

        segTree[LEFT_SON].orLazy |= segTree[segPt].orLazy;
        segTree[RIGHT_SON].orLazy |= segTree[segPt].orLazy;

        segTree[segPt].orLazy = 0;
    }
}

void build(int segPt, int leftPt, int rightPt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;
    segTree[segPt].andLazy = (1 << 21) - 1;
    segTree[segPt].orLazy = 0;

    if (leftPt == rightPt)
    {
        segTree[segPt].andSum = arr[leftPt];
        segTree[segPt].orSum = arr[leftPt];
        segTree[segPt].maxVal = arr[leftPt];
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(segPt);
}

void rangeAnd(int segPt, int qLeftPt, int qRightPt, int val)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        if (((segTree[segPt].andSum ^ segTree[segPt].orSum) & ~val) == 0)
        {
            segTree[segPt].andSum &= val;
            segTree[segPt].orSum &= val;
            segTree[segPt].maxVal &= val;
            segTree[segPt].andLazy &= val;
            segTree[segPt].orLazy &= val;
            return;
        }
    }

    pushDown(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        rangeAnd(LEFT_SON, qLeftPt, qRightPt, val);
    if (qRightPt > midPt)
        rangeAnd(RIGHT_SON, qLeftPt, qRightPt, val);
    pushUp(segPt);
}

void rangeOr(int segPt, int qLeftPt, int qRightPt, int val)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        if (((segTree[segPt].andSum ^ segTree[segPt].orSum) & val) == 0)
        {
            segTree[segPt].andSum |= val;
            segTree[segPt].orSum |= val;
            segTree[segPt].maxVal |= val;
            segTree[segPt].orLazy |= val;
            return;
        } 
    }

    pushDown(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        rangeOr(LEFT_SON, qLeftPt, qRightPt, val);
    if (qRightPt > midPt)
        rangeOr(RIGHT_SON, qLeftPt, qRightPt, val);
    pushUp(segPt);
}

int queryMax(int segPt, int qLeftPt, int qRightPt)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        return segTree[segPt].maxVal;
    }

    pushDown(segPt);
    int ans = 0;
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans = max(ans, queryMax(LEFT_SON, qLeftPt, qRightPt));
    if (qRightPt > midPt)
        ans = max(ans, queryMax(RIGHT_SON, qLeftPt, qRightPt));
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int len, qNum;
    cin >> len >> qNum;

    for (int i = 1; i <= len; i++)
        cin >> arr[i];

    build(1, 1, len);

    while (qNum--)
    {
        int type, qLeftPt, qRightPt;
        cin >> type >> qLeftPt >> qRightPt;

        if (type == 1)
        {
            // And
            int val;
            cin >> val;
            rangeAnd(1, qLeftPt, qRightPt, val);
        }
        else if (type == 2)
        {
            // Or
            int val;
            cin >> val;
            rangeOr(1, qLeftPt, qRightPt, val);
        }
        else if (type == 3)
        {
            // Max
            int ans = queryMax(1, qLeftPt, qRightPt);
            cout << ans << endl;
        }
    }

    return 0;
}
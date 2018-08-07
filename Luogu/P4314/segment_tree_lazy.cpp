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
#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

#define CURRENT 0
#define HISTORY 1

typedef struct _SegNode
{
    int leftPt, rightPt;
    int cntMax, cntAddLazy, cntUpdLazy;
    int hstMax, hstAddLazy, hstUpdLazy;
} SegNode;

SegNode segTree[SIZE << 2];

int arr[SIZE];

void pushUp(int segPt)
{
    segTree[segPt].cntMax = max(segTree[LEFT_SON].cntMax, segTree[RIGHT_SON].cntMax);
    segTree[segPt].hstMax = max(segTree[LEFT_SON].hstMax, segTree[RIGHT_SON].hstMax);
}

void addCnt(int segPt, int value)
{
    segTree[segPt].hstMax = max(segTree[segPt].hstMax, segTree[segPt].cntMax += value);
    if (segTree[segPt].cntUpdLazy != INT_MIN)
        segTree[segPt].hstUpdLazy = max(segTree[segPt].hstUpdLazy, segTree[segPt].cntUpdLazy += value);
    else
        segTree[segPt].hstAddLazy = max(segTree[segPt].hstAddLazy, segTree[segPt].cntAddLazy += value);
}

void addHst(int segPt, int value)
{
    segTree[segPt].hstMax = max(segTree[segPt].hstMax, segTree[segPt].cntMax + value);
    if (segTree[segPt].cntUpdLazy != INT_MIN)
        segTree[segPt].hstUpdLazy = max(segTree[segPt].hstUpdLazy, segTree[segPt].cntUpdLazy + value);
    else
        segTree[segPt].hstAddLazy = max(segTree[segPt].hstAddLazy, segTree[segPt].cntAddLazy + value);
}

void updateCnt(int segPt, int value)
{
    segTree[segPt].hstMax = max(segTree[segPt].hstMax, segTree[segPt].cntMax = value);
    segTree[segPt].hstUpdLazy = max(segTree[segPt].hstUpdLazy, segTree[segPt].cntUpdLazy = value);
}

void updateHst(int segPt, int value)
{
    segTree[segPt].hstMax = max(segTree[segPt].hstMax, value);
    segTree[segPt].hstUpdLazy = max(segTree[segPt].hstUpdLazy, value);
}

void pushDown(int segPt)
{
    if (segTree[segPt].hstAddLazy != 0)
    {
        addHst(LEFT_SON, segTree[segPt].hstAddLazy);
        addHst(RIGHT_SON, segTree[segPt].hstAddLazy);
        segTree[segPt].hstAddLazy = 0;
    }

    if (segTree[segPt].hstUpdLazy != INT_MIN)
    {
        updateHst(LEFT_SON, segTree[segPt].hstUpdLazy);
        updateHst(RIGHT_SON, segTree[segPt].hstUpdLazy);
        segTree[segPt].hstUpdLazy = INT_MIN;
    }

    if (segTree[segPt].cntAddLazy != 0)
    {
        addCnt(LEFT_SON, segTree[segPt].cntAddLazy);
        addCnt(RIGHT_SON, segTree[segPt].cntAddLazy);
        segTree[segPt].cntAddLazy = 0;
    }

    if (segTree[segPt].cntUpdLazy != INT_MIN)
    {
        updateCnt(LEFT_SON, segTree[segPt].cntUpdLazy);
        updateCnt(RIGHT_SON, segTree[segPt].cntUpdLazy);
        segTree[segPt].cntUpdLazy = INT_MIN;
    }
}

void build(int segPt, int leftPt, int rightPt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;

    segTree[segPt].cntAddLazy = 0;
    segTree[segPt].cntUpdLazy = INT_MIN;
    segTree[segPt].hstAddLazy = 0;
    segTree[segPt].hstUpdLazy = INT_MIN;

    if (leftPt == rightPt)
    {
        segTree[segPt].cntMax = arr[leftPt];
        segTree[segPt].hstMax = arr[leftPt];
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(segPt);
}

void rangeUpdate(int segPt, int qLeftPt, int qRightPt, int val)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        updateCnt(segPt, val);
        return;
    }

    pushDown(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        rangeUpdate(LEFT_SON, qLeftPt, qRightPt, val);
    if (qRightPt > midPt)
        rangeUpdate(RIGHT_SON, qLeftPt, qRightPt, val);
    pushUp(segPt);
}

void rangeAdd(int segPt, int qLeftPt, int qRightPt, int val)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        addCnt(segPt, val);
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

int queryMax(int segPt, int qLeftPt, int qRightPt, bool qType)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        return qType == CURRENT ? segTree[segPt].cntMax : segTree[segPt].hstMax;
    }

    pushDown(segPt);
    int ans = INT_MIN;
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans = max(ans, queryMax(LEFT_SON, qLeftPt, qRightPt, qType));
    if (qRightPt > midPt)
        ans = max(ans, queryMax(RIGHT_SON, qLeftPt, qRightPt, qType));
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int len;
    cin >> len;
    for (int i = 1; i <= len; i++)
    {
        cin >> arr[i];
    }

    build(1, 1, len);

    int oprNum;
    cin >> oprNum;
    while (oprNum--)
    {
        char opr;
        int qLeftPt, qRightPt;
        cin >> opr >> qLeftPt >> qRightPt;

        if (opr == 'Q')
        {
            cout << queryMax(1, qLeftPt, qRightPt, CURRENT) << endl;
        }
        else if (opr == 'A')
        {
            cout << queryMax(1, qLeftPt, qRightPt, HISTORY) << endl;
        }
        else if (opr == 'P')
        {
            int val;
            cin >> val;
            rangeAdd(1, qLeftPt, qRightPt, val);
        }
        else if (opr == 'C')
        {
            int val;
            cin >> val;
            rangeUpdate(1, qLeftPt, qRightPt, val);
        }
    }
    return 0;
}
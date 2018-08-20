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

#define SIZE 50010

typedef struct _Opr
{
    int qLeftPt, qRightPt;
    long long int k;
    int id;
} Opr;

Opr oprArr[SIZE], fstQueue[SIZE], sndQueue[SIZE];

long long int arr[SIZE], ans[SIZE];

int len, qNum;

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegNode
{
    int leftPt, rightPt;
    long long int sum;
    long long int lazy;
} SegNode;

SegNode segTree[SIZE << 2];

void pushUp(int segPt)
{
    segTree[segPt].sum = segTree[LEFT_SON].sum + segTree[RIGHT_SON].sum;
}

void pushDown(int segPt)
{
    if (segTree[segPt].lazy != 0)
    {
        segTree[LEFT_SON].sum += segTree[segPt].lazy * (segTree[LEFT_SON].rightPt - segTree[LEFT_SON].leftPt + 1);
        segTree[RIGHT_SON].sum += segTree[segPt].lazy * (segTree[RIGHT_SON].rightPt - segTree[RIGHT_SON].leftPt + 1);

        segTree[LEFT_SON].lazy += segTree[segPt].lazy;
        segTree[RIGHT_SON].lazy += segTree[segPt].lazy;

        segTree[segPt].lazy = 0;
    }
}

void build(int segPt, int leftPt, int rightPt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;
    if (leftPt == rightPt)
    {
        segTree[segPt].sum = 0;
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
        segTree[segPt].sum += val * (segTree[segPt].rightPt - segTree[segPt].leftPt + 1);
        segTree[segPt].lazy += val;
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

long long int querySum(int segPt, int qLeftPt, int qRightPt)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        return segTree[segPt].sum;
    }
    pushDown(segPt);
    long long int ans = 0;
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans += querySum(LEFT_SON, qLeftPt, qRightPt);
    if (qRightPt > midPt)
        ans += querySum(RIGHT_SON, qLeftPt, qRightPt);
    return ans;
}

void divideConquer(int headPt, int tailPt, int leftPt, int rightPt)
{
    if (leftPt == rightPt)
    {
        for (int i = headPt; i <= tailPt; i++)
        {
            if (oprArr[i].id != -1)
            {
                ans[oprArr[i].id] = rightPt;
            }
        }
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;

    int fstQPt = 0, sndQPt = 0;
    for (int i = headPt; i <= tailPt; i++)
    {
        if (oprArr[i].id == -1)
        {
            // add
            if (oprArr[i].k <= midPt)
            {
                fstQueue[fstQPt++] = oprArr[i];
            }
            else
            {
                rangeAdd(1, oprArr[i].qLeftPt + 1, oprArr[i].qRightPt + 1, 1);
                sndQueue[sndQPt++] = oprArr[i];
            }
        }
        else
        {
            // query
            long long int cntNum = querySum(1, oprArr[i].qLeftPt + 1, oprArr[i].qRightPt + 1);
            if (oprArr[i].k <= cntNum)
            {
                sndQueue[sndQPt++] = oprArr[i];
            }
            else
            {
                oprArr[i].k -= cntNum;
                fstQueue[fstQPt++] = oprArr[i];
            }
        }
    }

    // Restore Segment Tree
    for (int i = headPt; i <= tailPt; i++)
    {
        if (oprArr[i].id == -1 && oprArr[i].k > midPt)
        {
            rangeAdd(1, oprArr[i].qLeftPt + 1, oprArr[i].qRightPt + 1, -1);
        }
    }

    int cntPt = headPt;
    for (int i = 0; i < fstQPt; i++)
    {
        oprArr[cntPt++] = fstQueue[i];
    }
    for (int i = 0; i < sndQPt; i++)
    {
        oprArr[cntPt++] = sndQueue[i];
    }

    if (fstQPt > 0)
        divideConquer(headPt, headPt + fstQPt - 1, leftPt, midPt);
    if (headPt + fstQPt <= tailPt)
        divideConquer(headPt + fstQPt, tailPt, midPt + 1, rightPt);
}

int main()
{
    ios::sync_with_stdio(false);
    int len, oprNum;
    cin >> len >> oprNum;

    build(1, 1, len);

    int queryId = 0;
    for (int i = 0; i < oprNum; i++)
    {
        int type, qLeftPt, qRightPt;
        long long int k;
        cin >> type >> qLeftPt >> qRightPt >> k;
        oprArr[i] = {qLeftPt, qRightPt, k, -1};

        if (type == 2)
        {
            oprArr[i].id = queryId++;
        }
    }

    divideConquer(0, oprNum - 1, 1, len);

    for (int i = 0; i < queryId; i++)
    {
        cout << ans[i] << endl;
    }
    return 0;
}

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

#define SIZE 300010

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegNode
{
    int leftPt, rightPt;
    long long int minVal, secMinVal, minNum;
    long long int deltaLazy, deltaMinLazy, coverLazy;
} SegNode;

SegNode segTree[SIZE << 2];
long long int arr[SIZE];

void pushUp(int segPt)
{
    segTree[segPt].minVal = min(segTree[LEFT_SON].minVal, segTree[RIGHT_SON].minVal);
    if (segTree[LEFT_SON].minVal == segTree[RIGHT_SON].minVal)
    {
        segTree[segPt].minNum = segTree[LEFT_SON].minNum + segTree[RIGHT_SON].minNum;
        segTree[segPt].secMinVal = min(segTree[LEFT_SON].secMinVal, segTree[RIGHT_SON].secMinVal);
    }
    else if (segTree[segPt].minVal == segTree[LEFT_SON].minVal)
    {
        segTree[segPt].minNum = segTree[LEFT_SON].minNum;
        segTree[segPt].secMinVal = min(segTree[LEFT_SON].secMinVal, segTree[RIGHT_SON].minVal);
    }
    else
    {
        segTree[segPt].minNum = segTree[RIGHT_SON].minNum;
        segTree[segPt].secMinVal = min(segTree[LEFT_SON].minVal, segTree[RIGHT_SON].secMinVal);
    }
}

void pushDown(int segPt)
{
    if (segTree[segPt].coverLazy != -1)
    {
        segTree[LEFT_SON].minVal = segTree[segPt].coverLazy;
        segTree[LEFT_SON].secMinVal = LLONG_MAX;
        segTree[LEFT_SON].minNum = segTree[LEFT_SON].rightPt - segTree[LEFT_SON].leftPt + 1;
        segTree[RIGHT_SON].minVal = segTree[segPt].coverLazy;
        segTree[RIGHT_SON].secMinVal = LLONG_MAX;
        segTree[RIGHT_SON].minNum = segTree[RIGHT_SON].rightPt - segTree[RIGHT_SON].leftPt + 1;

        segTree[LEFT_SON].coverLazy = segTree[segPt].coverLazy;
        segTree[LEFT_SON].deltaMinLazy = 0;
        segTree[LEFT_SON].deltaLazy = 0;
        segTree[RIGHT_SON].coverLazy = segTree[segPt].coverLazy;
        segTree[RIGHT_SON].deltaMinLazy = 0;
        segTree[RIGHT_SON].deltaLazy = 0;

        segTree[segPt].coverLazy = -1;
    }

    if (segTree[segPt].deltaLazy != 0)
    {
        segTree[LEFT_SON].minVal += segTree[segPt].deltaLazy;
        if (segTree[LEFT_SON].secMinVal != LLONG_MAX)
            segTree[LEFT_SON].secMinVal += segTree[segPt].deltaLazy;

        segTree[RIGHT_SON].minVal += segTree[segPt].deltaLazy;
        if (segTree[RIGHT_SON].secMinVal != LLONG_MAX)
            segTree[RIGHT_SON].secMinVal += segTree[segPt].deltaLazy;

        segTree[LEFT_SON].deltaLazy += segTree[segPt].deltaLazy;
        segTree[RIGHT_SON].deltaLazy += segTree[segPt].deltaLazy;

        segTree[segPt].deltaLazy = 0;
    }
    
    if (segTree[segPt].deltaMinLazy != 0)
    {
        if (segTree[LEFT_SON].minVal == segTree[RIGHT_SON].minVal)
        {
            segTree[LEFT_SON].minVal += segTree[segPt].deltaMinLazy;
            segTree[RIGHT_SON].minVal += segTree[segPt].deltaMinLazy;

            segTree[LEFT_SON].deltaMinLazy += segTree[segPt].deltaMinLazy;
            segTree[RIGHT_SON].deltaMinLazy += segTree[segPt].deltaMinLazy;
        }
        else if (segTree[LEFT_SON].minVal < segTree[RIGHT_SON].minVal)
        {
            segTree[LEFT_SON].minVal += segTree[segPt].deltaMinLazy;
            segTree[LEFT_SON].deltaMinLazy += segTree[segPt].deltaMinLazy;
        }
        else
        {
            segTree[RIGHT_SON].minVal += segTree[segPt].deltaMinLazy;
            segTree[RIGHT_SON].deltaMinLazy += segTree[segPt].deltaMinLazy;
        }

        segTree[segPt].deltaMinLazy = 0;
    }
}

void build(int segPt, int leftPt, int rightPt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;

    if (leftPt == rightPt)
    {
        segTree[segPt].minVal = arr[leftPt];
        segTree[segPt].secMinVal = LLONG_MAX;
        segTree[segPt].minNum = 1;
        segTree[segPt].coverLazy = -1;
        segTree[segPt].deltaMinLazy = 0;
        segTree[segPt].deltaLazy = 0;
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);

    pushUp(segPt);
    segTree[segPt].coverLazy = -1;
    segTree[segPt].deltaMinLazy = 0;
    segTree[segPt].deltaLazy = 0;
}

void rangeUpd(int segPt, int qLeftPt, int qRightPt, long long int val)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        segTree[segPt].minVal = val;
        segTree[segPt].secMinVal = LLONG_MAX;
        segTree[segPt].minNum = segTree[segPt].rightPt - segTree[segPt].leftPt + 1;
        segTree[segPt].coverLazy = val;
        segTree[segPt].deltaMinLazy = 0;
        segTree[segPt].deltaLazy = 0;
        return;
    }

    pushDown(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        rangeUpd(LEFT_SON, qLeftPt, qRightPt, val);
    if (qRightPt > midPt)
        rangeUpd(RIGHT_SON, qLeftPt, qRightPt, val);
    pushUp(segPt);
}

void rangeAdd(int segPt, int qLeftPt, int qRightPt, long long int val)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        if (segTree[segPt].minVal + val >= 0)
        {
            segTree[segPt].minVal += val;
            if (segTree[segPt].secMinVal != LLONG_MAX)
                segTree[segPt].secMinVal += val;
            segTree[segPt].deltaLazy += val;
            return;
        }
        else if (segTree[segPt].secMinVal == LLONG_MAX)
        {
            segTree[segPt].minVal = 0;
            segTree[segPt].coverLazy = 0;
            segTree[segPt].deltaMinLazy = 0;
            segTree[segPt].deltaLazy = 0;
            return;
        }
        else if (segTree[segPt].secMinVal + val > 0)
        {
            // Only change minVal to 0
            segTree[segPt].deltaMinLazy -= val + segTree[segPt].minVal;
            segTree[segPt].minVal = 0;
            if (segTree[segPt].secMinVal != LLONG_MAX)
                segTree[segPt].secMinVal += val;
            segTree[segPt].deltaLazy += val;
            return;
        }
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
        if (segTree[segPt].minVal == 0)
            return segTree[segPt].minNum;
        return 0;
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

int main()
{
    int len, qNum;
    scanf("%d%d", &len, &qNum);

    for (int i = 1; i <= len; i++)
        scanf("%lld", arr + i);

    build(1, 1, len);

    while (qNum--)
    {
        int type, qLeftPt, qRightPt;
        scanf("%d%d%d", &type, &qLeftPt, &qRightPt);

        if (type == 1)
        {
            long long int val;
            scanf("%lld", &val);
            rangeUpd(1, qLeftPt, qRightPt, val);
        }
        else if (type == 2)
        {
            long long int val;
            scanf("%lld", &val);
            rangeAdd(1, qLeftPt, qRightPt, val);
        }
        else if (type == 3)
        {
            printf("%lld\n", querySum(1, qLeftPt, qRightPt));
        }
    }

    return 0;
}
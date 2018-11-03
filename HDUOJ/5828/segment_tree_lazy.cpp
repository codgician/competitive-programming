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

#define SIZE 100010
#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegNode
{
    int leftPt, rightPt;
    long long int sum, minVal, maxVal;
    long long int deltaLazy, coverLazy;
} SegNode;

SegNode segTree[SIZE << 2];
int arr[SIZE];

void pushUp(int segPt)
{
    segTree[segPt].sum = segTree[LEFT_SON].sum + segTree[RIGHT_SON].sum;
    segTree[segPt].minVal = min(segTree[LEFT_SON].minVal, segTree[RIGHT_SON].minVal);
    segTree[segPt].maxVal = max(segTree[LEFT_SON].maxVal, segTree[RIGHT_SON].maxVal);
}

void pushDown(int segPt)
{
    if (segTree[segPt].coverLazy != 0)
    {
        segTree[LEFT_SON].minVal = segTree[segPt].coverLazy;
        segTree[LEFT_SON].maxVal = segTree[segPt].coverLazy;
        segTree[RIGHT_SON].minVal = segTree[segPt].coverLazy;
        segTree[RIGHT_SON].maxVal = segTree[segPt].coverLazy;

        segTree[LEFT_SON].sum = segTree[segPt].coverLazy * (segTree[LEFT_SON].rightPt - segTree[LEFT_SON].leftPt + 1);
        segTree[RIGHT_SON].sum = segTree[segPt].coverLazy * (segTree[RIGHT_SON].rightPt - segTree[RIGHT_SON].leftPt + 1);

        segTree[LEFT_SON].coverLazy = segTree[segPt].coverLazy;
        segTree[LEFT_SON].deltaLazy = 0;
        segTree[RIGHT_SON].coverLazy = segTree[segPt].coverLazy;
        segTree[RIGHT_SON].deltaLazy = 0;

        segTree[segPt].coverLazy = 0;
    }

    if (segTree[segPt].deltaLazy != 0)
    {
        segTree[LEFT_SON].minVal += segTree[segPt].deltaLazy;
        segTree[LEFT_SON].maxVal += segTree[segPt].deltaLazy;
        segTree[RIGHT_SON].minVal += segTree[segPt].deltaLazy;
        segTree[RIGHT_SON].maxVal += segTree[segPt].deltaLazy;

        segTree[LEFT_SON].sum += segTree[segPt].deltaLazy * (segTree[LEFT_SON].rightPt - segTree[LEFT_SON].leftPt + 1);
        segTree[RIGHT_SON].sum += segTree[segPt].deltaLazy * (segTree[RIGHT_SON].rightPt - segTree[RIGHT_SON].leftPt + 1);

        segTree[LEFT_SON].deltaLazy += segTree[segPt].deltaLazy;
        segTree[RIGHT_SON].deltaLazy += segTree[segPt].deltaLazy;

        segTree[segPt].deltaLazy = 0;
    }
}

void build(int segPt, int leftPt, int rightPt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;

    if (leftPt == rightPt)
    {
        segTree[segPt].sum = arr[leftPt];
        segTree[segPt].minVal = arr[leftPt];
        segTree[segPt].maxVal = arr[leftPt];
        segTree[segPt].coverLazy = 0;
        segTree[segPt].deltaLazy = 0;
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);

    pushUp(segPt);
    segTree[segPt].coverLazy = 0;
    segTree[segPt].deltaLazy = 0;
}

void rangeAdd(int segPt, int qLeftPt, int qRightPt, long long int val)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        segTree[segPt].minVal += val;
        segTree[segPt].maxVal += val;
        segTree[segPt].sum += val * (segTree[segPt].rightPt - segTree[segPt].leftPt + 1);
        segTree[segPt].deltaLazy += val;
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

void rangeSqrt(int segPt, int qLeftPt, int qRightPt)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        long long int minSqrt = sqrt(segTree[segPt].minVal);
        long long int maxSqrt = sqrt(segTree[segPt].maxVal);

        if (minSqrt == maxSqrt)
        {
            segTree[segPt].minVal = minSqrt;
            segTree[segPt].maxVal = maxSqrt;
            segTree[segPt].sum = minSqrt * (segTree[segPt].rightPt - segTree[segPt].leftPt + 1);

            segTree[segPt].coverLazy = minSqrt;
            segTree[segPt].deltaLazy = 0;

            return;
        }
        else if (segTree[segPt].minVal + 1 == segTree[segPt].maxVal && minSqrt + 1 == maxSqrt)
        {
            long long int delta = segTree[segPt].minVal - minSqrt;

            segTree[segPt].minVal = minSqrt;
            segTree[segPt].maxVal = maxSqrt;

            segTree[segPt].sum -= delta * (segTree[segPt].rightPt - segTree[segPt].leftPt + 1);
            segTree[segPt].deltaLazy -= delta;

            return;
        }        
    }

    pushDown(segPt);
    int midPt = (segTree[LEFT_SON].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        rangeSqrt(LEFT_SON, qLeftPt, qRightPt);
    if (qRightPt > midPt)
        rangeSqrt(RIGHT_SON, qLeftPt, qRightPt);
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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int len, qNum;
        cin >> len >> qNum;

        for (int i = 1; i <= len; i++)
            cin >> arr[i];

        build(1, 1, len);

        while (qNum--)
        {
            int opr, qLeftPt, qRightPt;
            cin >> opr >> qLeftPt >> qRightPt;

            if (opr == 1)
            {
                // Add x
                long long int val;
                cin >> val;
                rangeAdd(1, qLeftPt, qRightPt, val);
            }
            else if (opr == 2)
            {
                // Change to sqrt
                rangeSqrt(1, qLeftPt, qRightPt);
            }
            else if (opr == 3)
            {
                // Range sum
                long long int ans = querySum(1, qLeftPt, qRightPt);
                cout << ans << endl;
            }
        }
    }

    return 0;
}
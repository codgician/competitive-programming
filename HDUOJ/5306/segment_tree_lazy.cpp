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

#define SIZE 1000100
#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegNode
{
    int leftPt, rightPt;
    int maxVal, secMaxVal;
    int maxNum;
    long long int sum;
    int lazy;
} SegNode;

SegNode segTree[SIZE << 2];

int arr[SIZE];

void pushUp(int segPt)
{
    if (segTree[LEFT_SON].maxVal > segTree[RIGHT_SON].maxVal)
    {
        segTree[segPt].maxVal = segTree[LEFT_SON].maxVal;
        segTree[segPt].maxNum = segTree[LEFT_SON].maxNum;
        segTree[segPt].secMaxVal = max(segTree[RIGHT_SON].maxVal, max(segTree[LEFT_SON].secMaxVal, segTree[RIGHT_SON].secMaxVal));
    }
    else if (segTree[LEFT_SON].maxVal < segTree[RIGHT_SON].maxVal)
    {
        segTree[segPt].maxVal = segTree[RIGHT_SON].maxVal;
        segTree[segPt].maxNum = segTree[RIGHT_SON].maxNum;
        segTree[segPt].secMaxVal = max(segTree[LEFT_SON].maxVal, max(segTree[LEFT_SON].secMaxVal, segTree[RIGHT_SON].secMaxVal));
    }
    else
    {
        segTree[segPt].maxVal = segTree[LEFT_SON].maxVal;
        segTree[segPt].maxNum = segTree[LEFT_SON].maxNum + segTree[RIGHT_SON].maxNum;
        segTree[segPt].secMaxVal = max(segTree[LEFT_SON].secMaxVal, segTree[RIGHT_SON].secMaxVal);
    }

    segTree[segPt].sum = segTree[LEFT_SON].sum + segTree[RIGHT_SON].sum;
}

void pushDown(int segPt)
{
    if (segTree[segPt].lazy != -1)
    {
        if (segTree[LEFT_SON].maxVal > segTree[segPt].lazy)
        {
            segTree[LEFT_SON].sum -= (long long int)segTree[LEFT_SON].maxNum * (segTree[LEFT_SON].maxVal - segTree[segPt].lazy);
            segTree[LEFT_SON].maxVal = segTree[segPt].lazy;
            segTree[LEFT_SON].lazy = segTree[segPt].lazy;
        }

        if (segTree[RIGHT_SON].maxVal > segTree[segPt].lazy)
        {
            segTree[RIGHT_SON].sum -= (long long int)segTree[RIGHT_SON].maxNum * (segTree[RIGHT_SON].maxVal - segTree[segPt].lazy);
            segTree[RIGHT_SON].maxVal = segTree[segPt].lazy;
            segTree[RIGHT_SON].lazy = segTree[segPt].lazy;
        }

        segTree[segPt].lazy = -1;
    }
}

void build(int segPt, int leftPt, int rightPt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;
    segTree[segPt].lazy = -1;

    if (leftPt == rightPt)
    {
        segTree[segPt].maxVal = arr[leftPt];
        segTree[segPt].maxNum = 1;
        segTree[segPt].secMaxVal = -1;
        segTree[segPt].sum = arr[leftPt];
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(segPt);
}

void rangeUpdate(int segPt, int qLeftPt, int qRightPt, int val)
{
    if (segTree[segPt].maxVal <= val)
    {
        return;
    }

    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        if (segTree[segPt].secMaxVal <= val)
        {
            segTree[segPt].sum -= (long long int)segTree[segPt].maxNum * (segTree[segPt].maxVal - val);
            segTree[segPt].maxVal = val;
            segTree[segPt].lazy = val;
            return;
        }
    }

    pushDown(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        rangeUpdate(LEFT_SON, qLeftPt, qRightPt, val);
    if (qRightPt > midPt)
        rangeUpdate(RIGHT_SON, qLeftPt, qRightPt, val);
    pushUp(segPt);
}

int queryMax(int segPt, int qLeftPt, int qRightPt)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        return segTree[segPt].maxVal;
    }

    pushDown(segPt);
    int ans = INT_MIN;
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans = max(ans, queryMax(LEFT_SON, qLeftPt, qRightPt));
    if (qRightPt > midPt)
        ans = max(ans, queryMax(RIGHT_SON, qLeftPt, qRightPt));
    return ans;
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
        int len, oprNum;
        cin >> len >> oprNum;
        for (int i = 1; i <= len; i++)
        {
            cin >> arr[i];
        }

        build(1, 1, len);

        while (oprNum--)
        {
            int opr, qLeftPt, qRightPt;
            cin >> opr >> qLeftPt >> qRightPt;

            if (opr == 0)
            {
                int val;
                cin >> val;
                rangeUpdate(1, qLeftPt, qRightPt, val);
            }
            else if (opr == 1)
            {
                cout << queryMax(1, qLeftPt, qRightPt) << endl;
            }
            else
            {
                cout << querySum(1, qLeftPt, qRightPt) << endl;
            }
        }
    }
    return 0;
}
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)
#define SIZE 800080

typedef struct _SegNode
{
    int leftPt, rightPt;
    long long int sum;
    long long int maxVal, minVal;
} SegNode;

SegNode segTree[SIZE << 2];

long long int minAns, maxAns;

void pushUp(int segPt)
{
    segTree[segPt].sum = segTree[LEFT_SON].sum + segTree[RIGHT_SON].sum;
    segTree[segPt].minVal = min(segTree[LEFT_SON].minVal, segTree[RIGHT_SON].minVal);
    segTree[segPt].maxVal = max(segTree[LEFT_SON].maxVal, segTree[RIGHT_SON].maxVal);
}

void build(int segPt, int leftPt, int rightPt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;

    if (leftPt == rightPt)
    {
        segTree[segPt].sum = 0;
        segTree[segPt].minVal = 0;
        segTree[segPt].maxVal = 0;
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(segPt);
}

void update(int segPt, int cntPt, long long int val)
{
    if (segTree[segPt].leftPt == segTree[segPt].rightPt)
    {
        segTree[segPt].sum = val;
        segTree[segPt].minVal = val;
        segTree[segPt].maxVal = val;
        return;
    }

    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (cntPt <= midPt)
        update(LEFT_SON, cntPt, val);
    else
        update(RIGHT_SON, cntPt, val);
    pushUp(segPt);
}

long long int querySum(int segPt, int qLeftPt, int qRightPt)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        return segTree[segPt].sum;
    }

    long long int ans = 0;
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans += querySum(LEFT_SON, qLeftPt, qRightPt);
    if (qRightPt > midPt)
        ans += querySum(RIGHT_SON, qLeftPt, qRightPt);
    return ans;
}

void queryMinMax(int segPt, int qLeftPt, int qRightPt)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        minAns = min(minAns, segTree[segPt].minVal);
        maxAns = max(maxAns, segTree[segPt].maxVal);
        return;
    }

    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        queryMinMax(LEFT_SON, qLeftPt, qRightPt);
    if (qRightPt > midPt)
        queryMinMax(RIGHT_SON, qLeftPt, qRightPt);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int len, qNum;
    while (cin >> len >> qNum)
    {
        build(1, 1, len);
        while (qNum--)
        {
            bool opr;
            cin >> opr;
            if (opr == 0)
            {
                int pos;
                long long int val;
                cin >> pos >> val;
                update(1, pos, val);
            }
            else
            {
                int leftPt, rightPt;
                cin >> leftPt >> rightPt;

                long long int sum = querySum(1, leftPt, rightPt);

                minAns = LLONG_MAX;
                maxAns = LLONG_MIN;
                queryMinMax(1, leftPt, rightPt);

                cout << sum - minAns - maxAns << endl;
            }
        }
    }
    return 0;
}
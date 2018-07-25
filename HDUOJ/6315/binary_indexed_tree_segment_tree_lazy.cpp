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

int arr[SIZE];
int bitArr[SIZE];
int num;

int getLowbit(int n)
{
    return n & -n;
}

void bitAdd(int pos, int val)
{
    for (int i = pos; i <= num; i += getLowbit(i))
    {
        bitArr[i] += val;
    }
}

int getSum(int pos)
{
    int ans = 0;
    for (int i = pos; i > 0; i -= getLowbit(i))
    {
        ans += bitArr[i];
    }
    return ans;
}

typedef struct _SegNode
{
    int leftPt, rightPt;
    int minVal, minPos;
    int lazy;
} SegNode;

SegNode segTree[SIZE << 2];

void pushUp(int segPt)
{
    if (segTree[LEFT_SON].minVal < segTree[RIGHT_SON].minVal)
    {
        segTree[segPt].minVal = segTree[LEFT_SON].minVal;
        segTree[segPt].minPos = segTree[LEFT_SON].minPos;
    }
    else if (segTree[LEFT_SON].minVal > segTree[RIGHT_SON].minVal)
    {
        segTree[segPt].minVal = segTree[RIGHT_SON].minVal;
        segTree[segPt].minPos = segTree[RIGHT_SON].minPos;
    }
    else
    {
        segTree[segPt].minVal = segTree[LEFT_SON].minVal;
        segTree[segPt].minPos = min(segTree[LEFT_SON].minPos, segTree[RIGHT_SON].minPos);
    }
}

void pushDown(int segPt)
{
    if (segTree[segPt].lazy != 0)
    {
        segTree[LEFT_SON].minVal += segTree[segPt].lazy;
        segTree[RIGHT_SON].minVal += segTree[segPt].lazy;

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
        segTree[segPt].minVal = arr[leftPt];
        segTree[segPt].minPos = leftPt;
        segTree[segPt].lazy = 0;
        return;
    }
    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(segPt);
    segTree[segPt].lazy = 0;
}

void rangeAdd(int segPt, int qLeftPt, int qRightPt, int val)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        segTree[segPt].minVal += val;
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

int queryMin(int segPt, int qLeftPt, int qRightPt)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        return segTree[segPt].minVal;
    }
    pushDown(segPt);
    int ans = INT_MAX;
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans = min(ans, queryMin(LEFT_SON, qLeftPt, qRightPt));
    if (qRightPt > midPt)
        ans = min(ans, queryMin(RIGHT_SON, qLeftPt, qRightPt));
    return ans;
}

pair<int, int> queryMinPos(int segPt, int qLeftPt, int qRightPt)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        return make_pair(segTree[segPt].minVal, segTree[segPt].minPos);
    }

    pushDown(segPt);
    pair<int, int> ans = make_pair(INT_MAX, INT_MAX);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans = min(ans, queryMinPos(LEFT_SON, qLeftPt, qRightPt));
    if (qRightPt > midPt)
        ans = min(ans, queryMinPos(RIGHT_SON, qLeftPt, qRightPt));
    return ans;
}

int main()
{
    int qNum;
    while (scanf("%d%d", &num, &qNum) != EOF)
    {
        memset(bitArr, 0, sizeof(bitArr));
        for (int i = 1; i <= num; i++)
        {
            scanf("%d", arr + i);
        }

        build(1, 1, num);

        while (qNum--)
        {
            char opr[10];
            scanf("%s", opr);
            int leftPt, rightPt;
            scanf("%d%d", &leftPt, &rightPt);

            if (opr[0] == 'a')
            {
                rangeAdd(1, leftPt, rightPt, -1);

                int cntLeft = leftPt, cntRight = rightPt;
                while (queryMin(1, cntLeft, cntRight) == 0)
                {
                    int cntMinPos = queryMinPos(1, cntLeft, cntRight).second;
                    bitAdd(cntMinPos, 1);
                    rangeAdd(1, cntMinPos, cntMinPos, arr[cntMinPos]);
                    cntLeft = cntMinPos + 1;
                    if (cntLeft > cntRight)
                        break;
                }
            }
            else
            {
                int ans = getSum(rightPt) - getSum(leftPt - 1);
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SIZE 80100
#define leftSon ((segPt << 1) + 1)
#define rightSon ((segPt << 1) + 2)
using namespace std;

typedef struct _SegTree
{
    int leftPt, rightPt;
    int preLen, sufLen;
    int maxLen;
    int lazy;
} SegTree;

SegTree segTree[SIZE << 2];

void pushUp(int segPt)
{
    segTree[segPt].maxLen = max(segTree[leftSon].sufLen + segTree[rightSon].preLen, max(segTree[leftSon].maxLen, segTree[rightSon].maxLen));

    segTree[segPt].preLen = segTree[leftSon].preLen;
    if (segTree[leftSon].preLen == segTree[leftSon].rightPt - segTree[leftSon].leftPt + 1)
    {
        segTree[segPt].preLen += segTree[rightSon].preLen;
    }

    segTree[segPt].sufLen = segTree[rightSon].sufLen;
    if (segTree[rightSon].sufLen == segTree[rightSon].rightPt - segTree[rightSon].leftPt + 1)
    {
        segTree[segPt].sufLen += segTree[leftSon].sufLen;
    }
}

void pushDown(int segPt)
{
    if (segTree[segPt].lazy > -1)
    {
        if (segTree[segPt].lazy == 0)
        {
            segTree[leftSon].maxLen = segTree[leftSon].rightPt - segTree[leftSon].leftPt + 1;
            segTree[leftSon].preLen = segTree[leftSon].rightPt - segTree[leftSon].leftPt + 1;
            segTree[leftSon].sufLen = segTree[leftSon].rightPt - segTree[leftSon].leftPt + 1;

            segTree[rightSon].maxLen = segTree[rightSon].rightPt - segTree[rightSon].leftPt + 1;
            segTree[rightSon].preLen = segTree[rightSon].rightPt - segTree[rightSon].leftPt + 1;
            segTree[rightSon].sufLen = segTree[rightSon].rightPt - segTree[rightSon].leftPt + 1;
        }
        else
        {
            segTree[leftSon].maxLen = 0;
            segTree[leftSon].preLen = 0;
            segTree[leftSon].sufLen = 0;

            segTree[rightSon].maxLen = 0;
            segTree[rightSon].preLen = 0;
            segTree[rightSon].sufLen = 0;
        }

        segTree[leftSon].lazy = segTree[segPt].lazy;
        segTree[rightSon].lazy = segTree[segPt].lazy;
        segTree[segPt].lazy = -1;
    }
}

void build(int segPt, int leftPt, int rightPt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;

    if (segTree[segPt].leftPt == segTree[segPt].rightPt)
    {
        segTree[segPt].preLen = 1;
        segTree[segPt].sufLen = 1;
        segTree[segPt].maxLen = 1;
        segTree[segPt].lazy = -1;
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(leftSon, leftPt, midPt);
    build(rightSon, midPt + 1, rightPt);
    pushUp(segPt);
    segTree[segPt].lazy = -1;
}

void rangeUpdate(int segPt, int leftPt, int rightPt, bool typeId)
{
    if (segTree[segPt].leftPt >= leftPt && segTree[segPt].rightPt <= rightPt)
    {
        if (typeId == 0)
        {
            segTree[segPt].maxLen = segTree[segPt].rightPt - segTree[segPt].leftPt + 1;
            segTree[segPt].preLen = segTree[segPt].rightPt - segTree[segPt].leftPt + 1;
            segTree[segPt].sufLen = segTree[segPt].rightPt - segTree[segPt].leftPt + 1;
            segTree[segPt].lazy = 0;
        }
        else
        {
            segTree[segPt].maxLen = 0;
            segTree[segPt].preLen = 0;
            segTree[segPt].sufLen = 0;
            segTree[segPt].lazy = 1;
        }

        return;
    }

    pushDown(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (leftPt <= midPt)
        rangeUpdate(leftSon, leftPt, rightPt, typeId);
    if (rightPt > midPt)
        rangeUpdate(rightSon, leftPt, rightPt, typeId);
    pushUp(segPt);
}

int query(int segPt, int needNum)
{
    pushDown(segPt);
    if (segTree[segPt].maxLen < needNum)
        return -1;

    if (segTree[segPt].leftPt == segTree[segPt].rightPt)
        return segTree[leftSon].leftPt;

    if (segTree[leftSon].maxLen >= needNum)
        return query(leftSon, needNum);

    if (segTree[leftSon].sufLen + segTree[rightSon].preLen >= needNum)
        return segTree[leftSon].rightPt - segTree[leftSon].sufLen + 1;

    return query(rightSon, needNum);
}

int main()
{
    ios::sync_with_stdio(false);
    int cowNum, oprNum;
    while (cin >> cowNum >> oprNum)
    {
        build(0, 0, cowNum - 1);

        for (int t = 0; t < oprNum; t++)
        {
            int opr;
            cin >> opr;
            if (opr == 1)
            {
                int groupSize;
                cin >> groupSize;

                int ans = query(0, groupSize);
                if (ans > -1)
                {
                    rangeUpdate(0, ans, ans + groupSize - 1, 1);
                    cout << ans + 1 << endl;
                }
                else
                {
                    cout << 0 << endl;
                }
            }
            else if (opr == 2)
            {
                int startPt, groupSize;
                cin >> startPt >> groupSize;
                startPt--;
                rangeUpdate(0, startPt, startPt + groupSize - 1, 0);
            }
        }
    }
    return 0;
}

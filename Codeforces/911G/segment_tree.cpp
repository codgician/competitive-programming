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

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)
#define SIZE 200010
#define VAL_SIZE 110

typedef struct _SegNode
{
    int val[VAL_SIZE];
    int leftPt, rightPt;
} SegNode;

SegNode segTree[SIZE << 2];
int arr[SIZE];

void pushDown(int segPt)
{
    for (int i = 0; i < VAL_SIZE; i++)
    {
        segTree[LEFT_SON].val[i] = segTree[segPt].val[segTree[LEFT_SON].val[i]];
        segTree[RIGHT_SON].val[i] = segTree[segPt].val[segTree[RIGHT_SON].val[i]];
    }
    for (int i = 0; i < VAL_SIZE; i++)
    {
        segTree[segPt].val[i] = i;
    }
}

void build(int segPt, int leftPt, int rightPt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;
    for (int i = 0; i < VAL_SIZE; i++)
    {
        segTree[segPt].val[i] = i;
    }

    if (leftPt == rightPt)
    {
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
}

void update(int segPt, int qLeftPt, int qRightPt, int orig, int val)
{
    if (qLeftPt <= segTree[segPt].leftPt && qRightPt >= segTree[segPt].rightPt)
    {
        for (int i = 0; i < VAL_SIZE; i++)
        {
            if (segTree[segPt].val[i] == orig)
            {
                segTree[segPt].val[i] = val;
            }
        }
        return;
    }
    
    pushDown(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        update(LEFT_SON, qLeftPt, qRightPt, orig, val);
    if (qRightPt > midPt)
        update(RIGHT_SON, qLeftPt, qRightPt, orig, val);
}

int query(int segPt, int pos)
{
    if (segTree[segPt].leftPt == pos && segTree[segPt].rightPt == pos)
    {
        return segTree[segPt].val[arr[pos]];
    }

    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (pos <= midPt)
        return segTree[segPt].val[query(LEFT_SON, pos)];
    else
        return segTree[segPt].val[query(RIGHT_SON, pos)];
}

int main()
{
    ios::sync_with_stdio(false);
    int len;
    cin >> len;
    for (int i = 1; i <= len; i++)
    {
        cin >> arr[i];
    }

    build(1, 1, len);

    int qNum;
    cin >> qNum;
    while (qNum--)
    {
        int qLeftPt, qRightPt, orig, val;
        cin >> qLeftPt >> qRightPt >> orig >> val;
        update(1, qLeftPt, qRightPt, orig, val);
    }

    for (int i = 1; i <= len; i++)
    {
        cout << query(1, i);
        if (i < len)
            cout << " ";
        else
            cout << endl;
    }
    return 0;
}
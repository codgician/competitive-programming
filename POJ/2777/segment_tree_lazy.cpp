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
#define SIZE 100010
using namespace std;

typedef struct _SegTree
{
    int leftPt, rightPt;
    int val;
    bool lazy;
} SegTree;

SegTree segTree[SIZE << 2];

void build(int segPt, int leftPt, int rightPt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;

    if (segTree[segPt].leftPt == segTree[segPt].rightPt)
    {
        segTree[segPt].val = 1;
        segTree[segPt].lazy = false;
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build((segPt << 1) + 1, leftPt, midPt);
    build((segPt << 1) + 2, midPt + 1, rightPt);

    segTree[segPt].val = segTree[(segPt << 1) + 1].val | segTree[(segPt << 1) + 2].val;
    segTree[segPt].lazy = false;
}

void spread(int segPt)
{
    if (segTree[segPt].lazy)
    {
        segTree[(segPt << 1) + 1].val = segTree[segPt].val;
        segTree[(segPt << 1) + 2].val = segTree[segPt].val;

        segTree[(segPt << 1) + 1].lazy = segTree[segPt].lazy;
        segTree[(segPt << 1) + 2].lazy = segTree[segPt].lazy;

        segTree[segPt].lazy = false;
    }
}

void rangeUpdate(int segPt, int leftPt, int rightPt, int val)
{
    if (segTree[segPt].leftPt >= leftPt && segTree[segPt].rightPt <= rightPt)
    {
        segTree[segPt].val = val;
        segTree[segPt].lazy = true;
        return;
    }

    spread(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (leftPt <= midPt)
        rangeUpdate((segPt << 1) + 1, leftPt, rightPt, val);
    if (rightPt > midPt)
        rangeUpdate((segPt << 1) + 2, leftPt, rightPt, val);

    segTree[segPt].val = segTree[(segPt << 1) + 1].val | segTree[(segPt << 1) + 2].val;
}

int query(int segPt, int leftPt, int rightPt)
{
    if (segTree[segPt].leftPt >= leftPt && segTree[segPt].rightPt <= rightPt)
    {
        return segTree[segPt].val;
    }

    spread(segPt);
    int ans = 0;
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (leftPt <= midPt)
        ans |= query((segPt << 1) + 1, leftPt, rightPt);
    if (rightPt > midPt)
        ans |= query((segPt << 1) + 2, leftPt, rightPt);

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int segNum, colNum, oprNum;
    while (cin >> segNum >> colNum >> oprNum)
    {
        build(0, 0, segNum - 1);

        while (oprNum--)
        {
            char opr;
            cin >> opr;

            if (opr == 'C')
            {
                int leftPt, rightPt, colorId;
                cin >> leftPt >> rightPt >> colorId;
                leftPt--;
                rightPt--;
                colorId--;
                if (leftPt > rightPt)
                    swap(leftPt, rightPt);

                int val = 1 << colorId;
                rangeUpdate(0, leftPt, rightPt, val);

            }
            else if (opr == 'P')
            {
                int leftPt, rightPt;
                cin >> leftPt >> rightPt;
                leftPt--;
                rightPt--;
                if (leftPt > rightPt)
                    swap(leftPt, rightPt);

                int val = query(0, leftPt, rightPt), ans = 0;
                while (val)
                {
                    val &= (val - 1);
                    ans++;
                }
                cout << ans << endl;
            }
        }
    }
    return 0;
}

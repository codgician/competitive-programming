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
    long long int val, lazy;
} SegTree;

SegTree segTree[SIZE << 2];

void build(int segTreePt, int leftPt, int rightPt)
{
    segTree[segTreePt].leftPt = leftPt;
    segTree[segTreePt].rightPt = rightPt;

    if (leftPt == rightPt)
    {
        segTree[segTreePt].val = 1;
        segTree[segTreePt].lazy = 0;
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build((segTreePt << 1) + 1, leftPt, midPt);
    build((segTreePt << 1) + 2, midPt + 1, rightPt);

    segTree[segTreePt].val = segTree[(segTreePt << 1) + 1].val + segTree[(segTreePt << 1) + 2].val;
    segTree[segTreePt].lazy = 0;
}

void spread(int segTreePt)
{
    if (segTree[segTreePt].lazy)
    {
        segTree[(segTreePt << 1) + 1].val = segTree[segTreePt].lazy * (segTree[(segTreePt << 1) + 1].rightPt - segTree[(segTreePt << 1) + 1].leftPt + 1);
        segTree[(segTreePt << 1) + 2].val = segTree[segTreePt].lazy * (segTree[(segTreePt << 1) + 2].rightPt - segTree[(segTreePt << 1) + 2].leftPt + 1);

        segTree[(segTreePt << 1) + 1].lazy = segTree[segTreePt].lazy;
        segTree[(segTreePt << 1) + 2].lazy = segTree[segTreePt].lazy;

        segTree[segTreePt].lazy = 0;
    }
}

void rangeUpdate(int segTreePt, int leftPt, int rightPt, long long int val)
{
    if (segTree[segTreePt].leftPt >= leftPt && segTree[segTreePt].rightPt <= rightPt)
    {
        segTree[segTreePt].val = val * (segTree[segTreePt].rightPt - segTree[segTreePt].leftPt + 1);
        segTree[segTreePt].lazy = val;
        return;
    }

    spread(segTreePt);
    int midPt = (segTree[segTreePt].leftPt + segTree[segTreePt].rightPt) >> 1;
    if (leftPt <= midPt)
        rangeUpdate((segTreePt << 1) + 1, leftPt, rightPt, val);
    if (rightPt > midPt)
        rangeUpdate((segTreePt << 1) + 2, leftPt, rightPt, val);

    segTree[segTreePt].val = segTree[(segTreePt << 1) + 1].val + segTree[(segTreePt << 1) + 2].val;
}

long long int query(int segTreePt, int leftPt, int rightPt)
{
    if (segTree[segTreePt].leftPt >= leftPt && segTree[segTreePt].rightPt <= rightPt)
    {
        return segTree[segTreePt].val;
    }

    spread(segTreePt);
    long long int ans = 0;
    int midPt = (segTree[segTreePt].leftPt + segTree[segTreePt].rightPt) >> 1;
    if (leftPt <= midPt)
        ans += query((segTreePt << 1) + 1, leftPt, rightPt);
    if (rightPt > midPt)
        ans += query((segTreePt << 1) + 2, leftPt, rightPt);

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        int stickNum, oprNum;
        cin >> stickNum >> oprNum;

        build(0, 0, stickNum - 1);

        while (oprNum--)
        {
            int leftPt, rightPt, val;
            cin >> leftPt >> rightPt >> val;
            leftPt--;
            rightPt--;

            rangeUpdate(0, leftPt, rightPt, val);
        }

        long long int ans = query(0, 0, stickNum - 1);
        cout << "Case " << t << ": The total value of the hook is " << ans << "." << endl;
    }
    return 0;
}

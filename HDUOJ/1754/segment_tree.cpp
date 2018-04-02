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
#define SIZE 200010
using namespace std;

typedef struct _SegTree
{
    int leftPt, rightPt;
    int val;
} SegTree;

SegTree segTree[SIZE << 2];
int arr[SIZE];

void build(int segTreePt, int leftPt, int rightPt)
{
    segTree[segTreePt].leftPt = leftPt;
    segTree[segTreePt].rightPt = rightPt;

    if (leftPt == rightPt)
    {
        segTree[segTreePt].val = arr[leftPt];
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build((segTreePt << 1) + 1, leftPt, midPt);
    build((segTreePt << 1) + 2, midPt + 1, rightPt);

    segTree[segTreePt].val = max(segTree[(segTreePt << 1) + 1].val, segTree[(segTreePt << 1) + 2].val);
}

void update(int segTreePt, int cntPt, int val)
{
    if (segTree[segTreePt].leftPt == segTree[segTreePt].rightPt)
    {
        segTree[segTreePt].val = val;
        return;
    }

    int midPt = (segTree[segTreePt].leftPt + segTree[segTreePt].rightPt) >> 1;
    if (cntPt <= midPt)
    {
        update((segTreePt << 1) + 1, cntPt, val);
    }
    else
    {
        update((segTreePt << 1) + 2, cntPt, val);
    }

    segTree[segTreePt].val = max(segTree[(segTreePt << 1) + 1].val, segTree[(segTreePt << 1) + 2].val);
}

int query(int segTreePt, int leftPt, int rightPt)
{
    if (segTree[segTreePt].leftPt >= leftPt && segTree[segTreePt].rightPt <= rightPt)
    {
        return segTree[segTreePt].val;
    }

    int ans = INT_MIN;
    int midPt = (segTree[segTreePt].leftPt + segTree[segTreePt].rightPt) >> 1;
    if (leftPt <= midPt)
    {
        ans = max(ans, query((segTreePt << 1) + 1, leftPt, rightPt));
    }
    if (rightPt > midPt)
    {
        ans = max(ans, query((segTreePt << 1) + 2, leftPt, rightPt));
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int stuNum, oprNum;
    while (cin >> stuNum >> oprNum)
    {
        for (int i = 0; i < stuNum; i++)
        {
            cin >> arr[i];
        }

        build(0, 0, stuNum - 1);

        while (oprNum--)
        {
            char opr;
            cin >> opr;
            if (opr == 'Q')
            {
                int leftPt, rightPt;
                cin >> leftPt >> rightPt;
                leftPt--;
                rightPt--;
                if (leftPt > rightPt)
                    swap(leftPt, rightPt);

                int ans = query(0, leftPt, rightPt);
                cout << ans << endl;
            }
            else if (opr == 'U')
            {
                int cntPt, val;
                cin >> cntPt >> val;
                cntPt--;
                update(0, cntPt, val);
            }
        }
    }
    return 0;
}

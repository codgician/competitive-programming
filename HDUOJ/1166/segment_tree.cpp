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
#define SIZE 50100
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
    build(segTreePt << 1, leftPt, midPt);
    build((segTreePt << 1) + 1, midPt + 1, rightPt);

    segTree[segTreePt].val = segTree[segTreePt << 1].val + segTree[(segTreePt << 1) + 1].val;
}

void add(int segTreePt, int cntPt, int val)
{
    if (segTree[segTreePt].leftPt == segTree[segTreePt].rightPt)
    {
        segTree[segTreePt].val += val;
        return;
    }

    int midPt = (segTree[segTreePt].leftPt + segTree[segTreePt].rightPt) >> 1;
    if (cntPt <= midPt)
        add(segTreePt << 1, cntPt, val);
    else
        add((segTreePt << 1) + 1, cntPt, val);

    segTree[segTreePt].val = segTree[segTreePt << 1].val + segTree[(segTreePt << 1) + 1].val;
}

int query(int segTreePt, int leftPt, int rightPt)
{
    if (segTree[segTreePt].leftPt >= leftPt && segTree[segTreePt].rightPt <= rightPt)
    {
        return segTree[segTreePt].val;
    }

    int ans = 0;
    int midPt = (segTree[segTreePt].leftPt + segTree[segTreePt].rightPt) >> 1;
    if (leftPt <= midPt)
    {
        ans += query(segTreePt << 1, leftPt, rightPt);
    }
    if (rightPt > midPt)
    {
        ans += query((segTreePt << 1) + 1, leftPt, rightPt);
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        int personNum;
        cin >> personNum;
        for (int i = 1; i <= personNum; i++)
        {
            cin >> arr[i];
        }

        build(1, 1, personNum);

        cout << "Case " << t << ":" << endl;
        string opr;
        while (cin >> opr)
        {
            if (opr == "Add")
            {
                int cntPt, val;
                cin >> cntPt >> val;
                add(1, cntPt, val);
            }
            else if (opr == "Sub")
            {
                int cntPt, val;
                cin >> cntPt >> val;
                add(1, cntPt, -val);
            }
            else if (opr == "Query")
            {
                int leftPt, rightPt;
                cin >> leftPt >> rightPt;
                int ans = query(1, leftPt, rightPt);
                cout << ans << endl;
            }
            else
            {
                break;
            }
        }
    }
    return 0;
}

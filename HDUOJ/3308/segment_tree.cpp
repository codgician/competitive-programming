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
#define SIZE 100100
using namespace std;

typedef struct _SegTree
{
    int leftPt, rightPt;
    int preLen, sufLen, maxLen;
} SegTree;

SegTree segTree[SIZE << 2];
int arr[SIZE];

void pushUp(int segPt, int leftPt, int rightPt)
{
    int midPt = (leftPt + rightPt) >> 1;

    segTree[segPt].maxLen = max(segTree[(segPt << 1) + 1].maxLen, segTree[(segPt << 1) + 2].maxLen);
    if (arr[midPt] < arr[midPt + 1])
        segTree[segPt].maxLen = max(segTree[segPt].maxLen, segTree[(segPt << 1) + 1].sufLen + segTree[(segPt << 1) + 2].preLen);

    segTree[segPt].preLen = segTree[(segPt << 1) + 1].preLen;
    if (segTree[(segPt << 1) + 1].preLen == midPt - leftPt + 1 && arr[midPt] < arr[midPt + 1])
        segTree[segPt].preLen += segTree[(segPt << 1) + 2].preLen;

    segTree[segPt].sufLen = segTree[(segPt << 1) + 2].sufLen;
    if (segTree[(segPt << 1) + 2].sufLen == rightPt - midPt && arr[midPt] < arr[midPt + 1])
        segTree[segPt].sufLen += segTree[(segPt << 1) + 1].sufLen;

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
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build((segPt << 1) + 1, leftPt, midPt);
    build((segPt << 1) + 2, midPt + 1, rightPt);
    pushUp(segPt, leftPt, rightPt);
}

void update(int segPt, int cntPt, int val)
{
    if (segTree[segPt].leftPt == segTree[segPt].rightPt)
    {
        arr[cntPt] = val;
        segTree[segPt].preLen = 1;
        segTree[segPt].sufLen = 1;
        segTree[segPt].maxLen = 1;
        return;
    }

    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (cntPt <= midPt)
        update((segPt << 1) + 1, cntPt, val);
    else
        update((segPt << 1) + 2, cntPt, val);
    pushUp(segPt, segTree[segPt].leftPt, segTree[segPt].rightPt);
}

int query(int segPt, int leftPt, int rightPt)
{
    if (segTree[segPt].leftPt >= leftPt && segTree[segPt].rightPt <= rightPt)
    {
        return segTree[segPt].maxLen;
    }

    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (rightPt <= midPt)
        return query((segPt << 1) + 1, leftPt, rightPt);
    if (leftPt > midPt)
        return query((segPt << 1) + 2, leftPt, rightPt);

    int ans = max(query((segPt << 1) + 1, leftPt, rightPt), query((segPt << 1) + 2, leftPt, rightPt));
    if (arr[midPt] < arr[midPt + 1])
    {
        int leftSufLen = min(midPt - leftPt + 1, segTree[(segPt << 1) + 1].sufLen);
        int rightPreLen = min(rightPt - midPt, segTree[(segPt << 1) + 2].preLen);
        ans = max(ans, leftSufLen + rightPreLen);
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int intNum, oprNum;
        cin >> intNum >> oprNum;

        for (int i = 0; i < intNum; i++)
        {
            cin >> arr[i];
        }

        build(0, 0, intNum - 1);

        while (oprNum--)
        {
            char opr;
            cin >> opr;

            if (opr == 'U')
            {
                int cntPt, val;
                cin >> cntPt >> val;
                update(0, cntPt, val);
            }
            else if (opr == 'Q')
            {
                int leftPt, rightPt;
                cin >> leftPt >> rightPt;
                int ans = query(0, leftPt, rightPt);
                cout << ans << endl;
            }
        }
    }
    return 0;
}

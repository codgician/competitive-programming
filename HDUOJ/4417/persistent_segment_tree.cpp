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

typedef struct _Node
{
    int sum;
    int leftSon, rightSon;
} SegNode;

SegNode segTree[SIZE * 20];
int root[SIZE];

int arr[SIZE], dsc[SIZE];
int cntPt;

void build(int & segPt, int leftPt, int rightPt)
{
    segPt = ++cntPt;
    segTree[segPt].sum = 0;
    if (leftPt == rightPt)
    {
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(segTree[segPt].leftSon, leftPt, midPt);
    build(segTree[segPt].rightSon, midPt + 1, rightPt);
}

void add(int & segPt, int prevPt, int leftPt, int rightPt, int pos, int val)
{
    segPt = ++cntPt;
    segTree[segPt].leftSon = segTree[prevPt].leftSon;
    segTree[segPt].rightSon = segTree[prevPt].rightSon;
    segTree[segPt].sum = segTree[prevPt].sum + val;

    if (leftPt == rightPt)
        return;

    int midPt = (leftPt + rightPt) >> 1;
    if (pos <= midPt)
        add(segTree[segPt].leftSon, segTree[prevPt].leftSon, leftPt, midPt, pos, val);
    else
        add(segTree[segPt].rightSon, segTree[prevPt].rightSon, midPt + 1, rightPt, pos, val);
}

int query(int leftPt, int rightPt, int qLeftPt, int qRightPt, int k)
{
    int ans = 0;
    while (leftPt < rightPt)
    {
        int midPt = (leftPt + rightPt) >> 1;
        if (k <= midPt)
        {
            qLeftPt = segTree[qLeftPt].leftSon;
            qRightPt = segTree[qRightPt].leftSon;
            rightPt = midPt;
        }
        else
        {
            ans += segTree[segTree[qRightPt].leftSon].sum - segTree[segTree[qLeftPt].leftSon].sum;
            qLeftPt = segTree[qLeftPt].rightSon;
            qRightPt = segTree[qRightPt].rightSon;
            leftPt = midPt + 1;
        }    
    }

    if (k >= leftPt)
        ans += segTree[qRightPt].sum - segTree[qLeftPt].sum;

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        cntPt = 0;
        memset(root, 0, sizeof(root));

        int len, qNum;
        cin >> len >> qNum;
        for (int i = 1; i <= len; i++)
        {
            cin >> arr[i];
            dsc[i] = arr[i];
        }
        sort(dsc + 1, dsc + len + 1);
        int dscLen = unique(dsc + 1, dsc + len + 1) - dsc - 1;
        for (int i = 1; i <= len; i++)
        {
            int pos = lower_bound(dsc + 1, dsc + dscLen + 1, arr[i]) - dsc;
            add(root[i], root[i - 1], 1, dscLen, pos, 1);
        }

        cout << "Case " << t << ":" << endl;
        while (qNum--)
        {
            int qLeftPt, qRightPt, k;
            cin >> qLeftPt >> qRightPt >> k;
            qLeftPt++;
            qRightPt++;
            k = upper_bound(dsc + 1, dsc + dscLen + 1, k) - dsc - 1;
            cout << query(1, dscLen, root[qLeftPt - 1], root[qRightPt], k) << endl;
        }
    }
    return 0;
}

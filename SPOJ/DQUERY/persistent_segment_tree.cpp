#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
using namespace std;

#define SIZE 30010

typedef struct _Node
{
    int sum;
    int leftSon, rightSon;
} SegNode;

SegNode segTree[SIZE * 40];
int rootArr[SIZE];

int arr[SIZE];
int cntPt;

map<int, int> posMp;

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

int query(int segPt, int leftPt, int rightPt, int qLeftPt, int qRightPt)
{
    if (qLeftPt <= leftPt && qRightPt >= rightPt)
    {
        return segTree[segPt].sum;
    }

    int ans = 0;
    int midPt = (leftPt + rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans += query(segTree[segPt].leftSon, leftPt, midPt, qLeftPt, qRightPt);
    if (qRightPt > midPt)
        ans += query(segTree[segPt].rightSon, midPt + 1, rightPt, qLeftPt, qRightPt);
    return ans;
}

int main()
{
    int len;
    while (scanf("%d", &len) != EOF)
    {
        memset(rootArr, 0, sizeof(rootArr));
        posMp.clear();

        for (int i = 1; i <= len; i++)
        {
            scanf("%d", arr + i);
            if (posMp.find(arr[i]) == posMp.end())
            {
                add(rootArr[i], rootArr[i - 1], 1, len, i, 1);
            }
            else
            {
                add(rootArr[i], rootArr[i - 1], 1, len, posMp[arr[i]], -1);
                add(rootArr[i], rootArr[i], 1, len, i, 1);
            }
            posMp[arr[i]] = i;
        }

        int qNum;
        scanf("%d", &qNum);
        while (qNum--)
        {
            int qLeftPt, qRightPt;
            scanf("%d%d", &qLeftPt, &qRightPt);
            int ans = query(rootArr[qRightPt], 1, len, qLeftPt, qRightPt);
            printf("%d\n", ans);
        }
    }

    return 0;
}
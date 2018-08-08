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

#define LSON(x) segTree[x].leftSon
#define RSON(x) segTree[x].rightSon
#define SIZE 100010

typedef struct _Node
{
    long long int sum;
    long long int lazy;
    int leftSon, rightSon;
} SegNode;

SegNode segTree[SIZE * 40];
int root[SIZE];

int arr[SIZE];
int cntPt;

void pushUp(int segPt, int len)
{
    segTree[segPt].sum = segTree[LSON(segPt)].sum + segTree[RSON(segPt)].sum + len * segTree[segPt].lazy;
}

void build(int & segPt, int leftPt, int rightPt)
{
    segPt = ++cntPt;
    segTree[segPt].lazy = 0;
    if (leftPt == rightPt)
    {
        segTree[segPt].sum = arr[leftPt];
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(segTree[segPt].leftSon, leftPt, midPt);
    build(segTree[segPt].rightSon, midPt + 1, rightPt);
    pushUp(segPt, 0);
}

void rangeAdd(int & segPt, int prevPt, int leftPt, int rightPt, int qLeftPt, int qRightPt, int val)
{
    segPt = ++cntPt;
    segTree[segPt] = segTree[prevPt];
    
    if (leftPt >= qLeftPt && rightPt <= qRightPt)
    {
        segTree[segPt].sum += (long long int)val * (rightPt - leftPt + 1);
        segTree[segPt].lazy += val;
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    if (qLeftPt <= midPt)
        rangeAdd(LSON(segPt), LSON(prevPt), leftPt, midPt, qLeftPt, qRightPt, val);
    if (qRightPt > midPt)
        rangeAdd(RSON(segPt), RSON(prevPt), midPt + 1, rightPt, qLeftPt, qRightPt, val);
    pushUp(segPt, rightPt - leftPt + 1);
}

long long int querySum(int segPt, int leftPt, int rightPt, int qLeftPt, int qRightPt, long long int lazy)
{
    if (leftPt >= qLeftPt && rightPt <= qRightPt)
    {
        return segTree[segPt].sum + lazy * (rightPt - leftPt + 1);
    }

    long long int ans = 0;
    int midPt = (leftPt + rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans += querySum(LSON(segPt), leftPt, midPt, qLeftPt, qRightPt, lazy + segTree[segPt].lazy);
    if (qRightPt > midPt)
        ans += querySum(RSON(segPt), midPt + 1, rightPt, qLeftPt, qRightPt, lazy + segTree[segPt].lazy);
    return ans;
}

int main()
{
    int len, oprNum;
    while (scanf("%d%d", &len, &oprNum) != EOF)
    {
        cntPt = 0;
        memset(root, 0, sizeof(root));
        for (int i = 1; i <= len; i++)
        {
            scanf("%d", arr + i);
        }

        build(root[0], 1, len);

        int cntTime = 0;
        while (oprNum--)
        {
            char opr[2];
            scanf("%s", opr);
            if (opr[0] == 'Q')
            {
                int qLeftPt, qRightPt;
                scanf("%d%d", &qLeftPt, &qRightPt);
                printf("%lld\n", querySum(root[cntTime], 1, len, qLeftPt, qRightPt, 0));
            }
            else if (opr[0] == 'C')
            {
                int qLeftPt, qRightPt, val;
                scanf("%d%d%d", &qLeftPt, &qRightPt, &val);
                rangeAdd(root[cntTime + 1], root[cntTime], 1, len, qLeftPt, qRightPt, val);
                cntTime++;
            }
            else if (opr[0] == 'H')
            {
                int qLeftPt, qRightPt, hstTime;
                scanf("%d%d%d", &qLeftPt, &qRightPt, &hstTime);
                printf("%lld\n", querySum(root[hstTime], 1, len, qLeftPt, qRightPt, 0));
            }
            else if (opr[0] == 'B')
            {
                int destTime;
                scanf("%d", &destTime);
                cntTime = destTime;
            }
        }
    }
    return 0;
}
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

#define QUERY_SIZE 50010
#define DSC_SIZE 100010

typedef struct _Query
{
    int qLeftPt, qRightPt;
    long long int a, b;
} Query;

Query qArr[QUERY_SIZE];
int dscArr[DSC_SIZE], dscPt;
int len;

long long int quasiEuclidean(long long int a, long long int b, long long int c, long long int n)
{
    if (a == 0)
    {
        return (n + 1) * (b / c);
    }

    if (a >= c || b >= c)
    {
        long long int tmp = (n & 1) ? ((n + 1) >> 1) * n : (n >> 1) * (n + 1);
        return (a / c) * tmp + (b / c) * (n + 1) + quasiEuclidean(a % c, b % c, c, n);
    }

    long long int m = (a * n + b) / c;
    return n * m - quasiEuclidean(c, c - b - 1, a, m - 1);
}

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegNode
{
    int leftPt, rightPt;
    long long int sum, a, b, startPt;
} SegNode;

SegNode segTree[DSC_SIZE << 2];

void updateNode(int segPt, long long int a, long long int b, long long int startPt)
{
    segTree[segPt].a = a;
    segTree[segPt].b = b;
    segTree[segPt].startPt = startPt;

    long long int n = dscArr[segTree[segPt].rightPt] - dscArr[segTree[segPt].leftPt - 1];
    long long int sec = b * (quasiEuclidean(a, 0, b, dscArr[segTree[segPt].rightPt] - startPt) - quasiEuclidean(a, 0, b, dscArr[segTree[segPt].leftPt - 1] - startPt));
    segTree[segPt].sum = (n * (dscArr[segTree[segPt].leftPt - 1] - startPt + 1) + ((n & 1) ? ((n - 1) >> 1) * n : (n >> 1) * (n - 1))) * a - sec;  
}

void pushUp(int segPt)
{
    segTree[segPt].sum = segTree[LEFT_SON].sum + segTree[RIGHT_SON].sum;
}

void pushDown(int segPt)
{
    if (segTree[segPt].b != 0)
    {
        updateNode(LEFT_SON, segTree[segPt].a, segTree[segPt].b, segTree[segPt].startPt);
        updateNode(RIGHT_SON, segTree[segPt].a, segTree[segPt].b, segTree[segPt].startPt);
        segTree[segPt].b = 0;
    }
}

void build(int segPt, int leftPt, int rightPt)
{
    segTree[segPt] = {leftPt, rightPt, 0, 0, 0, 0};

    if (leftPt == rightPt)
        return;

    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
}

void rangeUpdate(int segPt, int qLeftPt, int qRightPt, long long int a, long long int b, long long int startPt)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        updateNode(segPt, a, b, startPt);
        return;
    }

    pushDown(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;

    if (qLeftPt <= midPt)
        rangeUpdate(LEFT_SON, qLeftPt, qRightPt, a, b, startPt);
    if (qRightPt > midPt)
        rangeUpdate(RIGHT_SON, qLeftPt, qRightPt, a, b, startPt);

    pushUp(segPt);
}

long long int querySum(int segPt, int qLeftPt, int qRightPt)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        return segTree[segPt].sum;
    }

    pushDown(segPt);
    long long int ans = 0;
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans += querySum(LEFT_SON, qLeftPt, qRightPt);
    if (qRightPt > midPt)
        ans += querySum(RIGHT_SON, qLeftPt, qRightPt);

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int qNum;
    cin >> len >> qNum;

    dscPt = 0;
    for (int i = 0; i < qNum; i++)
    {
        int type;
        cin >> type >> qArr[i].qLeftPt >> qArr[i].qRightPt;
        dscArr[dscPt++] = qArr[i].qLeftPt;
        dscArr[dscPt++] = qArr[i].qRightPt + 1;

        if (type == 1)
        {
            cin >> qArr[i].a >> qArr[i].b;
            qArr[i].a %= qArr[i].b;
        }
        else
        {
            qArr[i].a = -1;
            qArr[i].b = -1;
        }
    }

    sort(dscArr + 0, dscArr + dscPt);
    dscPt = unique(dscArr + 0, dscArr + dscPt) - dscArr;

    build(1, 1, dscPt);

    for (int i = 0; i < qNum; i++)
    {
        int dscLeftPt = lower_bound(dscArr + 0, dscArr + dscPt, qArr[i].qLeftPt) - dscArr + 1;
        int dscRightPt = lower_bound(dscArr + 0, dscArr + dscPt, qArr[i].qRightPt + 1) - dscArr;

        if (qArr[i].a == -1)
            cout << querySum(1, dscLeftPt, dscRightPt) << endl;
        else
            rangeUpdate(1, dscLeftPt, dscRightPt, qArr[i].a, qArr[i].b, qArr[i].qLeftPt);
    }

    return 0;
}

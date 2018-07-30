#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <cfloat>
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
#define SIZE 60010

const double eps = 1e-7;

typedef struct _SegNode
{
    int leftPt, rightPt;
    double minVal, lazy;
} SegNode;

SegNode segTree[SIZE << 2];
int arr[SIZE], pre[SIZE], aprPos[SIZE];
int num;

void pushUp(int segPt)
{
    segTree[segPt].minVal = min(segTree[LEFT_SON].minVal, segTree[RIGHT_SON].minVal);
}

void pushDown(int segPt)
{
    if (segTree[segPt].lazy != 0)
    {
        segTree[LEFT_SON].minVal += segTree[segPt].lazy;
        segTree[RIGHT_SON].minVal += segTree[segPt].lazy;

        segTree[LEFT_SON].lazy += segTree[segPt].lazy;
        segTree[RIGHT_SON].lazy += segTree[segPt].lazy;

        segTree[segPt].lazy = 0;
    }
}

void build(int segPt, int leftPt, int rightPt, double cnt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;
    if (leftPt == rightPt)
    {
        segTree[segPt].minVal = leftPt * cnt;
        segTree[segPt].lazy = 0;
        return;
    }
    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt, cnt);
    build(RIGHT_SON, midPt + 1, rightPt, cnt);
    pushUp(segPt);
    segTree[segPt].lazy = 0;
}

void rangeAdd(int segPt, int qLeftPt, int qRightPt, double val)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        segTree[segPt].minVal += val;
        segTree[segPt].lazy += val;
        return;
    }
    pushDown(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        rangeAdd(LEFT_SON, qLeftPt, qRightPt, val);
    if (qRightPt > midPt)
        rangeAdd(RIGHT_SON, qLeftPt, qRightPt, val);
    pushUp(segPt);
}

double queryMin(int segPt, int qLeftPt, int qRightPt)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        return segTree[segPt].minVal;
    }
    pushDown(segPt);
    double ans = DBL_MAX;
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans = min(ans, queryMin(LEFT_SON, qLeftPt, qRightPt));
    if (qRightPt > midPt)
        ans = min(ans, queryMin(RIGHT_SON, qLeftPt, qRightPt));
    return ans;
}

bool check(double cnt)
{
    build(1, 1, num, cnt);
    for (int i = 1; i <= num; i++)
    {
        rangeAdd(1, pre[i] + 1, i, 1);
        if (queryMin(1, 1, i) <= cnt * (i + 1))
            return false;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(pre, -1, sizeof(pre));
        memset(aprPos, -1, sizeof(aprPos));
        cin >> num;
        for (int i = 1; i <= num; i++)
        {
            cin >> arr[i];
            pre[i] = aprPos[arr[i]];
            aprPos[arr[i]] = i;
        }

        double leftPt = 0, rightPt = 1;
        double ans = -1;
        while (rightPt - leftPt > eps)
        {
            double midPt = (leftPt + rightPt) / 2;
            if (check(midPt))
            {
                leftPt = midPt + eps;
                ans = midPt;
            }
            else
            {
                rightPt = midPt - eps;
            }
        }
        cout << fixed << setprecision(6) << ans << endl;
    }
    return 0;
}
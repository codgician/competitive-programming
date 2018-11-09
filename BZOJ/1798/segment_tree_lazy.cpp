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

long long int arr[SIZE], mod;

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegNode
{
    int leftPt, rightPt;
    long long int sum;
    long long int addLazy, mulLazy;
} SegNode;

SegNode segTree[SIZE << 2];

void pushUp(int segPt)
{
    segTree[segPt].sum = (segTree[LEFT_SON].sum + segTree[RIGHT_SON].sum) % mod;
}

void pushDown(int segPt)
{
    if (segTree[segPt].mulLazy != 1)
    {
        segTree[LEFT_SON].sum = segTree[LEFT_SON].sum * segTree[segPt].mulLazy % mod;
        segTree[RIGHT_SON].sum = segTree[RIGHT_SON].sum * segTree[segPt].mulLazy % mod;

        segTree[LEFT_SON].mulLazy = segTree[LEFT_SON].mulLazy * segTree[segPt].mulLazy % mod;
        segTree[LEFT_SON].addLazy = segTree[LEFT_SON].addLazy * segTree[segPt].mulLazy % mod;
        segTree[RIGHT_SON].mulLazy = segTree[RIGHT_SON].mulLazy * segTree[segPt].mulLazy % mod;
        segTree[RIGHT_SON].addLazy = segTree[RIGHT_SON].addLazy * segTree[segPt].mulLazy % mod;

        segTree[segPt].mulLazy = 1;
    }

    if (segTree[segPt].addLazy != 0)
    {
        segTree[LEFT_SON].sum = (segTree[LEFT_SON].sum + segTree[segPt].addLazy * (segTree[LEFT_SON].rightPt - segTree[LEFT_SON].leftPt + 1) % mod) % mod;
        segTree[RIGHT_SON].sum = (segTree[RIGHT_SON].sum + segTree[segPt].addLazy * (segTree[RIGHT_SON].rightPt - segTree[RIGHT_SON].leftPt + 1) % mod) % mod;

        segTree[LEFT_SON].addLazy = (segTree[LEFT_SON].addLazy + segTree[segPt].addLazy) % mod;
        segTree[RIGHT_SON].addLazy = (segTree[RIGHT_SON].addLazy + segTree[segPt].addLazy) % mod;

        segTree[segPt].addLazy = 0; 
    }
}

void build(int segPt, int leftPt, int rightPt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;
    segTree[segPt].addLazy = 0;
    segTree[segPt].mulLazy = 1;

    if (leftPt == rightPt)
    {
        segTree[segPt].sum = arr[leftPt] % mod;
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(segPt);
}

void rangeAdd(int segPt, int qLeftPt, int qRightPt, long long int val)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        segTree[segPt].sum = (segTree[segPt].sum + val * (segTree[segPt].rightPt - segTree[segPt].leftPt + 1) % mod) % mod;
        segTree[segPt].addLazy = (segTree[segPt].addLazy + val) % mod;
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

void rangeMul(int segPt, int qLeftPt, int qRightPt, long long int val)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        segTree[segPt].sum = segTree[segPt].sum * val % mod;
        segTree[segPt].mulLazy = segTree[segPt].mulLazy * val % mod;
        segTree[segPt].addLazy = segTree[segPt].addLazy * val % mod;
        return;
    }

    pushDown(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        rangeMul(LEFT_SON, qLeftPt, qRightPt, val);
    if (qRightPt > midPt)
        rangeMul(RIGHT_SON, qLeftPt, qRightPt, val);
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
        ans = (ans + querySum(LEFT_SON, qLeftPt, qRightPt)) % mod;
    if (qRightPt > midPt)
        ans = (ans + querySum(RIGHT_SON, qLeftPt, qRightPt)) % mod;
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int len;
    cin >> len >> mod;

    for (int i = 1; i <= len; i++)
        cin >> arr[i];

    build(1, 1, len);

    int qNum;
    cin >> qNum;
    while (qNum--)
    {
        int type, qLeftPt, qRightPt;
        cin >> type >> qLeftPt >> qRightPt;

        if (type == 1)
        {
            // Multiply
            long long int val;
            cin >> val;
            rangeMul(1, qLeftPt, qRightPt, val % mod);
        }
        else if (type == 2)
        {
            // Add
            long long int val;
            cin >> val;
            rangeAdd(1, qLeftPt, qRightPt, val % mod);
        }
        else if (type == 3)
        {
            // Query Sum
            long long int ans = querySum(1, qLeftPt, qRightPt);
            cout << ans << endl;
        }
    }
    return 0;
}
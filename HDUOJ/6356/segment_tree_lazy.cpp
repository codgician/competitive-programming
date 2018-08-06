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
#define OPR_SIZE 5000010
#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegNode
{
    unsigned int leftPt, rightPt;
    unsigned int minVal, maxVal;
    unsigned int lazy;
} SegNode;

SegNode segTree[SIZE << 2];
unsigned int randArr[OPR_SIZE * 3];

unsigned int x, y, z;
long long int ans;

const unsigned int mod = 1 << 30;

unsigned int rng61()
{
    x = x ^ (x << 11);
    x = x ^ (x >> 4);
    x = x ^ (x << 5);
    x = x ^ (x >> 14);
    unsigned int w = x ^ (y ^ z);
    x = y;
    y = z;
    z = w;
    return z;
}

void pushUp(unsigned int segPt)
{
    segTree[segPt].minVal = min(segTree[LEFT_SON].minVal, segTree[RIGHT_SON].minVal);
    segTree[segPt].maxVal = max(segTree[LEFT_SON].maxVal, segTree[RIGHT_SON].maxVal);
}

void pushDown(unsigned int segPt)
{
    if (segTree[segPt].lazy != 0)
    {
        segTree[LEFT_SON].minVal = segTree[segPt].lazy;
        segTree[RIGHT_SON].minVal = segTree[segPt].lazy;
        segTree[LEFT_SON].maxVal = segTree[segPt].lazy;
        segTree[RIGHT_SON].maxVal = segTree[segPt].lazy;

        segTree[LEFT_SON].lazy = segTree[segPt].lazy;
        segTree[RIGHT_SON].lazy = segTree[segPt].lazy;

        segTree[segPt].lazy = 0;
    }
}

void build(unsigned int segPt, unsigned int leftPt, unsigned int rightPt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;
    segTree[segPt].lazy = 0;
    if (leftPt == rightPt)
    {
        segTree[segPt].minVal = 0;
        segTree[segPt].maxVal = 0;
        return;
    }

    unsigned int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(segPt);
}

void rangeUpdate(unsigned int segPt, unsigned int qLeftPt, unsigned int qRightPt, unsigned int val)
{
    // Fuck...
    if (segTree[segPt].minVal > val)
        return;

    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        if (segTree[segPt].maxVal < val)
        {
            segTree[segPt].minVal = val;
            segTree[segPt].maxVal = val;
            segTree[segPt].lazy = val;
            return;
        }
        else if (segTree[segPt].minVal > val)
        {
            return;
        }
    }

    pushDown(segPt);
    unsigned int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        rangeUpdate(LEFT_SON, qLeftPt, qRightPt, val);
    if (qRightPt > midPt)
        rangeUpdate(RIGHT_SON, qLeftPt, qRightPt, val);
    pushUp(segPt);
}

void getAns(unsigned int segPt, unsigned int leftPt, unsigned int rightPt)
{
    if (leftPt == rightPt)
    {
        ans ^= (long long int)leftPt * segTree[segPt].minVal;
        return;
    }

    pushDown(segPt);
    unsigned int midPt = (leftPt + rightPt) >> 1;
    getAns(LEFT_SON, leftPt, midPt);
    getAns(RIGHT_SON, midPt + 1, rightPt);
}

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        int num, oprNum;
        scanf("%d%d", &num, &oprNum);
        scanf("%u%u%u", &x, &y, &z);
        for (int i = 1; i <= oprNum * 3; i++)
        {
            randArr[i] = rng61();
        }

        build(1, 1, num);

        for (int i = 1; i <= oprNum; i++)
        {
            unsigned int qLeftPt = randArr[3 * i - 2] % num + 1;
            unsigned int qRightPt = randArr[3 * i - 1] % num + 1;

            if (qLeftPt > qRightPt)
                swap(qLeftPt, qRightPt);
            unsigned int val = randArr[3 * i] % mod;
            if (val == 0)
                continue;
            rangeUpdate(1, qLeftPt, qRightPt, val);
        }
        
        ans = 0;
        getAns(1, 1, num);
        printf("%lld\n", ans);
    }
    return 0;
}
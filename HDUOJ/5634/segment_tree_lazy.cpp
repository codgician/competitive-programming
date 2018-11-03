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
#include <cassert>
using namespace std;

#define SIZE 300010
#define PHI_SIZE 10000010

int factorArr[PHI_SIZE], primeArr[664580], phi[PHI_SIZE];
int primePt;

void initPhi()
{
    memset(factorArr, 0, sizeof(factorArr));
    primePt = 0;
    for (int i = 2; i < PHI_SIZE; i++)
    {
        if (factorArr[i] == 0)
        {
            factorArr[i] = i;
            primeArr[primePt++] = i;
            phi[i] = i - 1;
        }

        for (int j = 0; j < primePt; j++)
        {
            if (primeArr[j] > factorArr[i] || primeArr[j] > (PHI_SIZE - 1) / i)
                break;
            factorArr[i * primeArr[j]] = primeArr[j];
            phi[i * primeArr[j]] = phi[i] * (i % primeArr[j] == 0 ? primeArr[j] : primeArr[j] - 1);
        }
    }
}

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegNode
{
    int leftPt, rightPt;
    int minVal, maxVal, lazy;
    long long int sum;
} SegNode;

SegNode segTree[SIZE << 2];

int arr[SIZE];

void pushUp(int segPt)
{
    segTree[segPt].sum = segTree[LEFT_SON].sum + segTree[RIGHT_SON].sum;
    segTree[segPt].minVal = min(segTree[LEFT_SON].minVal, segTree[RIGHT_SON].minVal);
    segTree[segPt].maxVal = max(segTree[LEFT_SON].maxVal, segTree[RIGHT_SON].maxVal);
}

void pushDown(int segPt)
{
    if (segTree[segPt].lazy != 0)
    {
        segTree[LEFT_SON].minVal = segTree[segPt].lazy;
        segTree[LEFT_SON].maxVal = segTree[segPt].lazy;
        segTree[RIGHT_SON].minVal = segTree[segPt].lazy;
        segTree[RIGHT_SON].maxVal = segTree[segPt].lazy;

        segTree[LEFT_SON].sum = (long long int)segTree[segPt].lazy * (segTree[LEFT_SON].rightPt - segTree[LEFT_SON].leftPt + 1);
        segTree[RIGHT_SON].sum = (long long int)segTree[segPt].lazy * (segTree[RIGHT_SON].rightPt - segTree[RIGHT_SON].leftPt + 1);

        segTree[LEFT_SON].lazy = segTree[segPt].lazy;
        segTree[RIGHT_SON].lazy = segTree[segPt].lazy;

        segTree[segPt].lazy = 0;
    }
}

void build(int segPt, int leftPt, int rightPt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;

    if (leftPt == rightPt)
    {
        segTree[segPt].minVal = arr[leftPt];
        segTree[segPt].maxVal = arr[leftPt];
        segTree[segPt].sum = arr[leftPt];
        segTree[segPt].lazy = 0;
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(segPt);
    segTree[segPt].lazy = 0;
}

void rangeUpd(int segPt, int qLeftPt, int qRightPt, int val)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        segTree[segPt].minVal = val;
        segTree[segPt].maxVal = val;
        segTree[segPt].sum = (long long int)val * (segTree[segPt].rightPt - segTree[segPt].leftPt + 1);
        segTree[segPt].lazy = val;
        return;
    }

    pushDown(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        rangeUpd(LEFT_SON, qLeftPt, qRightPt, val);
    if (qRightPt > midPt)
        rangeUpd(RIGHT_SON, qLeftPt, qRightPt, val);
    pushUp(segPt);
}

void rangePhi(int segPt, int qLeftPt, int qRightPt)
{
    if (segTree[segPt].minVal == 1 && segTree[segPt].maxVal == 1)
        return;

    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        if (segTree[segPt].minVal == segTree[segPt].maxVal)
        {
            int val = phi[segTree[segPt].minVal];
            segTree[segPt].minVal = val;
            segTree[segPt].maxVal = val;
            segTree[segPt].sum = (long long int)val * (segTree[segPt].rightPt - segTree[segPt].leftPt + 1);
            segTree[segPt].lazy = val;
            return;
        }
    }

    pushDown(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        rangePhi(LEFT_SON, qLeftPt, qRightPt);
    if (qRightPt > midPt)
        rangePhi(RIGHT_SON, qLeftPt, qRightPt);
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
    initPhi();

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int len, qNum;
        cin >> len >> qNum;

        for (int i = 1; i <= len; i++)
            cin >> arr[i];
        
        build(1, 1, len);

        while (qNum--)
        {
            int type, qLeftPt, qRightPt;
            cin >> type >> qLeftPt >> qRightPt;

            if (type == 1)
            {
                rangePhi(1, qLeftPt, qRightPt);
            }
            else if (type == 2)
            {
                int val;
                cin >> val;
                rangeUpd(1, qLeftPt, qRightPt, val);
            }
            else if (type == 3)
            {
                cout << querySum(1, qLeftPt, qRightPt) << endl;
            }
        }
    }

    return 0;
}
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
#define leftSon (segPt << 1) + 1
#define rightSon (segPt << 1) + 2
#define UPD_TWO false
#define UPD_THREE true
#define SIZE 100010
using namespace std;

typedef struct _SegTree
{
    int leftPt, rightPt;
    int twoNum, threeNum;
    int twoLazy, threeLazy;
} SegTree;

SegTree segTree[SIZE << 2];

const long long int mod = 998244353;

long long int fastPow(long long int a, int n)
{
    long long int ans = 1;
    ans %= mod;

    while (n > 0)
    {
        if (n & 1)
            ans = ans * a % mod;
        a = a * a % mod;
        n >>= 1;
    }

    return ans % mod;
}

void pushUp(int segPt)
{
    segTree[segPt].twoNum = min(segTree[leftSon].twoNum, segTree[rightSon].twoNum);
    segTree[segPt].threeNum = min(segTree[leftSon].threeNum, segTree[rightSon].threeNum);
}

void pushDown(int segPt)
{
    if (segTree[segPt].twoLazy)
    {
        segTree[leftSon].twoNum += segTree[segPt].twoLazy;
        segTree[rightSon].twoNum += segTree[segPt].twoLazy;


        segTree[leftSon].twoLazy += segTree[segPt].twoLazy;
        segTree[rightSon].twoLazy += segTree[segPt].twoLazy;

        segTree[segPt].twoLazy = 0;
    }

    if (segTree[segPt].threeLazy)
    {
        segTree[leftSon].threeNum += segTree[segPt].threeLazy;
        segTree[rightSon].threeNum += segTree[segPt].threeLazy;


        segTree[leftSon].threeLazy += segTree[segPt].threeLazy;
        segTree[rightSon].threeLazy += segTree[segPt].threeLazy;

        segTree[segPt].threeLazy = 0;
    }
}

void build(int segPt, int leftPt, int rightPt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;

    if (segTree[segPt].leftPt == segTree[segPt].rightPt)
    {
        segTree[segPt].twoNum = 0;
        segTree[segPt].threeNum = 0;
        segTree[segPt].twoLazy = 0;
        segTree[segPt].threeLazy = 0;
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(leftSon, leftPt, midPt);
    build(rightSon, midPt + 1, rightPt);
    pushUp(segPt);
    segTree[segPt].twoLazy = 0;
    segTree[segPt].threeLazy = 0;
}

void rangeUpdate(int segPt, int leftPt, int rightPt, bool updType)
{
    if (segTree[segPt].leftPt >= leftPt && segTree[segPt].rightPt <= rightPt)
    {
        if (updType == UPD_TWO)
        {
            segTree[segPt].twoNum++;
            segTree[segPt].twoLazy++;
        }
        else if (updType == UPD_THREE)
        {
            segTree[segPt].threeNum++;
            segTree[segPt].threeLazy++;
        }
        return;
    }

    pushDown(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (leftPt <= midPt)
        rangeUpdate(leftSon, leftPt, rightPt, updType);
    if (rightPt > midPt)
        rangeUpdate(rightSon, leftPt, rightPt, updType);
    pushUp(segPt);
}

int query(int segPt, int leftPt, int rightPt, bool qType)
{
    if (segTree[segPt].leftPt >= leftPt && segTree[segPt].rightPt <= rightPt)
    {
        if (qType == UPD_TWO)
        {
            return segTree[segPt].twoNum;
        }
        else if (qType == UPD_THREE)
        {
            return segTree[segPt].threeNum;
        }
    }

    pushDown(segPt);
    int ans = INT_MAX;
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (leftPt <= midPt)
        ans = min(ans, query(leftSon, leftPt, rightPt, qType));
    if (rightPt > midPt)
        ans = min(ans, query(rightSon, leftPt, rightPt, qType));

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int seqLen, oprNum;
        cin >> seqLen >> oprNum;

        build(0, 0, seqLen - 1);

        while (oprNum--)
        {
            int leftPt, rightPt, factor;
            cin >> leftPt >> rightPt >> factor;
            leftPt--;
            rightPt--;
            if (factor == 2)
            {
                rangeUpdate(0, leftPt, rightPt, UPD_TWO);
            }
            else if (factor == 3)
            {
                rangeUpdate(0, leftPt, rightPt, UPD_THREE);
            }
        }

        int twoAns = query(0, 0, seqLen - 1, UPD_TWO);
        int threeAns = query(0, 0, seqLen - 1, UPD_THREE);
        long long int ans = (fastPow(2, twoAns) * fastPow(3, threeAns)) % mod;

        cout << ans << endl;
    }
    return 0;
}

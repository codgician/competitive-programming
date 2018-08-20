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

#define SIZE 100100

// k > 0: query
// k == 0: modify: pos = qLeftPt, val = qRightPt, type = cntNum
typedef struct _Opr
{
    int qLeftPt, qRightPt, k;
    int id, cntNum;
} Opr;

// len + (qNum << 1)
Opr oprArr[SIZE * 3], fstQueue[SIZE * 3], sndQueue[SIZE * 3];

int arr[SIZE], ans[SIZE];

int bitArr[SIZE];

int len, qNum;

int getLowbit(int n)
{
    return n & -n;
}

void add(int pos, int val)
{
    for (int i = pos; i <= len; i += getLowbit(i))
    {
        bitArr[i] += val;
    }
}

int getPrefixSum(int pos)
{
    int ans = 0;
    for (int i = pos; i > 0; i -= getLowbit(i))
    {
        ans += bitArr[i];
    }
    return ans;
}

void divideConquer(int headPt, int tailPt, int leftPt, int rightPt)
{
    if (leftPt == rightPt)
    {
        for (int i = headPt; i <= tailPt; i++)
        {
            if (oprArr[i].id == -1)
                continue;
            ans[oprArr[i].id] = rightPt;
        }
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;

    // Update BIT
    for (int i = headPt; i <= tailPt; i++)
    {
        if (oprArr[i].k > 0)
        {
            // query
            oprArr[i].cntNum = getPrefixSum(oprArr[i].qRightPt + 1) - getPrefixSum(oprArr[i].qLeftPt);
        }
        else if (oprArr[i].qRightPt <= midPt)
        {
            // modify && val <= midPt
            add(oprArr[i].qLeftPt + 1, oprArr[i].cntNum);
        }
    }

    // Restore BIT
    for (int i = headPt; i <= tailPt; i++)
    {
        if (oprArr[i].k == 0 && oprArr[i].qRightPt <= midPt)
        {
            add(oprArr[i].qLeftPt + 1, -oprArr[i].cntNum);
        }
    }

    int fstQPt = 0, sndQPt = 0;
    for (int i = headPt; i <= tailPt; i++)
    {
        if (oprArr[i].k > 0)
        {
            // query
            if (oprArr[i].k <= oprArr[i].cntNum)
            {
                fstQueue[fstQPt++] = oprArr[i];
            }
            else
            {
                oprArr[i].k -= oprArr[i].cntNum;
                sndQueue[sndQPt++] = oprArr[i];
            }
        }
        else
        {
            // modify
            if (oprArr[i].qRightPt <= midPt)
            {
                fstQueue[fstQPt++] = oprArr[i];
            }
            else
            {
                sndQueue[sndQPt++] = oprArr[i];
            }
        }
    }

    int cntPt = headPt;
    for (int i = 0; i < fstQPt; i++)
    {
        oprArr[cntPt++] = fstQueue[i];
    }
    for (int i = 0; i < sndQPt; i++)
    {
        oprArr[cntPt++] = sndQueue[i];
    }

    if (fstQPt > 0)
        divideConquer(headPt, headPt + fstQPt - 1, leftPt, midPt);
    if (headPt + fstQPt <= tailPt)
        divideConquer(headPt + fstQPt, tailPt, midPt + 1, rightPt);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> len)
    {
        memset(bitArr, 0, sizeof(bitArr));
        int oprNum = 0, maxVal = INT_MIN;
        for (int i = 0; i < len; i++)
        {
            cin >> arr[i];
            oprArr[oprNum++] = {i, arr[i], 0, -1, 1};
            maxVal = max(maxVal, arr[i]);
        }

        cin >> qNum;

        for (int i = 0; i < qNum; i++)
        {
            int opr;
            cin >> opr;
            if (opr == 1)
            {
                // change
                int pos, val;
                cin >> pos >> val;
                pos--;

                // delete original
                oprArr[oprNum++] = {pos, arr[pos], 0, -1, -1};
                // insert new
                oprArr[oprNum++] = {pos, val, 0, -1, 1};
                arr[pos] = val;
                maxVal = max(maxVal, val);
                ans[i] = -1;
            }
            else
            {
                // query
                int qLeftPt, qRightPt, k;
                cin >> qLeftPt >> qRightPt >> k;
                qLeftPt--;
                qRightPt--;
                oprArr[oprNum++] = {qLeftPt, qRightPt, k, i, 0};
            }
        }

        divideConquer(0, oprNum - 1, 1, maxVal);

        for (int i = 0; i < qNum; i++)
        {
            if (ans[i] != -1)
            {
                cout << ans[i] << endl;
            }
        }
    }
    return 0;
}
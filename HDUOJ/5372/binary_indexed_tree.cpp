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

#define SIZE 200010

typedef struct _Query
{
    int id;
    int opr, leftPt, rightPt;
} Query;

Query qArr[SIZE];

int addArr[SIZE];
int leftBit[SIZE], rightBit[SIZE];
int leftDsc[SIZE], rightDsc[SIZE];

int getLowbit(int n)
{
    return n & (-n);
}

void add(int * bitArr, int pos, int val)
{
    for (int i = pos; i < SIZE; i += getLowbit(i))
    {
        bitArr[i] += val;
    }
}

int getPrefixSum(int * bitArr, int pos)
{
    int ans = 0;
    for (int i = pos; i > 0; i -= getLowbit(i))
    {
        ans += bitArr[i];
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int oprNum, casePt = 0;
    while (cin >> oprNum)
    {
        memset(leftBit, 0, sizeof(leftBit));
        memset(rightBit, 0, sizeof(rightBit));

        int addPt = 0;
        for (int i = 0; i < oprNum; i++)
        {
            cin >> qArr[i].opr >> qArr[i].leftPt;
            if (qArr[i].opr == 0)
            {
                // add
                qArr[i].rightPt = qArr[i].leftPt + addPt + 1;
                leftDsc[addPt] = qArr[i].leftPt;
                rightDsc[addPt] = qArr[i].rightPt;
                addArr[addPt] = i;
                addPt++;
            }
            else
            {
                // delete
                qArr[i].leftPt--;
            }
        }

        sort(leftDsc + 0, leftDsc + addPt);
        sort(rightDsc + 0, rightDsc + addPt);
        int leftLen = unique(leftDsc + 0, leftDsc + addPt) - leftDsc;
        int rightLen = unique(rightDsc + 0, rightDsc + addPt) - rightDsc;

        cout << "Case #" << ++casePt << ":" << endl;

        for (int i = 0; i < oprNum; i++)
        {
            if (qArr[i].opr == 0)
            {
                // add
                int leftPos = lower_bound(leftDsc + 0, leftDsc + leftLen, qArr[i].leftPt) - leftDsc + 1;
                int rightPos = lower_bound(rightDsc + 0, rightDsc + rightLen, qArr[i].rightPt) - rightDsc + 1;
                cout << getPrefixSum(rightBit, rightPos) - getPrefixSum(leftBit, leftPos - 1) << endl;
                add(leftBit, leftPos, 1);
                add(rightBit, rightPos, 1);
            }
            else
            {
                // delete
                int qPt = addArr[qArr[i].leftPt];
                int leftPos = lower_bound(leftDsc + 0, leftDsc + leftLen, qArr[qPt].leftPt) - leftDsc + 1;
                int rightPos = lower_bound(rightDsc + 0, rightDsc + rightLen, qArr[qPt].rightPt) - rightDsc + 1;
                add(leftBit, leftPos, -1);
                add(rightBit, rightPos, -1);
            }
        }
    }

    return 0;
}
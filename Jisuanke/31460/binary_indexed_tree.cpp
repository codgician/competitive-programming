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

long long int origBit[SIZE], procBit[SIZE];
int len;

int getLowbit(int n)
{
    return n & -n;
}

void add(long long int bitArr[], int pos, long long int val)
{
    for (int i = pos; i <= len; i += getLowbit(i))
    {
        bitArr[i] += val;
    }
}

long long int getPrefixSum(long long int bitArr[], int pos)
{
    long long int ans = 0;
    for (int i = pos; i > 0; i -= getLowbit(i))
    {
        ans += bitArr[i];
    }
    return ans;
}

long long int getRangeSum(long long int bitArr[], int leftPt, int rightPt)
{
    return getPrefixSum(bitArr, rightPt) - getPrefixSum(bitArr, leftPt - 1);
}

void update(long long int bitArr[], int pos, long long int val)
{
    long long int origVal = getRangeSum(bitArr, pos, pos);
    add(bitArr, pos, val - origVal);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int qNum;
    while (cin >> len >> qNum)
    {
        memset(origBit, 0, sizeof(origBit));
        memset(procBit, 0, sizeof(procBit));
        for (int i = 1; i <= len; i++)
        {
            long long int cnt;
            cin >> cnt;
            update(origBit, i, cnt);
            update(procBit, i, cnt * (len - i + 1));
        }

        while (qNum--)
        {
            int opr;
            cin >> opr;
            if (opr == 1)
            {
                // query
                int leftPt, rightPt;
                cin >> leftPt >> rightPt;

                long long int procInterval = getRangeSum(procBit, leftPt, rightPt);
                long long int origInterval = getRangeSum(origBit, leftPt, rightPt);
                long long int ans = procInterval - (len - rightPt) * origInterval;
                cout << ans << endl;
            }
            else if (opr == 2)
            {
                // modify
                int pos;
                long long int val;
                cin >> pos >> val;

                update(origBit, pos, val);
                update(procBit, pos, val * (len - pos + 1));
            }
        }
    }

    return 0;
}
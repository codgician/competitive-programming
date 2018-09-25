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

typedef struct _Box
{
    int pos, weight;
} Box;

Box arr[SIZE];
long long int bit1[SIZE], bit2[SIZE];

const int mod = 1e9 + 7;
int num;

int getLowbit(int n)
{
    return n & (-n);
}

void add(long long int * bitArr, int pos, long long int val, bool shouldMod)
{
    if (shouldMod)
        val = (val + mod) % mod;

    for (int i = pos; i <= num; i += getLowbit(i))
    {
        bitArr[i] += val;
        if (shouldMod)
            bitArr[i] = (bitArr[i] + mod) % mod;
    }
}

long long int getPrefixSum(long long int * bitArr, int pos, bool shouldMod)
{
    long long int ans = 0;
    for (int i = pos; i > 0; i -= getLowbit(i))
    {
        ans += bitArr[i];
        if (shouldMod)
            ans = (ans + mod) % mod;
    }
    return ans;
}

long long int getRangeSum(long long int * bitArr, int qLeftPt, int qRightPt, bool shouldMod)
{
    if (qRightPt < qLeftPt)
        return 0;

    long long int ans = getPrefixSum(bitArr, qRightPt, shouldMod) - getPrefixSum(bitArr, qLeftPt - 1, shouldMod);
    if (shouldMod)
        ans = (ans + mod) % mod;
    return ans;
}

int getMidPos(int qLeftPt, int qRightPt)
{
    int leftPt = qLeftPt, rightPt = qRightPt;
    int ans = rightPt;

    while (leftPt <= rightPt)
    {
        int midPt = (leftPt + rightPt) >> 1;
        if (getRangeSum(bit1, qLeftPt, midPt, false) >= getRangeSum(bit1, midPt + 1, qRightPt, false))
        {
            ans = midPt;
            rightPt = midPt - 1;
        }
        else
        {
            leftPt = midPt + 1;
        }
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    memset(bit1, 0, sizeof(bit1));
    memset(bit2, 0, sizeof(bit2));
    int qNum;
    cin >> num >> qNum;
    for (int i = 1; i <= num; i++)
    {
        cin >> arr[i].pos;
    }
    for (int i = 1; i <= num; i++)
    {
        cin >> arr[i].weight;
        add(bit1, i, arr[i].weight, false);
        add(bit2, i, (long long int)arr[i].weight * (arr[i].pos - i), true);
    }

    while (qNum--)
    {
        int x, y;
        cin >> x >> y;

        if (x < 0)
        {
            // modify weight
            x = -x;
            add(bit1, x, y - arr[x].weight, false);
            add(bit2, x, ((long long int)y - arr[x].weight) * (arr[x].pos - x), true);
            arr[x].weight = y;
        }
        else
        {
            // query energy
            if (x == y)
            {
                cout << 0 << endl;
                continue;
            }
            
            int midPos = getMidPos(x, y);

            long long int leftAns = (getRangeSum(bit1, x, midPos, true) * abs(arr[midPos].pos - midPos) % mod - getRangeSum(bit2, x, midPos, true) + mod) % mod;
            long long int rightAns = (getRangeSum(bit1, midPos, y, true) * abs(arr[midPos].pos - midPos) % mod - getRangeSum(bit2, midPos, y, true) + mod) % mod;

            long long int ans = (leftAns - rightAns + mod) % mod;

            cout << ans << endl;
        }
    }

    return 0;
}